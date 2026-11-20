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
    char  issued_at[20];    
    char  cert_id[40];      
} Certificate;


void report_build(Certificate *c, const char *player_name, int score,
                  int accuracy_pct, float session_time,
                  int patches_done, int patches_total,
                  int phase, int difficulty, int alignment_pct);


const char *report_rating(int accuracy_pct);


bool report_export_txt(const Certificate *c, const char *path);
bool report_export_json(const Certificate *c, const char *path);
bool report_export(const Certificate *c); 


void report_draw_certificate(const Certificate *c, bool exported);

#endif 