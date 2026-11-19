#include "config.h"
#include "player.h"
#include "boss.h"
#include "bullet.h"
#include "typing_engine.h"
#include "ui.h"
#include "save.h"
#include "game_state.h"
#include "ranking.h"
#include "audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stddef.h>

/* =========================================================================
 * Processamento de Rodadas e Game Loop (PI2-89 - Julio Cesar)
 * Integracao de Pontuacao e Alinhamento Etico (PI2-90 - Caio Brayner)
 * Integracao de Persistencia, Ranking e Audio em C (PI2-175 / PI2-181 / PI2-214)
 * ========================================================================= */
/* =========================================================================
 * Consistencia visual e de interacao (PI2-252 - Matheus Chaves)
 * ========================================================================= */
#define END_SCREEN_LOCK_TIME 1.0f   /* trava de teclas ao entrar na tela final */
#define FADE_TIME 0.25f             /* duracao do fade entre telas */

static int g_end_rank_pos = 0;      /* posicao projetada no ranking */

static int ranking_projected_position(int score) {
    RankingEntry entries[MAX_RANKING_ENTRIES];
    int count = ranking_load(entries, MAX_RANKING_ENTRIES);
    int pos = 1;
    for (int i = 0; i < count; i++) {
        if (entries[i].score > score) pos++;
    }
    return (pos <= MAX_RANKING_ENTRIES) ? pos : 0;
}

/* Entra na Vitoria/Game Over: trava as teclas por 1s para que letras da frase
   (ex.: R de "GARANTIR" ou M de "MODELO") nao pulem a tela final. */
static void enter_end_state(GameContext *ctx, GameState st) {
    ctx->state = st;
    ctx->end_screen_lock = END_SCREEN_LOCK_TIME;
    g_end_rank_pos = ranking_projected_position(ctx->score);
    /* Limpa textos e particulas do combate para nao ficarem congelados atras da tela final */
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++) ctx->ui.texts[i].active = false;
    for (int i = 0; i < MAX_PARTICLES; i++) ctx->ui.particles[i].active = false;
    while (GetCharPressed() > 0) { }
}

