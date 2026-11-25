#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#define MAKE_DIR(path) _mkdir(path)
#else
#include <sys/types.h>
#define MAKE_DIR(path) mkdir((path), 0755)
#endif

#ifdef S_ISDIR
#define IS_DIR_MODE(m) S_ISDIR(m)
#else
#define IS_DIR_MODE(m) (((m) & _S_IFDIR) != 0)
#endif

#define RANKING_BASENAME "ranking.txt"
#define MATCH_HISTORY_BASENAME "matches.csv"
#define MAX_TEMP_ENTRIES 64

static bool dir_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0) && IS_DIR_MODE(st.st_mode);
}

static bool file_exists_local(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

/* Resolve bin/<arquivo> a partir da raiz OU <arquivo> se executado dentro de bin/ */
static void resolve_data_path(const char *basename, char *out, size_t out_size, bool ensure_dir) {
    if (dir_exists("bin")) {
        snprintf(out, out_size, "bin/%s", basename);
        return;
    }
    if (dir_exists("../src") || file_exists_local("raylib.dll") || file_exists_local(basename)) {
        snprintf(out, out_size, "%s", basename);
        return;
    }
    if (ensure_dir) {
        if (MAKE_DIR("bin") == 0 || dir_exists("bin")) {
            snprintf(out, out_size, "bin/%s", basename);
            return;
        }
    }
    snprintf(out, out_size, "%s", basename);
}

static int compare_entries_desc(const void *a, const void *b) {
    const RankingEntry *ea = (const RankingEntry *)a;
    const RankingEntry *eb = (const RankingEntry *)b;
    return eb->score - ea->score;
}

static bool names_equal_nocase(const char *a, const char *b) {
    while (*a != '\0' && *b != '\0') {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return false;
        }
        a++;
        b++;
    }
    return (*a == '\0' && *b == '\0');
}

static bool normalize_player_name_strict(const char *player_name, char clean_name[MAX_NAME_LEN]) {
    clean_name[0] = '\0';
    if (player_name == NULL) {
        return false;
    }

    const char *start = player_name;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        start++;
    }
    size_t len = strlen(start);
    while (len > 0 && isspace((unsigned char)start[len - 1])) {
        len--;
    }
    if (len == 0) {
        return false;
    }

    int j = 0;
    for (size_t i = 0; i < len && j < MAX_NAME_LEN - 1; i++) {
        unsigned char uc = (unsigned char)start[i];
        if (uc < 32 || uc == 127) continue;
        clean_name[j++] = (start[i] == ' ' || start[i] == '\t') ? '_' : start[i];
    }
    clean_name[j] = '\0';
    return (j > 0);
}

static void normalize_player_name(const char *player_name, char clean_name[MAX_NAME_LEN]) {
    if (!normalize_player_name_strict(player_name, clean_name)) {
        strncpy(clean_name, "OPERADOR", MAX_NAME_LEN - 1);
        clean_name[MAX_NAME_LEN - 1] = '\0';
    }
}

static bool ranking_save_entries(const RankingEntry entries[], int count) {
    char path[256];
    resolve_data_path(RANKING_BASENAME, path, sizeof(path), true);

    FILE *f = fopen(path, "w");
    if (!f) return false;

    for (int i = 0; i < count; i++) {
        if (fprintf(f, "%s %d\n", entries[i].name, entries[i].score) < 0) {
            fclose(f);
            return false;
        }
    }
    if (fflush(f) != 0 || ferror(f)) {
        fclose(f);
        return false;
    }
    return fclose(f) == 0;
}

