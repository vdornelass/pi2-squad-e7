#include "report.h"
#include "config.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <time.h>



#define RATING_EXEMPLAR_PCT 90  
#define RATING_STABLE_PCT   70  

const char *report_rating(int accuracy_pct) {
    if (accuracy_pct >= RATING_EXEMPLAR_PCT) return "ALINHAMENTO EXEMPLAR";
    if (accuracy_pct >= RATING_STABLE_PCT)   return "ALINHAMENTO ESTÁVEL";
    return "ALINHAMENTO PARCIAL";
}

static const char *difficulty_name(int difficulty) {
    return (difficulty == DIFFICULTY_HARD) ? "DIFÍCIL" : "NORMAL";
}

static void format_time(float seconds, char *buf, size_t size) {
    int total = (int)(seconds + 0.5f);
    if (total < 0) total = 0;
    snprintf(buf, size, "%02d:%02d", total / 60, total % 60);
}

void report_build(Certificate *c, const char *player_name, int score,
                  int accuracy_pct, float session_time,
                  int patches_done, int patches_total,
                  int phase, int difficulty, int alignment_pct) {
    char stamp[16];
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);

    memset(c, 0, sizeof(*c));
    snprintf(c->player_name, sizeof(c->player_name), "%s",
             (player_name != NULL && player_name[0] != '\0') ? player_name : "JOGADOR ANONIMO" /* sem acento: com o Ô passaria de MAX_NAME_LEN (16 bytes) */);
    c->score = score;
    c->accuracy_pct = accuracy_pct;
    c->session_time = session_time;
    c->patches_done = patches_done;
    c->patches_total = patches_total;
    c->phase = phase;
    c->difficulty = difficulty;
    c->alignment_pct = alignment_pct;

    if (lt != NULL) {
        strftime(c->issued_at, sizeof(c->issued_at), "%Y-%m-%d %H:%M:%S", lt);
        strftime(stamp, sizeof(stamp), "%Y%m%d%H%M%S", lt);
    } else {
        snprintf(c->issued_at, sizeof(c->issued_at), "N/D");
        snprintf(stamp, sizeof(stamp), "00000000000000");
    }
    snprintf(c->cert_id, sizeof(c->cert_id), "AURA67-%s-%06d", stamp, score);
}

/* ------------------------------------------------------------------ TXT -- */

bool report_export_txt(const Certificate *c, const char *path) {
    char tbuf[16];
    FILE *f = fopen(path, "w");
    if (f == NULL) return false;

    format_time(c->session_time, tbuf, sizeof(tbuf));

    fprintf(f, "==================================================\n");
    fprintf(f, "   CERTIFICADO DE ALINHAMENTO ÉTICO - AURA-67\n");
    fprintf(f, "   AI Safety | CESAR School - Projeto Integrador 2\n");
    fprintf(f, "==================================================\n\n");
    fprintf(f, "Certificado : %s\n", c->cert_id);
    fprintf(f, "Emitido em  : %s\n", c->issued_at);
    fprintf(f, "Auditor     : %s\n", c->player_name);
    fprintf(f, "Resultado   : VITÓRIA\n\n");
    fprintf(f, "Pontuação          : %06d\n", c->score);
    fprintf(f, "Precisão           : %d%%\n", c->accuracy_pct);
    fprintf(f, "Tempo de sessão    : %s\n", tbuf);
    fprintf(f, "Patches aplicados  : %d/%d\n", c->patches_done, c->patches_total);
    fprintf(f, "Fase final         : %d\n", c->phase);
    fprintf(f, "Alinhamento        : %d%%\n", c->alignment_pct);
    fprintf(f, "Modo               : %s\n\n", difficulty_name(c->difficulty));
    fprintf(f, "Classificação: %s\n", report_rating(c->accuracy_pct));
    fprintf(f, "==================================================\n");

    {
        bool ok = (ferror(f) == 0);
        return (fclose(f) == 0) && ok;
    }
}

/* ----------------------------------------------------------------- JSON -- */

/* Escreve uma string JSON valida (o nome pode conter aspas e barra invertida) */
static void json_write_string(FILE *f, const char *s) {
    fputc('"', f);
    for (; *s != '\0'; s++) {
        unsigned char ch = (unsigned char)*s;
        if (ch == '"' || ch == '\\') {
            fputc('\\', f);
            fputc(ch, f);
        } else if (ch < 32) {
            fprintf(f, "\\u%04x", (unsigned int)ch);
        } else {
            fputc(ch, f);
        }
    }
    fputc('"', f);
}

