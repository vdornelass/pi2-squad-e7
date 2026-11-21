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

#define REPORT_BODY_MAX 2048

/* Hash djb2 (Dan Bernstein): simples, deterministico e suficiente para
   detectar alteracoes acidentais ou manuais no certificado. */
static unsigned long hash_djb2(const char *s, size_t len) {
    unsigned long h = 5381UL;
    size_t i;
    for (i = 0; i < len; i++) {
        h = ((h << 5) + h) + (unsigned char)s[i];
        h &= 0xFFFFFFFFUL; /* 32 bits, igual em Linux e Windows */
    }
    return h;
}

static void format_time(float seconds, char *buf, size_t size) {
    int total = (int)(seconds + 0.5f);
    if (total < 0) total = 0;
    snprintf(buf, size, "%02d:%02d", total / 60, total % 60);
}

void report_build(Certificate *c, const char *player_name, int score,
                  int accuracy_pct, float session_time,
                  int patches_done, int patches_total,
                  int phase, int difficulty, int alignment_pct,
                  int player_hp, int player_max_hp) {
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
    c->player_hp = player_hp;
    c->player_max_hp = player_max_hp;

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

/* Monta o corpo do certificado (tudo o que fica antes da linha do hash).
   O hash e calculado sobre exatamente este texto. */
static int format_txt_body(const Certificate *c, char *buf, size_t size) {
    char tbuf[16];
    format_time(c->session_time, tbuf, sizeof(tbuf));
    return snprintf(buf, size,
        "==================================================\n"
        "   CERTIFICADO DE ALINHAMENTO ÉTICO - AURA-67\n"
        "   AI Safety | CESAR School - Projeto Integrador 2\n"
        "==================================================\n\n"
        "Certificado : %s\n"
        "Emitido em  : %s\n"
        "Auditor     : %s\n"
        "Resultado   : VITÓRIA\n\n"
        "Pontuação             : %06d\n"
        "Precisão              : %d%%\n"
        "Tempo de sessão       : %s\n"
        "Patches aplicados     : %d/%d\n"
        "Fase final            : %d\n"
        "Alinhamento           : %d%%\n"
        "Integridade restante  : %d/%d\n"
        "Modo                  : %s\n\n"
        "Classificação: %s\n",
        c->cert_id, c->issued_at, c->player_name,
        c->score, c->accuracy_pct, tbuf,
        c->patches_done, c->patches_total, c->phase, c->alignment_pct,
        c->player_hp, c->player_max_hp,
        difficulty_name(c->difficulty), report_rating(c->accuracy_pct));
}

static unsigned long compute_hash(const Certificate *c) {
    char body[REPORT_BODY_MAX];
    int n = format_txt_body(c, body, sizeof(body));
    if (n < 0) return 0UL;
    if ((size_t)n >= sizeof(body)) n = (int)sizeof(body) - 1;
    return hash_djb2(body, (size_t)n);
}

bool report_export_txt(const Certificate *c, const char *path) {
    char body[REPORT_BODY_MAX];
    int n;
    /* "wb": grava so \n tambem no Windows, para o hash bater com o arquivo */
    FILE *f = fopen(path, "wb");
    if (f == NULL) return false;

    n = format_txt_body(c, body, sizeof(body));
    if (n < 0) n = 0;
    if ((size_t)n >= sizeof(body)) n = (int)sizeof(body) - 1;

    fwrite(body, 1, (size_t)n, f);
    fprintf(f, REPORT_HASH_LABEL "%08lX\n", hash_djb2(body, (size_t)n));
    fprintf(f, "==================================================\n");

    {
        bool ok = (ferror(f) == 0);
        return (fclose(f) == 0) && ok;
    }
}

int report_verify_txt(const char *path) {
    char content[REPORT_BODY_MAX + 256];
    size_t len;
    char *mark;
    unsigned long saved = 0UL;
    FILE *f = fopen(path, "rb");
    if (f == NULL) return -1;

    len = fread(content, 1, sizeof(content) - 1, f);
    fclose(f);
    content[len] = '\0';

    mark = strstr(content, "\n" REPORT_HASH_LABEL);
    if (mark == NULL) return -1;
    mark++; /* o \n final faz parte do corpo */
    if (sscanf(mark + strlen(REPORT_HASH_LABEL), "%lx", &saved) != 1) return -1;

    return (hash_djb2(content, (size_t)(mark - content)) == saved) ? 1 : 0;
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
    fprintf(f, "  \"integridade_restante\": %d,\n", c->player_hp);
    fprintf(f, "  \"integridade_maxima\": %d,\n", c->player_max_hp);
    fprintf(f, "  \"dificuldade\": \"%s\",\n", difficulty_name(c->difficulty));
    fprintf(f, "  \"classificacao\": \"%s\",\n", report_rating(c->accuracy_pct));
    fprintf(f, "  \"hash_integridade\": \"%08lX\"\n", compute_hash(c));
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
    ui_draw_text_centered(TextFormat("Integridade restante: %d/%d", c->player_hp, c->player_max_hp),
                          box_y + 340, 22, RAYWHITE);

    ui_draw_text_centered(report_rating(c->accuracy_pct), box_y + 380, 28, rating_c);

    ui_draw_text_centered(TextFormat("Emitido em: %s", c->issued_at), box_y + 420, 16, COLOR_TEXT_UNTYPED);
    ui_draw_text_centered(TextFormat("ID: %s   |   Hash: %08lX", c->cert_id, compute_hash(c)),
                          box_y + 445, 16, COLOR_TEXT_UNTYPED);

    if (exported) {
        ui_draw_text_centered("Relatórios salvos: " REPORT_TXT_FILE "  e  " REPORT_JSON_FILE,
                              box_y + 495, 16, GREEN);
    } else {
        ui_draw_text_centered("ERRO: não foi possível salvar os relatórios em bin/",
                              box_y + 495, 16, RED);
    }

    ui_draw_text_centered("[ENTER] Ver ranking   |   [M] ou [ESC] Menu", SCREEN_HEIGHT - 60, 20, COLOR_TEXT_UNTYPED);
}
