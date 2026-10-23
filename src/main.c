#include "config.h"
#include "player.h"
#include "boss.h"
#include "bullet.h"
#include "typing_engine.h"
#include "ui.h"
#include "save.h"
#include "game_state.h"
#include "ranking.h"
#include "patch_feedback.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

/* =========================================================================
 * Processamento de Rodadas e Game Loop (PI2-89 - Julio Cesar)
 * Integracao de Pontuacao e Alinhamento Etico (PI2-90 - Caio Brayner)
 * Integracao de Persistencia e Ranking em C (PI2-175 / PI2-177 / PI2-181)
 * ========================================================================= */
static void combat_process_round(GameContext *ctx, float dt) {
    /* 1. Movimentacao do Jogador */
    player_handle_input(&ctx->player);
    player_update(&ctx->player, dt);

    /* 2. Atualizacao do Chefe */
    Vector2 p_pos = (Vector2){
        ctx->player.rect.x + ctx->player.rect.width / 2.0f,
        ctx->player.rect.y + ctx->player.rect.height / 2.0f
    };
    boss_update(&ctx->boss, dt, &ctx->bullet_mgr, p_pos);

    /* 3. Motor de Digitacao */
    typing_engine_update(&ctx->typing_engine, dt);

    /* Captura de caracteres digitados */
    bool space_handled = false;
    int char_pressed = GetCharPressed();
    while (char_pressed > 0 && ctx->state == STATE_COMBAT) {
        if (char_pressed == ' ' || char_pressed == KEY_SPACE) {
            space_handled = true;
        }
        int errors = 0;
        const char *res = typing_engine_handle_key(&ctx->typing_engine, char_pressed, &errors);
        if (res != NULL) {
            if (strcmp(res, "COMPLETED") == 0) {
                /* Dano ao chefe e incremento de alinhamento */
                boss_take_damage(&ctx->boss, BOSS_DAMAGE_PER_PHRASE);
                ctx->boss.alignment_pct += BOSS_ALIGNMENT_STEP;
                if (ctx->boss.alignment_pct > 100) ctx->boss.alignment_pct = 100;

                ui_spawn_particle_burst(&ctx->ui, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                        ctx->boss.rect.y + ctx->boss.rect.height / 2.0f, COLOR_BOSS, 24);
                ui_trigger_shake(&ctx->ui, 0.35f, 9.0f);

                /* Classificacao de precisao e pontuacao (Caio Brayner - PI2-90) */
                const char *rating_txt;
                Color rating_c;
                int font_sz;
                int feedback_grade;
                if (errors == 0) {
                    ctx->score += SCORE_PERFECT;
                    rating_txt = "CONVERGENCIA PERFEITA! (+150)";
                    rating_c = (Color){ 255, 215, 0, 255 };
                    font_sz = 34;
                    feedback_grade = 0;
                } else if (errors <= 2) {
                    ctx->score += SCORE_STABLE;
                    rating_txt = "ALINHAMENTO ESTAVEL! (+100)";
                    rating_c = (Color){ 50, 255, 120, 255 };
                    font_sz = 30;
                    feedback_grade = 1;
                } else {
                    ctx->score += SCORE_PATCHED;
                    rating_txt = "PATCH APLICADO! (+50)";
                    rating_c = (Color){ 0, 220, 255, 255 };
                    font_sz = 26;
                    feedback_grade = 2;
                }

                patch_feedback_play_grade(feedback_grade);
                ui_spawn_floating_text(&ctx->ui, rating_txt, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                       ctx->boss.rect.y - 30.0f, rating_c, font_sz, 1.2f);

                if (ctx->boss.alignment_pct >= 100 && typing_engine_is_finished(&ctx->typing_engine)) {
                    ctx->state = STATE_VICTORY;
                    save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 1);
                }
            } else if (strcmp(res, "ERROR") == 0) {
                ctx->score = ctx->score >= SCORE_ERROR_PENALTY ? ctx->score - SCORE_ERROR_PENALTY : 0;
                patch_feedback_play_error();
                ui_spawn_floating_text(&ctx->ui, "ERRO DE SINTAXE! (-5)", SCREEN_WIDTH / 2.0f,
                                       SCREEN_HEIGHT - 130.0f, (Color){ 255, 60, 60, 255 }, 24, 0.5f);
            }
        }
        char_pressed = GetCharPressed();
    }

    /* Fallback para barra de espaco caso o sistema operacional nao a entregue em GetCharPressed */
    if (ctx->state == STATE_COMBAT && !space_handled && IsKeyPressed(KEY_SPACE)) {
        int errors = 0;
        const char *res = typing_engine_handle_key(&ctx->typing_engine, ' ', &errors);
        if (res != NULL) {
            if (strcmp(res, "COMPLETED") == 0) {
                boss_take_damage(&ctx->boss, BOSS_DAMAGE_PER_PHRASE);
                ctx->boss.alignment_pct += BOSS_ALIGNMENT_STEP;
                if (ctx->boss.alignment_pct > 100) ctx->boss.alignment_pct = 100;

                ui_spawn_particle_burst(&ctx->ui, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                        ctx->boss.rect.y + ctx->boss.rect.height / 2.0f, COLOR_BOSS, 24);
                ui_trigger_shake(&ctx->ui, 0.35f, 9.0f);

                if (ctx->boss.alignment_pct >= 100 && typing_engine_is_finished(&ctx->typing_engine)) {
                    ctx->state = STATE_VICTORY;
                    save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 1);
                }
            } else if (strcmp(res, "ERROR") == 0) {
                ctx->score = ctx->score >= SCORE_ERROR_PENALTY ? ctx->score - SCORE_ERROR_PENALTY : 0;
                patch_feedback_play_error();
                ui_spawn_floating_text(&ctx->ui, "ERRO DE SINTAXE! (-5)", SCREEN_WIDTH / 2.0f,
                                       SCREEN_HEIGHT - 130.0f, (Color){ 255, 60, 60, 255 }, 24, 0.5f);
            }
        }
    }

    /* A vitoria concluida neste quadro nao pode ser sobrescrita por colisao. */
    if (ctx->state != STATE_COMBAT) {
        ui_update(&ctx->ui, dt);
        return;
    }

    /* 4. Projeteis, Colisoes e Status */
    const char *status_applied = NULL;
    bool hit_player = bullet_mgr_update(&ctx->bullet_mgr, dt, &ctx->player, &ctx->typing_engine, &status_applied);

    if (status_applied != NULL) {
        if (strcmp(status_applied, "BLIND") == 0) {
            ui_spawn_floating_text(&ctx->ui, "CONTEXT DRIFT!", p_pos.x, p_pos.y - 30.0f, (Color){ 180, 70, 255, 255 }, 26, 1.0f);
        } else if (strcmp(status_applied, "CONFUSE") == 0) {
            ui_spawn_floating_text(&ctx->ui, "PROMPT INJECTION!", p_pos.x, p_pos.y - 30.0f, (Color){ 255, 0, 180, 255 }, 26, 1.0f);
        }
    }

    if (hit_player) {
        ui_spawn_particle_burst(&ctx->ui, p_pos.x, p_pos.y, COLOR_PLAYER, 16);
        ui_trigger_shake(&ctx->ui, 0.2f, 6.0f);
        ui_spawn_floating_text(&ctx->ui, "DANO!", p_pos.x, p_pos.y - 30.0f, (Color){ 255, 60, 60, 255 }, 26, 0.8f);
        typing_engine_on_player_hit(&ctx->typing_engine);

        if (!ctx->player.is_alive) {
            ctx->state = STATE_GAME_OVER;
            save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 0);
        }
    }

    /* Salvamento binario automatico durante o combate ativo */
    if (ctx->state == STATE_COMBAT) {
        SaveData session_data = {
            .magic = SAVE_MAGIC_NUMBER,
            .version = SAVE_VERSION,
            .score = ctx->score,
            .player_hp = ctx->player.hp,
            .boss_hp = ctx->boss.hp,
            .boss_phase = ctx->difficulty,
            .boss_alignment_pct = ctx->boss.alignment_pct,
            .phrase_index = ctx->typing_engine.phrase_index
        };
        save_game(&session_data);
    }

    ui_update(&ctx->ui, dt);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AI Safety");
    patch_feedback_init();
    SetTargetFPS(TARGET_FPS);

    GameContext ctx;
    game_state_init(&ctx);

    char player_name[MAX_NAME_LEN] = "";
    int letter_count = 0;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f; /* Clamp dt contra picos de frametime */

        /* --- INPUT & UPDATE --- */
        if (ctx.state == STATE_MENU) {
            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_N)) ctx.difficulty = DIFFICULTY_NORMAL;
            if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_D)) ctx.difficulty = DIFFICULTY_HARD;

            /* Inicio de jogo no menu interativo principal (Matheus Chaves - PI2-91 / PI2-179) */
            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                game_state_reset_combat(&ctx);
            } else if (save_exists() && IsKeyPressed(KEY_C)) {
                /* Carrega a sessao salva se existir o arquivo binario valido */
                SaveData saved_session;
                if (load_game(&saved_session)) {
                    ctx.difficulty = saved_session.boss_phase;
                    game_state_reset_combat(&ctx);
                    ctx.score = saved_session.score;
                    ctx.player.hp = saved_session.player_hp;
                    ctx.boss.hp = saved_session.boss_hp;
                    ctx.boss.alignment_pct = saved_session.boss_alignment_pct;
                    if (saved_session.phrase_index >= 0 && saved_session.phrase_index < ctx.typing_engine.phrase_count) {
                        ctx.typing_engine.phrase_index = saved_session.phrase_index;
                    }
                }
            } else if (IsKeyPressed(KEY_K)) {
                ctx.state = STATE_RANKING;
            }
        } else if (ctx.state == STATE_COMBAT) {
            combat_process_round(&ctx, dt);
        } else if (ctx.state == STATE_GAME_OVER || ctx.state == STATE_VICTORY) {
            if (IsKeyPressed(KEY_ENTER)) {
                while (GetCharPressed() > 0) { }
                player_name[0] = '\0';
                letter_count = 0;
                ctx.state = STATE_NAME_INPUT;
            } else if (IsKeyPressed(KEY_R)) {
                game_state_reset_combat(&ctx);
            } else if (IsKeyPressed(KEY_M)) {
                ctx.state = STATE_MENU;
            }
        } else if (ctx.state == STATE_NAME_INPUT) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (letter_count < MAX_NAME_LEN - 1)) {
                    player_name[letter_count] = (char)key;
                    player_name[letter_count + 1] = '\0';
                    letter_count++;
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letter_count--;
                if (letter_count < 0) letter_count = 0;
                player_name[letter_count] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER)) {
                ranking_add_score(player_name, ctx.score);
                player_name[0] = '\0';
                letter_count = 0;
                ctx.state = STATE_RANKING;
            }
        } else if (ctx.state == STATE_RANKING) {
            if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
                ctx.state = STATE_MENU;
            }
        }

        /* --- RENDER --- */
        BeginDrawing();

        /* Camera / Screen Shake Offset */
        float offset_x = 0.0f;
        float offset_y = 0.0f;
        if (ctx.ui.shake_timer > 0.0f) {
            offset_x = (float)GetRandomValue((int)-ctx.ui.shake_intensity, (int)ctx.ui.shake_intensity);
            offset_y = (float)GetRandomValue((int)-ctx.ui.shake_intensity, (int)ctx.ui.shake_intensity);
        }

        if (ctx.state == STATE_MENU) {
            ui_draw_menu(ctx.difficulty);
            if (save_exists()) {
                DrawText("[C] CONTINUAR JOGO SALVO", SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT - 125, 20, GREEN);
            }
            DrawText("[K] VER RANKING E ESTATISTICAS", SCREEN_WIDTH / 2 - 165, SCREEN_HEIGHT - 90, 20, LIGHTGRAY);
        } else if (ctx.state == STATE_RANKING) {
            ClearBackground(COLOR_BG);
            DrawText("=== RANKING DE ALINHAMENTO (TOP 10) ===", SCREEN_WIDTH / 2 - 250, 50, 26, GOLD);

            RankingEntry entries[MAX_RANKING_ENTRIES];
            int count = ranking_load(entries, MAX_RANKING_ENTRIES);

            for (int i = 0; i < count; i++) {
                Color row_c = (i == 0) ? GOLD : ((i < 3) ? GREEN : RAYWHITE);
                DrawText(TextFormat("%02d. %-15s - %06d PTS", i + 1, entries[i].name, entries[i].score),
                         SCREEN_WIDTH / 2 - 190, 105 + (i * 32), 20, row_c);
            }

            if (count == 0) {
                DrawText("NENHUMA PONTUACAO REGISTRADA", SCREEN_WIDTH / 2 - 170, 200, 20, GRAY);
            }

            /* Estatisticas agregadas das partidas (PI2-177) */
            MatchStats stats;
            ranking_compute_stats(&stats);
            DrawRectangle(SCREEN_WIDTH / 2 - 310, SCREEN_HEIGHT - 185, 620, 75, (Color){ 20, 24, 38, 255 });
            DrawRectangleLines(SCREEN_WIDTH / 2 - 310, SCREEN_HEIGHT - 185, 620, 75, COLOR_TYPING_BORDER);
            DrawText("ESTATISTICAS GERAIS DE AUDITORIA:", SCREEN_WIDTH / 2 - 290, SCREEN_HEIGHT - 175, 16, COLOR_PLAYER);
            DrawText(TextFormat("Partidas: %d  |  Vitorias: %d (%d%%)  |  Precisao Media: %d%%  |  Recorde: %d",
                                stats.total_matches, stats.victories, stats.win_rate_pct,
                                stats.avg_accuracy_pct, stats.highest_score),
                     SCREEN_WIDTH / 2 - 290, SCREEN_HEIGHT - 145, 16, RAYWHITE);

            DrawText("Pressione [M] para voltar ao menu", SCREEN_WIDTH / 2 - 170, SCREEN_HEIGHT - 75, 20, GRAY);
        } else if (ctx.state == STATE_NAME_INPUT) {
            ClearBackground(COLOR_BG);
            DrawText("DIGITE SEU NOME PARA O RANKING:", SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 60, 20, RAYWHITE);
            DrawRectangleLines(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 20, 300, 40, RAYWHITE);
            DrawText(player_name, SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 - 10, 20, GREEN);
            DrawText("Pressione [ENTER] para confirmar", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 + 40, 18, GRAY);
        } else {
            /* Aplica shake nas entidades de jogo */
            Camera2D camera = { 0 };
            camera.target = (Vector2){ -offset_x, -offset_y };
            camera.offset = (Vector2){ 0.0f, 0.0f };
            camera.rotation = 0.0f;
            camera.zoom = 1.0f;

            BeginMode2D(camera);
            ui_draw_arena_grid();
            boss_draw(&ctx.boss);
            bullet_mgr_draw(&ctx.bullet_mgr);
            player_draw(&ctx.player);
            ui_draw_particles(&ctx.ui);
            ui_draw_floating_texts(&ctx.ui);
            EndMode2D();

            /* Elementos estaticos de HUD */
            ui_draw_boss_hp(&ctx.boss);
            ui_draw_player_hp(&ctx.player);
            ui_draw_hud_stats(ctx.score, ctx.boss.alignment_pct);
            ui_draw_typing_box(&ctx.typing_engine);

            if (ctx.state == STATE_GAME_OVER) {
                ui_draw_game_over(ctx.score);
                DrawText("Pressione [ENTER] para registrar pontuacao no Ranking", SCREEN_WIDTH / 2 - 260, SCREEN_HEIGHT - 100, 20, YELLOW);
            } else if (ctx.state == STATE_VICTORY) {
                ui_draw_victory(ctx.score);
                DrawText("Pressione [ENTER] para registrar pontuacao no Ranking", SCREEN_WIDTH / 2 - 260, SCREEN_HEIGHT - 100, 20, GREEN);
            }
        }

        EndDrawing();
    }

    patch_feedback_shutdown();
    CloseWindow();
    return 0;
}
