#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <direct.h>
#define SAVE_MAKE_DIR(path) _mkdir(path)
#else
#include <sys/types.h>
#define SAVE_MAKE_DIR(path) mkdir((path), 0755)
#endif

#ifdef S_ISDIR
#define SAVE_IS_DIR_MODE(m) S_ISDIR(m)
#else
#define SAVE_IS_DIR_MODE(m) (((m) & _S_IFDIR) != 0)
#endif

#define SAVE_BASENAME "savegame.dat"
#define MATCH_BASENAME "matches.csv"

static bool save_dir_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0) && SAVE_IS_DIR_MODE(st.st_mode);
}

static bool save_file_exists_local(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0);
}

static void save_resolve_path(const char *basename, char *out, size_t out_size, bool ensure_dir) {
    if (save_dir_exists("bin")) {
        snprintf(out, out_size, "bin/%s", basename);
        return;
    }
    if (save_dir_exists("../src") || save_file_exists_local("raylib.dll") || save_file_exists_local(basename)) {
        snprintf(out, out_size, "%s", basename);
        return;
    }
    if (ensure_dir) {
        if (SAVE_MAKE_DIR("bin") == 0 || save_dir_exists("bin")) {
            snprintf(out, out_size, "bin/%s", basename);
            return;
        }
    }
    snprintf(out, out_size, "%s", basename);
}

bool save_game(const SaveData *data) {
    char path[256];
    save_resolve_path(SAVE_BASENAME, path, sizeof(path), true);

    FILE *file = fopen(path, "wb");
    if (!file) return false;

    /* Cria uma copia local para injetar a assinatura e versao */
    SaveData out_data = *data;
    out_data.magic = SAVE_MAGIC_NUMBER;
    out_data.version = SAVE_VERSION;

    size_t written = fwrite(&out_data, sizeof(SaveData), 1, file);
    fflush(file);
    int closed = fclose(file);

    return (written == 1 && closed == 0);
}

bool load_game(SaveData *data) {
    char path[256];
    save_resolve_path(SAVE_BASENAME, path, sizeof(path), false);

    FILE *file = fopen(path, "rb");
    if (!file) return false;

    size_t read_bytes = fread(data, sizeof(SaveData), 1, file);
    fclose(file);

    if (read_bytes != 1) return false;

    /* Valida a integridade do arquivo atraves do numero magico e versao */
    if (data->magic != SAVE_MAGIC_NUMBER || data->version != SAVE_VERSION) {
        return false;
    }

    return true;
}

bool save_exists(void) {
    char path[256];
    save_resolve_path(SAVE_BASENAME, path, sizeof(path), false);

    FILE *file = fopen(path, "rb");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

void save_match_result(int score, int accuracy_pct, int victory) {
    char path[256];
    save_resolve_path(MATCH_BASENAME, path, sizeof(path), true);

    FILE *file = fopen(path, "a");
    if (!file) return;

    /* Captura a data e hora atuais do sistema */
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char date_str[20] = "2026-10-22 00:00:00";
    if (tm_info != NULL) {
        strftime(date_str, sizeof(date_str), "%Y-%m-%d %H:%M:%S", tm_info);
    }

    /* Grava os dados separados por ponto e virgula para o calculo de estatisticas em C */
    fprintf(file, "%s;%d;%d;%d\n", date_str, score, accuracy_pct, victory);
    fflush(file);
    fclose(file);
}
