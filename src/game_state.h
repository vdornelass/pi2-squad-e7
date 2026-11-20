#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "config.h"
#include "player.h"
#include "boss.h"
#include "bullet.h"
#include "typing_engine.h"
#include "ui.h"
#include "tutorial.h"

typedef enum {
    STATE_MENU,
    STATE_TUTORIAL,
    STATE_COMBAT,
    STATE_GAME_OVER,
    STATE_VICTORY,
    STATE_NAME_INPUT,
    STATE_RANKING
} GameState;

/* Contexto central: agrupa todos os modulos do jogo (PI2-178 - Caio Brayner) */
typedef struct {
    GameState state;
    int difficulty;
    int score;

    /* Consistencia visual das telas finais (PI2-252 - Matheus Chaves) */
    float session_time;      /* Tempo de sessao do combate, em segundos */
    float end_screen_lock;   /* Ignora teclas logo ao entrar na Vitoria/Game Over */

    Player player;
    Boss boss;
    Tutorial tutorial;
    BulletManager bullet_mgr;
    TypingEngine typing_engine;
    UIManager ui;
} GameContext;

/* Inicializa todos os modulos, zera o score e comeca no menu */
void game_state_init(GameContext *ctx);

/* Reinicia uma partida limpa (usa ctx->difficulty) e muda para STATE_COMBAT */
void game_state_reset_combat(GameContext *ctx);

#endif /* GAME_STATE_H */
