#include "game_state.h"

void game_state_init(GameContext *ctx) {
    ctx->state = STATE_MENU;
    ctx->difficulty = DIFFICULTY_NORMAL;
    ctx->score = 0;

    player_init(&ctx->player, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f);
    boss_init(&ctx->boss, SCREEN_WIDTH / 2.0f, 130.0f, ctx->difficulty);
    bullet_mgr_init(&ctx->bullet_mgr);
    typing_engine_init(&ctx->typing_engine);
    ui_init(&ctx->ui);
}

void game_state_reset_combat(GameContext *ctx) {
    player_init(&ctx->player, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f);
    boss_init(&ctx->boss, SCREEN_WIDTH / 2.0f, 130.0f, ctx->difficulty);
    bullet_mgr_clear(&ctx->bullet_mgr);
    typing_engine_reset(&ctx->typing_engine);
    ui_init(&ctx->ui);
    ctx->score = 0;

    /* Descarta caracteres que ainda estao na fila do raylib (ex.: o 'R' ou o
       ESPACO usado para iniciar). Sem isso eles viram "erro de sintaxe" no
       primeiro frame da nova partida. */
    while (GetCharPressed() > 0) { }

    ctx->state = STATE_COMBAT;
}
