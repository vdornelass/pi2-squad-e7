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

/* Adiciona uma nova pontuacao, ordena em ordem decrescente e persiste o Top 10 */
void ranking_add_score(const char *player_name, int score);

/* Carrega o ranking ordenado do arquivo local */
int ranking_load(RankingEntry entries[], int max_entries);

/* Calcula estatisticas agregadas a partir do historico de partidas (bin/matches.csv) */
void ranking_compute_stats(MatchStats *stats);

#endif /* RANKING_H */