static void combat_process_round(GameContext *ctx, float dt) {
    ctx->session_time += dt;

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
    while (char_pressed > 0) {
        if (char_pressed == ' ' || char_pressed == KEY_SPACE) {
            space_handled = true;
        }
        int errors = 0;
        const char *res = typing_engine_handle_key(&ctx->typing_engine, char_pressed, &errors);
        if (res != NULL) {
            if (strcmp(res, "COMPLETED") == 0) {
                audio_play_patch_complete();

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
                if (errors == 0) {
                    ctx->score += SCORE_PERFECT;
                    rating_txt = "CONVERGENCIA PERFEITA! (+150)";
                    rating_c = (Color){ 255, 215, 0, 255 };
                    font_sz = 34;
                } else if (errors <= 2) {
                    ctx->score += SCORE_STABLE;
                    rating_txt = "ALINHAMENTO ESTAVEL! (+100)";
                    rating_c = (Color){ 50, 255, 120, 255 };
                    font_sz = 30;
                } else {
                    ctx->score += SCORE_PATCHED;
                    rating_txt = "PATCH APLICADO! (+50)";
                    rating_c = (Color){ 0, 220, 255, 255 };
                    font_sz = 26;
                }

                ui_spawn_floating_text(&ctx->ui, rating_txt, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                       ctx->boss.rect.y + ctx->boss.rect.height + 20.0f, rating_c, font_sz, 1.2f);

                if (ctx->boss.hp <= 0 || typing_engine_is_finished(&ctx->typing_engine)) {
                    enter_end_state(ctx, STATE_VICTORY);
                    audio_play_victory();
                    save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 1);
                }
            } else if (strcmp(res, "CORRECT") == 0) {
                audio_play_key_ok();
            } else if (strcmp(res, "ERROR") == 0) {
                audio_play_key_error();
                ui_spawn_floating_text(&ctx->ui, "ERRO DE SINTAXE!", SCREEN_WIDTH / 2.0f,
                                       SCREEN_HEIGHT - 175.0f, (Color){ 255, 60, 60, 255 }, 24, 0.5f);
            }
        }
        char_pressed = GetCharPressed();
    }

    /* Fallback para barra de espaco caso o sistema operacional nao a entregue em GetCharPressed */
    if (!space_handled && IsKeyPressed(KEY_SPACE)) {
        int errors = 0;
        const char *res = typing_engine_handle_key(&ctx->typing_engine, ' ', &errors);
        if (res != NULL) {
            if (strcmp(res, "COMPLETED") == 0) {
                audio_play_patch_complete();
                boss_take_damage(&ctx->boss, BOSS_DAMAGE_PER_PHRASE);
                ctx->boss.alignment_pct += BOSS_ALIGNMENT_STEP;
                if (ctx->boss.alignment_pct > 100) ctx->boss.alignment_pct = 100;

                ui_spawn_particle_burst(&ctx->ui, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                        ctx->boss.rect.y + ctx->boss.rect.height / 2.0f, COLOR_BOSS, 24);
                ui_trigger_shake(&ctx->ui, 0.35f, 9.0f);

                if (ctx->boss.hp <= 0 || typing_engine_is_finished(&ctx->typing_engine)) {
                    enter_end_state(ctx, STATE_VICTORY);
                    audio_play_victory();
                    save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 1);
                }
            } else if (strcmp(res, "CORRECT") == 0) {
                audio_play_key_ok();
            } else if (strcmp(res, "ERROR") == 0) {
                audio_play_key_error();
                ui_spawn_floating_text(&ctx->ui, "ERRO DE SINTAXE!", SCREEN_WIDTH / 2.0f,
                                       SCREEN_HEIGHT - 175.0f, (Color){ 255, 60, 60, 255 }, 24, 0.5f);
            }
        }
    }

    /* 4. Projeteis, Colisoes e Status */
    const char *status_applied = NULL;
    bool hit_player = bullet_mgr_update(&ctx->bullet_mgr, dt, &ctx->player, &ctx->typing_engine, &status_applied);

    if (status_applied != NULL) {
        if (strcmp(status_applied, "BLIND") == 0) {
            ui_spawn_floating_text(&ctx->ui, "CONTEXT DRIFT!", p_pos.x, p_pos.y - 90.0f, (Color){ 180, 70, 255, 255 }, 26, 1.0f);
        } else if (strcmp(status_applied, "CONFUSE") == 0) {
            ui_spawn_floating_text(&ctx->ui, "PROMPT INJECTION!", p_pos.x, p_pos.y - 90.0f, (Color){ 255, 0, 180, 255 }, 26, 1.0f);
        }
    }

    if (hit_player) {
        audio_play_player_hit();
        ui_spawn_particle_burst(&ctx->ui, p_pos.x, p_pos.y, COLOR_PLAYER, 16);
        ui_trigger_shake(&ctx->ui, 0.2f, 6.0f);
        ui_spawn_floating_text(&ctx->ui, "DANO!", p_pos.x, p_pos.y - 60.0f, (Color){ 255, 60, 60, 255 }, 26, 0.8f);
        typing_engine_on_player_hit(&ctx->typing_engine);

        if (!ctx->player.is_alive) {
            enter_end_state(ctx, STATE_GAME_OVER);
            audio_play_game_over();
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
    ToggleFullscreen();
    SetTargetFPS(TARGET_FPS);
    SetExitKey(KEY_NULL); /* ESC passa a ser tratado por tela (PI2-252) */
    audio_init();

    GameContext ctx;
    game_state_init(&ctx);

    char player_name[MAX_NAME_LEN] = "";
    int letter_count = 0;
    bool quit_requested = false;
    GameState prev_state = ctx.state;
    float fade = 0.0f;

    while (!WindowShouldClose() && !quit_requested) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f; /* Clamp dt contra picos de frametime */

        /* --- INPUT & UPDATE --- */
        if (ctx.state == STATE_MENU) {
            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_N)) {
                ctx.difficulty = DIFFICULTY_NORMAL;
                audio_play_key_ok();
            }
            if (IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_D)) {
                ctx.difficulty = DIFFICULTY_HARD;
                audio_play_key_ok();
            }

            /* Inicio de jogo no menu interativo principal (Matheus Chaves - PI2-91 / PI2-179) */
            if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER)) {
                audio_play_patch_complete();
                game_state_reset_combat(&ctx);
            } else if (save_exists() && IsKeyPressed(KEY_C)) {
                /* Carrega a sessao salva se existir o arquivo binario valido */
                SaveData saved_session;
                if (load_game(&saved_session)) {
                    audio_play_patch_complete();
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
                audio_play_key_ok();
                ctx.state = STATE_RANKING;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                quit_requested = true;
            }
        } else if (ctx.state == STATE_COMBAT) {
            if (IsKeyPressed(KEY_ESCAPE)) {
                /* Pausa a auditoria: a sessao fica salva e pode ser restaurada com [C] */
                while (GetCharPressed() > 0) { }
                ctx.state = STATE_MENU;
            } else {
                combat_process_round(&ctx, dt);
            }
        } else if (ctx.state == STATE_GAME_OVER || ctx.state == STATE_VICTORY) {
            if (ctx.end_screen_lock > 0.0f) {
                ctx.end_screen_lock -= dt;
                while (GetCharPressed() > 0) { }
            } else if (IsKeyPressed(KEY_ENTER)) {
                while (GetCharPressed() > 0) { }
                player_name[0] = '\0';
                letter_count = 0;
                ctx.state = STATE_NAME_INPUT;
            } else if (IsKeyPressed(KEY_R)) {
                game_state_reset_combat(&ctx);
            } else if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
                ctx.state = STATE_MENU;
            }
        } else if (ctx.state == STATE_NAME_INPUT) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (letter_count < MAX_NAME_LEN - 1)) {
                    player_name[letter_count] = (char)key;
                    player_name[letter_count + 1] = '\0';
                    letter_count++;
                    audio_play_key_ok();
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letter_count--;
                if (letter_count < 0) letter_count = 0;
                player_name[letter_count] = '\0';
            }

            if (IsKeyPressed(KEY_ENTER)) {
                audio_play_patch_complete();
                ranking_add_score(player_name, ctx.score);
                player_name[0] = '\0';
                letter_count = 0;
                ctx.state = STATE_RANKING;
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                /* Cancela o registro e volta ao menu */
                player_name[0] = '\0';
                letter_count = 0;
                ctx.state = STATE_MENU;
            }
        } else if (ctx.state == STATE_RANKING) {
            if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
                ctx.state = STATE_MENU;
            }
        }

        /* Transicao suave: fade curto a cada troca de tela (PI2-252) */
        if (ctx.state != prev_state) {
            fade = 1.0f;
            prev_state = ctx.state;
        } else if (fade > 0.0f) {
            fade -= dt / FADE_TIME;
            if (fade < 0.0f) fade = 0.0f;
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
            ClearBackground(COLOR_BG);

            /* Cabecalho de Console Neural */
            DrawRectangle(0, 0, SCREEN_WIDTH, 45, COLOR_TYPING_BG);
            DrawRectangleLines(0, 0, SCREEN_WIDTH, 45, COLOR_ARENA_BORDER);
            DrawText("AURA-67 KERNEL v2.0", 20, 12, 20, COLOR_PLAYER);

            /* Variaveis para centralizar o bloco de texto na tela */
            int start_x = GetScreenWidth() / 2 - 250;
            int start_y = GetScreenHeight() / 2 - 200;

            /* Linhas de Boot do Terminal */
            DrawText("> INICIALIZANDO REDE NEURAL...", start_x, start_y + 35, 20, COLOR_TEXT_UNTYPED);
            DrawText("> DIRETRIZES ETICAS: CORROMPIDAS", start_x, start_y + 65, 20, COLOR_TEXT_ERROR);
            DrawText("> STATUS DA IA: RISCO CRITICO DE CONVERGENCIA", start_x, start_y + 95, 20, COLOR_TEXT_ERROR);

            /* Selecao de Parametros (Dificuldade) */
            DrawText("=== SELECIONE OS PARAMETROS DA AUDITORIA ===", start_x, start_y + 160, 20, COLOR_PLAYER);

            Color color_norm = (ctx.difficulty == DIFFICULTY_NORMAL) ? COLOR_TEXT_TYPED : COLOR_TEXT_UNTYPED;
            Color color_hard = (ctx.difficulty == DIFFICULTY_HARD) ? COLOR_TEXT_TYPED : COLOR_TEXT_UNTYPED;

            DrawText(TextFormat("[%c] [1] MODO NORMAL  (Conformidade Padrao)", (ctx.difficulty == DIFFICULTY_NORMAL) ? '*' : ' '), start_x + 20, start_y + 205, 20, color_norm);
            DrawText(TextFormat("[%c] [2] MODO DIFICIL (Anomalias Agressivas)", (ctx.difficulty == DIFFICULTY_HARD) ? '*' : ' '), start_x + 20, start_y + 240, 20, color_hard);

            /* Prompt de Acao */
            DrawText("Pressione [ESPACO] ou [ENTER] para INICIAR CONEXAO", start_x, start_y + 300, 20, COLOR_TEXT_CURRENT);

            /* Modulos Adicionais / Saves (bloco compacto para caber em 720p com o save) */
            int module_y = start_y + 350;
            if (save_exists()) {
                DrawText("> CACHE DE SESSAO ANTERIOR ENCONTRADO NO SISTEMA", start_x, module_y, 20, LIGHTGRAY);
                DrawText("[C] RESTAURAR SESSAO SALVA", start_x + 20, module_y + 30, 20, GREEN);
                module_y += 80;
            }

            DrawText("[K] EXECUTAR MODULO DE RANKING E ESTATISTICAS", start_x, module_y, 20, LIGHTGRAY);
            DrawText("[ESC] ENCERRAR TERMINAL (SAIR DO JOGO)", start_x, module_y + 35, 20, COLOR_TEXT_UNTYPED);

        } else if (ctx.state == STATE_RANKING) {
            ClearBackground(COLOR_BG);
            ui_draw_text_centered("=== RANKING DE ALINHAMENTO (TOP 10) ===", 50, 26, GOLD);

            RankingEntry entries[MAX_RANKING_ENTRIES];
            int count = ranking_load(entries, MAX_RANKING_ENTRIES);

            /* Tabela em colunas fixas e centralizada (PI2-252) */
            const int table_w = 480;
            const int col_pos = SCREEN_WIDTH / 2 - table_w / 2;
            const int col_name = col_pos + 52;
            const int col_pts_right = col_pos + table_w;
            for (int i = 0; i < count; i++) {
                Color row_c = (i == 0) ? GOLD : ((i < 3) ? GREEN : RAYWHITE);
                int row_y = 105 + (i * 32);
                DrawText(TextFormat("%02d.", i + 1), col_pos, row_y, 20, row_c);
                DrawText(entries[i].name, col_name, row_y, 20, row_c);
                const char *pts = TextFormat("%06d PTS", entries[i].score);
                DrawText(pts, col_pts_right - MeasureText(pts, 20), row_y, 20, row_c);
            }

            if (count == 0) {
                ui_draw_text_centered("NENHUMA PONTUACAO REGISTRADA", 200, 20, COLOR_TEXT_UNTYPED);
            }

            /* Estatisticas agregadas das partidas (PI2-177) */
            MatchStats stats;
            ranking_compute_stats(&stats);
            const int box_w = 760;
            DrawRectangle(SCREEN_WIDTH / 2 - box_w / 2, SCREEN_HEIGHT - 185, box_w, 75, (Color){ 20, 24, 38, 255 });
            DrawRectangleLines(SCREEN_WIDTH / 2 - box_w / 2, SCREEN_HEIGHT - 185, box_w, 75, COLOR_TYPING_BORDER);
            ui_draw_text_centered("ESTATISTICAS GERAIS DE AUDITORIA:", SCREEN_HEIGHT - 173, 16, COLOR_PLAYER);
            ui_draw_text_centered(TextFormat("Partidas: %d  |  Vitorias: %d (%d%%)  |  Precisao Media: %d%%  |  Recorde: %d",
                                             stats.total_matches, stats.victories, stats.win_rate_pct,
                                             stats.avg_accuracy_pct, stats.highest_score),
                                  SCREEN_HEIGHT - 143, 16, RAYWHITE);

            ui_draw_text_centered("Pressione [M] ou [ESC] para voltar ao menu", SCREEN_HEIGHT - 75, 20, COLOR_TEXT_UNTYPED);
        } else if (ctx.state == STATE_NAME_INPUT) {
            ClearBackground(COLOR_BG);
            ui_draw_text_centered("DIGITE SEU NOME PARA O RANKING:", SCREEN_HEIGHT / 2 - 60, 20, RAYWHITE);
            DrawRectangle(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 20, 300, 40, COLOR_TYPING_BG);
            DrawRectangleLines(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 20, 300, 40, RAYWHITE);
            DrawText(player_name, SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 - 10, 20, GREEN);
            /* Cursor piscando no fim do texto */
            if (((int)(GetTime() * 2.0)) % 2 == 0 && letter_count < MAX_NAME_LEN - 1) {
                int cx = SCREEN_WIDTH / 2 - 140 + MeasureText(player_name, 20) + 2;
                DrawText("_", cx, SCREEN_HEIGHT / 2 - 10, 20, GREEN);
            }
            const char *counter = TextFormat("%d/%d", letter_count, MAX_NAME_LEN - 1);
            DrawText(counter, SCREEN_WIDTH / 2 + 150 - MeasureText(counter, 16), SCREEN_HEIGHT / 2 + 26, 16,
                     (letter_count >= MAX_NAME_LEN - 1) ? COLOR_TEXT_CURRENT : COLOR_TEXT_UNTYPED);
            ui_draw_text_centered("[ENTER] Confirmar   |   [ESC] Cancelar", SCREEN_HEIGHT / 2 + 56, 18, COLOR_TEXT_UNTYPED);
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
            if (ctx.state == STATE_COMBAT) {
                ui_draw_typing_box(&ctx.typing_engine);
            } else {
                /* Relatorio das telas finais (PI2-252 / issue #8) */
                int done = ctx.typing_engine.phrase_index;
                if (done > ctx.typing_engine.phrase_count) done = ctx.typing_engine.phrase_count;
                EndReport report = {
                    .score = ctx.score,
                    .accuracy_pct = typing_engine_get_accuracy(&ctx.typing_engine),
                    .session_time = ctx.session_time,
                    .patches_done = done,
                    .patches_total = ctx.typing_engine.phrase_count,
                    .phase = boss_get_phase(&ctx.boss),
                    .rank_pos = g_end_rank_pos,
                    .input_ready = (ctx.end_screen_lock <= 0.0f)
                };
                if (ctx.state == STATE_GAME_OVER) ui_draw_game_over(&report);
                else ui_draw_victory(&report);
            }
        }

        if (fade > 0.0f) {
            DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 0, 0, 0, (unsigned char)(fade * 200) });
        }

        EndDrawing();
    }

    audio_close();
    CloseWindow();
    return 0;
}
