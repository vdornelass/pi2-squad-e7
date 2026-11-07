#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "config.h"
#include "player.h"
#include "typing_engine.h"
#include "ui.h"

/* Modo Tutorial Guiado de AI Safety - atalho [T] no menu (PI2-215 / IHC) */

/* Frase de teste digitada no passo 2 (maiusculas, sem acentos, como as diretrizes) */
#define TUTORIAL_PHRASE "IA SEGURA PROTEGE AS PESSOAS"

#define TUTORIAL_MAX_ORBS 3
#define TUTORIAL_ORB_RADIUS 12.0f
#define TUTORIAL_KEY_COUNT 4

/* Passos do treino, em ordem */
typedef enum {
    TUTORIAL_STEP_MOVE,  /* Passo 1: movimentacao e esquiva (WASD / setas) */
    TUTORIAL_STEP_TYPE,  /* Passo 2: digitacao de um patch de teste */
    TUTORIAL_STEP_DONE   /* Treino concluido: ir ao combate ou voltar ao menu */
} TutorialStep;

/* Esfera de treino: simula um projetil, mas NAO causa dano */
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float hit_cooldown;  /* Evita repetir o aviso "SEM DANO" a cada frame */
} TrainingOrb;

/* Estado completo do tutorial (independente do combate real: nao altera score, save nem ranking) */
typedef struct {
    TutorialStep step;
    bool key_used[TUTORIAL_KEY_COUNT];  /* Ordem: W, A, S, D (setas contam igual) */
    Player player;
    TypingEngine typing_engine;
    UIManager ui;
    TrainingOrb orbs[TUTORIAL_MAX_ORBS];
} Tutorial;

/* Zera o tutorial: volta ao passo 1, posiciona jogador e esferas, prepara a frase de teste */
void tutorial_init(Tutorial *t);

/* Atualiza um frame do tutorial (le o teclado: movimento e digitacao) */
void tutorial_update(Tutorial *t, float dt);

/* Retorna true quando o jogador concluiu os dois passos */
bool tutorial_is_complete(const Tutorial *t);

/* Desenha a tela inteira do tutorial (arena, instrucoes, HUD e caixa de digitacao) */
void tutorial_draw(const Tutorial *t);

#endif /* TUTORIAL_H */