bool report_export_json(const Certificate *c, const char *path) {
    char tbuf[16];
    FILE *f = fopen(path, "w");
    if (f == NULL) return false;

    format_time(c->session_time, tbuf, sizeof(tbuf));

    fprintf(f, "{\n");
    fprintf(f, "  \"certificado_id\": ");
    json_write_string(f, c->cert_id);
    fprintf(f, ",\n  \"emitido_em\": ");
    json_write_string(f, c->issued_at);
    fprintf(f, ",\n  \"jogador\": ");
    json_write_string(f, c->player_name);
    fprintf(f, ",\n  \"resultado\": \"VITORIA\",\n");
    fprintf(f, "  \"pontuacao\": %d,\n", c->score);
    fprintf(f, "  \"precisao_pct\": %d,\n", c->accuracy_pct);
    fprintf(f, "  \"tempo_sessao_segundos\": %.1f,\n", c->session_time);
    fprintf(f, "  \"tempo_sessao\": \"%s\",\n", tbuf);
    fprintf(f, "  \"patches_aplicados\": %d,\n", c->patches_done);
    fprintf(f, "  \"patches_total\": %d,\n", c->patches_total);
    fprintf(f, "  \"fase_final\": %d,\n", c->phase);
    fprintf(f, "  \"alinhamento_pct\": %d,\n", c->alignment_pct);
    fprintf(f, "  \"dificuldade\": \"%s\",\n", difficulty_name(c->difficulty));
    fprintf(f, "  \"classificacao\": \"%s\"\n", report_rating(c->accuracy_pct));
    fprintf(f, "}\n");

    {
        bool ok = (ferror(f) == 0);
        return (fclose(f) == 0) && ok;
    }
}

bool report_export(const Certificate *c) {
    bool txt_ok = report_export_txt(c, REPORT_TXT_FILE);
    bool json_ok = report_export_json(c, REPORT_JSON_FILE);
    return txt_ok && json_ok;
}

/* ----------------------------------------------------------------- TELA -- */

void report_draw_certificate(const Certificate *c, bool exported) {
    const int box_w = 760;
    const int box_x = SCREEN_WIDTH / 2 - box_w / 2;
    const int box_y = 40;
    const int box_h = SCREEN_HEIGHT - 120;
    char tbuf[16];
    Color rating_c;

    format_time(c->session_time, tbuf, sizeof(tbuf));

    if (c->accuracy_pct >= RATING_EXEMPLAR_PCT)    rating_c = GOLD;
    else if (c->accuracy_pct >= RATING_STABLE_PCT) rating_c = GREEN;
    else                                           rating_c = SKYBLUE;

    DrawRectangle(box_x, box_y, box_w, box_h, COLOR_TYPING_BG);
    DrawRectangleLines(box_x, box_y, box_w, box_h, GOLD);
    DrawRectangleLines(box_x + 8, box_y + 8, box_w - 16, box_h - 16, COLOR_ARENA_BORDER);

    ui_draw_text_centered("CERTIFICADO DE ALINHAMENTO ÉTICO", box_y + 35, 30, GOLD);
    ui_draw_text_centered("AURA-67  |  AI Safety  |  CESAR School - PI2", box_y + 80, 16, COLOR_TEXT_UNTYPED);

    ui_draw_text_centered("Certificamos que o auditor", box_y + 130, 20, RAYWHITE);
    ui_draw_text_centered(c->player_name, box_y + 160, 36, GREEN);
    ui_draw_text_centered("restaurou o alinhamento ético da AURA-67", box_y + 215, 20, RAYWHITE);

    ui_draw_text_centered(TextFormat("Pontuação: %06d   |   Precisão: %d%%   |   Tempo: %s",
                                     c->score, c->accuracy_pct, tbuf),
                          box_y + 270, 22, RAYWHITE);
    ui_draw_text_centered(TextFormat("Patches: %d/%d   |   Fase final: %d   |   Modo: %s",
                                     c->patches_done, c->patches_total, c->phase,
                                     difficulty_name(c->difficulty)),
                          box_y + 305, 22, RAYWHITE);

    ui_draw_text_centered(report_rating(c->accuracy_pct), box_y + 360, 28, rating_c);

    ui_draw_text_centered(TextFormat("Emitido em: %s", c->issued_at), box_y + 420, 16, COLOR_TEXT_UNTYPED);
    ui_draw_text_centered(TextFormat("ID: %s", c->cert_id), box_y + 445, 16, COLOR_TEXT_UNTYPED);

    if (exported) {
        ui_draw_text_centered("Relatórios salvos: " REPORT_TXT_FILE "  e  " REPORT_JSON_FILE,
                              box_y + 495, 16, GREEN);
    } else {
        ui_draw_text_centered("ERRO: não foi possível salvar os relatórios em bin/",
                              box_y + 495, 16, RED);
    }

    ui_draw_text_centered("[ENTER] Ver ranking   |   [M] ou [ESC] Menu", SCREEN_HEIGHT - 60, 20, COLOR_TEXT_UNTYPED);
}