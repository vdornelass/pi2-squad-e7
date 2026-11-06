#include "save.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAVE_FILE_PATH "bin/savegame.dat"
#define MATCH_FILE_PATH "bin/matches.csv"

bool save_game(const SaveData *data) {
    FILE *file = fopen(SAVE_FILE_PATH, "wb");
    if (!file) return false;

    /* Cria uma copia local para injetar a assinatura e versao */
    SaveData out_data = *data;
    out_data.magic = SAVE_MAGIC_NUMBER;
    out_data.version = SAVE_VERSION;

    size_t written = fwrite(&out_data, sizeof(SaveData), 1, file);
    fclose(file);

    return (written == 1);
}

bool load_game(SaveData *data) {
    FILE *file = fopen(SAVE_FILE_PATH, "rb");
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
    FILE *file = fopen(SAVE_FILE_PATH, "rb");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

void save_match_result(int score, int accuracy_pct, int victory) {
    FILE *file = fopen(MATCH_FILE_PATH, "a");
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
    fclose(file);
}