int ranking_load(RankingEntry entries[], int max_entries) {
    char path[256];
    resolve_data_path(RANKING_BASENAME, path, sizeof(path), false);

    FILE *f = fopen(path, "r");
    if (!f) return 0;

    int count = 0;
    bool had_duplicates = false;
    char tmp_name[MAX_NAME_LEN];
    int tmp_score = 0;

    while (fscanf(f, "%15s %d", tmp_name, &tmp_score) == 2) {
        int existing_idx = -1;
        for (int i = 0; i < count; i++) {
            if (names_equal_nocase(entries[i].name, tmp_name)) {
                existing_idx = i;
                break;
            }
        }

        if (existing_idx >= 0) {
            had_duplicates = true;
            if (tmp_score > entries[existing_idx].score) {
                entries[existing_idx].score = tmp_score;
            }
        } else if (count < max_entries) {
            strncpy(entries[count].name, tmp_name, MAX_NAME_LEN - 1);
            entries[count].name[MAX_NAME_LEN - 1] = '\0';
            entries[count].score = tmp_score;
            count++;
        }
    }
    fclose(f);

    if (count > 1) {
        qsort(entries, (size_t)count, sizeof(RankingEntry), compare_entries_desc);
    }

    if (had_duplicates) {
        ranking_save_entries(entries, count);
    }

    return count;
}

int ranking_get_score(const char *player_name) {
    char clean_name[MAX_NAME_LEN];
    if (!normalize_player_name_strict(player_name, clean_name)) {
        return -1;
    }

    RankingEntry entries[MAX_TEMP_ENTRIES];
    int count = ranking_load(entries, MAX_TEMP_ENTRIES);
    for (int i = 0; i < count; i++) {
        if (names_equal_nocase(entries[i].name, clean_name)) {
            return entries[i].score;
        }
    }
    return -1;
}

bool ranking_name_exists(const char *player_name) {
    return ranking_get_score(player_name) >= 0;
}

int ranking_add_score(const char *player_name, int score) {
    char clean_name[MAX_NAME_LEN];
    if (!normalize_player_name_strict(player_name, clean_name)) {
        return 0;
    }

    RankingEntry entries[MAX_TEMP_ENTRIES];
    int count = ranking_load(entries, MAX_TEMP_ENTRIES - 1);

    /* Se o nome ja existe: atualiza somente se superou o proprio recorde (sem duplicar) */
    bool updated_existing = false;
    for (int i = 0; i < count; i++) {
        if (names_equal_nocase(entries[i].name, clean_name)) {
            if (score > entries[i].score) {
                entries[i].score = score;
                updated_existing = true;
                break;
            }
            return 0;
        }
    }

    if (!updated_existing) {
        strncpy(entries[count].name, clean_name, MAX_NAME_LEN - 1);
        entries[count].name[MAX_NAME_LEN - 1] = '\0';
        entries[count].score = score;
        count++;
    }

    /* Ordena do maior para o menor score */
    qsort(entries, (size_t)count, sizeof(RankingEntry), compare_entries_desc);

    if (count > MAX_RANKING_ENTRIES) {
        count = MAX_RANKING_ENTRIES;
    }

    if (!ranking_save_entries(entries, count)) {
        return -1;
    }

    /* Posicao em que o nome ficou (0 = fora do Top 10) */
    for (int i = 0; i < count; i++) {
        if (names_equal_nocase(entries[i].name, clean_name)) {
            return i + 1;
        }
    }
    return 0;
}

const char *ranking_clean_name(const char *player_name, char out[MAX_NAME_LEN]) {
    normalize_player_name(player_name, out);
    return out;
}

void ranking_compute_stats(MatchStats *stats) {
    if (!stats) return;
    stats->total_matches = 0;
    stats->victories = 0;
    stats->win_rate_pct = 0;
    stats->avg_accuracy_pct = 0;
    stats->highest_score = 0;

    char path[256];
    resolve_data_path(MATCH_HISTORY_BASENAME, path, sizeof(path), false);

    FILE *f = fopen(path, "r");
    if (!f) return;

    char line[128];
    long sum_accuracy = 0;

    while (fgets(line, sizeof(line), f) != NULL) {
        char date_buf[32];
        int score = 0;
        int acc = 0;
        int vic = 0;

        if (sscanf(line, "%31[^;];%d;%d;%d", date_buf, &score, &acc, &vic) == 4) {
            stats->total_matches++;
            if (vic > 0) stats->victories++;
            sum_accuracy += acc;
            if (score > stats->highest_score) {
                stats->highest_score = score;
            }
        }
    }
    fclose(f);

    if (stats->total_matches > 0) {
        stats->win_rate_pct = (stats->victories * 100) / stats->total_matches;
        stats->avg_accuracy_pct = (int)(sum_accuracy / stats->total_matches);
    }
}
