#ifndef RANKING_H
#define RANKING_H

#include <stdbool.h>

#define RANKING_FILE "bin/ranking.txt"
#define MAX_RANKING_ENTRIES 10
#define MAX_NAME_LEN 16

typedef struct {
    char name[MAX_NAME_LEN];
    int score;
} RankingEntry;

typedef struct {
    int total_matches;
    int victories;
    int win_rate_pct;
    int avg_accuracy_pct;
    int highest_score;
} MatchStats;

/* Verifica se um nome de jogador ja esta registrado no ranking (case-insensitive) */
bool ranking_name_exists(const char *player_name);

/* Adiciona uma nova pontuacao, ordena em ordem decrescente e persiste o Top 10.
   Retorna a posicao no Top 10 (1..10), 0 se a pontuacao ficou fora do Top 10
   ou -1 se o arquivo do ranking nao pode ser gravado. */
int ranking_add_score(const char *player_name, int score);

/* Nome como ele e gravado no ranking (espacos viram _) */
const char *ranking_clean_name(const char *player_name, char out[MAX_NAME_LEN]);

/* Carrega o ranking ordenado do arquivo local */
int ranking_load(RankingEntry entries[], int max_entries);

/* Calcula estatisticas agregadas a partir do historico de partidas (bin/matches.csv) */
void ranking_compute_stats(MatchStats *stats);

#endif /* RANKING_H */
