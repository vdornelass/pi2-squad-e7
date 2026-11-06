#ifndef SAVE_H
#define SAVE_H

#include <stdbool.h>

/* Cabecalho de validacao de integridade (PI2-175 - Matheus Chaves) */
#define SAVE_MAGIC_NUMBER 0x41555241 /* Representa 'AURA' em Hex */
#define SAVE_VERSION 1

/* Estrutura contendo o estado exato da partida */
typedef struct {
    int magic;               /* Validacao do arquivo */
    int version;             /* Versao do formato do save */
    int score;               /* Pontuacao atual */
    int player_hp;           /* Vidas/HP do jogador */
    int boss_hp;             /* Vida da AURA-67 */
    int boss_phase;          /* Dificuldade/Fase atual da AURA-67 */
    int boss_alignment_pct;  /* Alinhamento etico (%) */
    int phrase_index;        /* Indice da diretriz (fase de digitacao) */
} SaveData;

/* Prototipos das funcoes de persistencia */
bool save_game(const SaveData *data);
bool load_game(SaveData *data);
bool save_exists(void);

/* Prototipo da funcao de exportacao de historico e estatisticas em C */
void save_match_result(int score, int accuracy_pct, int victory);

#endif /* SAVE_H */
