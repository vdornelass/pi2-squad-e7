#include "ranking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATCH_HISTORY_FILE "bin/matches.csv"
#define MAX_TEMP_ENTRIES 64

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

static void normalize_player_name(const char *player_name, char clean_name[MAX_NAME_LEN]) {
    if (player_name == NULL || player_name[0] == '\0') {
        strncpy(clean_name, "OPERADOR", MAX_NAME_LEN - 1);
        clean_name[MAX_NAME_LEN - 1] = '\0';
        return;
    }

    int j = 0;
    for (int i = 0; player_name[i] != '\0' && j < MAX_NAME_LEN - 1; i++) {
        char c = player_name[i];
        clean_name[j++] = (c == ' ' || c == '\t') ? '_' : c;
    }
    clean_name[j] = '\0';

    if (j == 0) {
        strncpy(clean_name, "OPERADOR", MAX_NAME_LEN - 1);
        clean_name[MAX_NAME_LEN - 1] = '\0';
    }
}

static void ranking_save_entries(const RankingEntry entries[], int count) {
    FILE *f = fopen(RANKING_FILE, "w");
    if (!f) return;

    for (int i = 0; i < count; i++) {
        fprintf(f, "%s %d\n", entries[i].name, entries[i].score);
    }
    fclose(f);
}

int ranking_load(RankingEntry entries[], int max_entries) {
    FILE *f = fopen(RANKING_FILE, "r");
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

bool ranking_name_exists(const char *player_name) {
    char clean_name[MAX_NAME_LEN];
    normalize_player_name(player_name, clean_name);

    RankingEntry entries[MAX_TEMP_ENTRIES];
    int count = ranking_load(entries, MAX_TEMP_ENTRIES);
    for (int i = 0; i < count; i++) {
        if (names_equal_nocase(entries[i].name, clean_name)) {
            return true;
        }
    }
    return false;
}

void ranking_add_score(const char *player_name, int score) {
    RankingEntry entries[MAX_TEMP_ENTRIES];
    int count = ranking_load(entries, MAX_TEMP_ENTRIES - 1);

    char clean_name[MAX_NAME_LEN];
    normalize_player_name(player_name, clean_name);

    /* Nao sobrescreve um nome ja existente no ranking */
    for (int i = 0; i < count; i++) {
        if (names_equal_nocase(entries[i].name, clean_name)) {
            return;
        }
    }

    strncpy(entries[count].name, clean_name, MAX_NAME_LEN - 1);
    entries[count].name[MAX_NAME_LEN - 1] = '\0';
    entries[count].score = score;
    count++;

    /* Ordena do maior para o menor score */
    qsort(entries, (size_t)count, sizeof(RankingEntry), compare_entries_desc);

    if (count > MAX_RANKING_ENTRIES) {
        count = MAX_RANKING_ENTRIES;
    }

    ranking_save_entries(entries, count);
}

void ranking_compute_stats(MatchStats *stats) {
    if (!stats) return;
    stats->total_matches = 0;
    stats->victories = 0;
    stats->win_rate_pct = 0;
    stats->avg_accuracy_pct = 0;
    stats->highest_score = 0;

    FILE *f = fopen(MATCH_HISTORY_FILE, "r");
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
