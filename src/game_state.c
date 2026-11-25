#include "game_state.h"

void game_state_init(GameContext *ctx) {
    ctx->state = STATE_MENU;
    ctx->difficulty = DIFFICULTY_NORMAL;
    ctx->control_mode = CONTROL_WASD_ARROWS;
    ctx->volume_pct = 75;
    ctx->score = 0;
    ctx->session_time = 0.0f;
    ctx->end_screen_lock = 0.0f;
    ctx->last_phase = 0;
    ctx->phase_banner_timer = 0.0f;

    player_init(&ctx->player, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f);
    tutorial_init(&ctx->tutorial);
    boss_init(&ctx->boss, SCREEN_WIDTH / 2.0f, 130.0f, ctx->difficulty);
    bullet_mgr_init(&ctx->bullet_mgr);
    typing_engine_init(&ctx->typing_engine);
    ctx->typing_engine.control_mode = ctx->control_mode;
    ui_init(&ctx->ui);
}

void game_state_reset_combat(GameContext *ctx) {
    player_init(&ctx->player, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f);
    tutorial_init(&ctx->tutorial);
    boss_init(&ctx->boss, SCREEN_WIDTH / 2.0f, 130.0f, ctx->difficulty);
    bullet_mgr_clear(&ctx->bullet_mgr);
    typing_engine_reset(&ctx->typing_engine);
    ctx->typing_engine.control_mode = ctx->control_mode;
    ui_init(&ctx->ui);
    ctx->score = 0;
    ctx->session_time = 0.0f;
    ctx->end_screen_lock = 0.0f;
    ctx->last_phase = 0;
    ctx->phase_banner_timer = 0.0f;

    /* Descarta caracteres que ainda estao na fila do raylib */
    while (GetCharPressed() > 0) { }

    ctx->state = STATE_COMBAT;
}
