#ifndef REPORT_H
#define REPORT_H

#include <stdbool.h>
#include "ranking.h" 



#define REPORT_TXT_FILE  "bin/certificado.txt"
#define REPORT_JSON_FILE "bin/certificado.json"

typedef struct {
    char  player_name[MAX_NAME_LEN];
    int   score;
    int   accuracy_pct;
    float session_time;     /* segundos */
    int   patches_done;
    int   patches_total;
    int   phase;            
    int   difficulty;
    int   alignment_pct;
    int   player_hp;        /* integridade restante do operador (vidas) */
    int   player_max_hp;
    char  issued_at[20];    
    char  cert_id[40];      
} Certificate;

#define REPORT_HASH_LABEL "Hash de integridade: "


void report_build(Certificate *c, const char *player_name, int score,
                  int accuracy_pct, float session_time,
                  int patches_done, int patches_total,
                  int phase, int difficulty, int alignment_pct,
                  int player_hp, int player_max_hp);


const char *report_rating(int accuracy_pct);


bool report_export_txt(const Certificate *c, const char *path);
bool report_export_json(const Certificate *c, const char *path);
bool report_export(const Certificate *c); 

/* Confere o hash de integridade de um certificado .txt ja gerado.
   Retorna 1 se o arquivo esta integro, 0 se foi alterado e -1 se nao foi
   possivel ler o arquivo ou achar a linha do hash. */
int report_verify_txt(const char *path);


void report_draw_certificate(const Certificate *c, bool exported);

#endif 