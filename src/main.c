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
#include "icon_data.h"
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
static void combat_process_round(GameContext *ctx, float dt, Vector2 mouse_arena_pos) {
    /* 1. Movimentacao do Jogador conforme o esquema escolhido nas Configuracoes */
    ctx->typing_engine.control_mode = ctx->control_mode;
    player_handle_input_ex(&ctx->player, ctx->control_mode, mouse_arena_pos);
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
    bool should_save = false;
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
                should_save = true;

                /* Dano ao chefe e incremento de alinhamento */
                boss_take_damage(&ctx->boss, BOSS_DAMAGE_PER_PHRASE);
                ctx->boss.alignment_pct += BOSS_ALIGNMENT_STEP;
                if (ctx->boss.alignment_pct > 100) ctx->boss.alignment_pct = 100;

                ui_spawn_particle_burst(&ctx->ui, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                        ctx->boss.rect.y + ctx->boss.rect.height / 2.0f, (Color){ 255, 255, 100, 255 }, 24);
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
                                       ctx->boss.rect.y - 30.0f, rating_c, font_sz, 1.2f);

                if (ctx->boss.hp <= 0 || typing_engine_is_finished(&ctx->typing_engine)) {
                    ctx->state = STATE_VICTORY;
                    audio_play_victory();
                    save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 1);
                }
            } else if (strcmp(res, "CORRECT") == 0) {
                audio_play_key_ok();
            } else if (strcmp(res, "ERROR") == 0) {
                audio_play_key_error();
                ui_spawn_floating_text(&ctx->ui, "ERRO DE SINTAXE!", SCREEN_WIDTH / 2.0f,
                                       SCREEN_HEIGHT - 130.0f, (Color){ 255, 60, 60, 255 }, 24, 0.5f);
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
                should_save = true;
                boss_take_damage(&ctx->boss, BOSS_DAMAGE_PER_PHRASE);
                ctx->boss.alignment_pct += BOSS_ALIGNMENT_STEP;
                if (ctx->boss.alignment_pct > 100) ctx->boss.alignment_pct = 100;

                ui_spawn_particle_burst(&ctx->ui, ctx->boss.rect.x + ctx->boss.rect.width / 2.0f,
                                        ctx->boss.rect.y + ctx->boss.rect.height / 2.0f, (Color){ 255, 255, 100, 255 }, 24);
                ui_trigger_shake(&ctx->ui, 0.35f, 9.0f);

                if (ctx->boss.hp <= 0 || typing_engine_is_finished(&ctx->typing_engine)) {
                    ctx->state = STATE_VICTORY;
                    audio_play_victory();
                    save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 1);
                }
            } else if (strcmp(res, "CORRECT") == 0) {
                audio_play_key_ok();
            } else if (strcmp(res, "ERROR") == 0) {
                audio_play_key_error();
                ui_spawn_floating_text(&ctx->ui, "ERRO DE SINTAXE!", SCREEN_WIDTH / 2.0f,
                                       SCREEN_HEIGHT - 130.0f, (Color){ 255, 60, 60, 255 }, 24, 0.5f);
            }
        }
    }

    /* 4. Projeteis, Colisoes e Status */
    const char *status_applied = NULL;
    bool hit_player = bullet_mgr_update(&ctx->bullet_mgr, dt, &ctx->player, &ctx->typing_engine, &status_applied);

    if (status_applied != NULL) {
        if (strcmp(status_applied, "BLIND") == 0) {
            audio_play_key_ok();
            ui_spawn_floating_text(&ctx->ui, "CONTEXT DRIFT!", p_pos.x, p_pos.y - 30.0f, (Color){ 180, 70, 255, 255 }, 26, 1.0f);
        } else if (strcmp(status_applied, "CONFUSE") == 0) {
            audio_play_key_ok();
            ui_spawn_floating_text(&ctx->ui, "PROMPT INJECTION!", p_pos.x, p_pos.y - 30.0f, (Color){ 255, 0, 180, 255 }, 26, 1.0f);
        }
    }

    if (hit_player) {
        audio_play_player_hit();
        ui_spawn_particle_burst(&ctx->ui, p_pos.x, p_pos.y, COLOR_PLAYER, 16);
        ui_trigger_shake(&ctx->ui, 0.2f, 6.0f);
        ui_spawn_floating_text(&ctx->ui, "DANO!", p_pos.x, p_pos.y - 30.0f, (Color){ 255, 60, 60, 255 }, 26, 0.8f);
        typing_engine_on_player_hit(&ctx->typing_engine);

        if (!ctx->player.is_alive) {
            ctx->state = STATE_GAME_OVER;
            audio_play_game_over();
            save_match_result(ctx->score, typing_engine_get_accuracy(&ctx->typing_engine), 0);
        }
    }

    /* Salvamento binario automatico ao avancar diretriz ou sofrer dano */
    if (ctx->state == STATE_COMBAT && (should_save || hit_player)) {
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

/* Desenha texto com sombra forte estilo God of War */
static void draw_gow_text(const char *text, int x, int y, int font_size, Color main_color, Color shadow_color, int shadow_offset) {
    DrawText(text, x + shadow_offset, y + shadow_offset, font_size, shadow_color);
    DrawText(text, x, y, font_size, main_color);
}

static const char *get_control_mode_name(int control_mode) {
    if (control_mode == CONTROL_ARROWS_ONLY) {
        return "SETAS DIRECIONAIS (LETRAS LIVRES)";
    }
    if (control_mode == CONTROL_MOUSE) {
        return "MOUSE (SEGUIR CURSOR)";
    }
    return "WASD + SETAS (CLASSICO)";
}

/* Renderiza o fundo atmosferico, retrato AURA-67 e banner estilo God of War */
static void draw_gow_backdrop_and_banner(Texture2D aura_tex, float menu_timer) {
    DrawRectangleGradientV(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
                           (Color){ 18, 12, 18, 255 }, (Color){ 8, 8, 14, 255 });

    float pulse = sinf(menu_timer * 2.2f);
    float head_cx = 935.0f;
    float head_cy = 370.0f;

    DrawCircleGradient((int)(head_cx - 70.0f), (int)head_cy, 340.0f + pulse * 18.0f,
                       (Color){ 165, 20, 35, 95 }, (Color){ 12, 12, 20, 0 });
    DrawCircleGradient((int)(head_cx + 85.0f), (int)head_cy, 330.0f - pulse * 15.0f,
                       (Color){ 20, 160, 75, 85 }, (Color){ 12, 12, 20, 0 });

    unsigned char bolt_alpha = (unsigned char)(35.0f + fabsf(sinf(menu_timer * 3.7f)) * 75.0f);
    Color bolt_c = (Color){ 220, 230, 255, bolt_alpha };
    DrawLineEx((Vector2){ 420.0f, 0.0f }, (Vector2){ 445.0f, 48.0f }, 2.0f, bolt_c);
    DrawLineEx((Vector2){ 445.0f, 48.0f }, (Vector2){ 430.0f, 85.0f }, 1.5f, bolt_c);
    DrawLineEx((Vector2){ 445.0f, 48.0f }, (Vector2){ 475.0f, 92.0f }, 1.5f, bolt_c);

    for (int i = 0; i < 28; i++) {
        float seed = (float)(i * 97 + 31);
        float px = fmodf(seed * 43.0f + sinf(menu_timer * 1.3f + (float)i) * 35.0f, (float)SCREEN_WIDTH);
        float py = SCREEN_HEIGHT - fmodf(menu_timer * (38.0f + (float)(i % 5) * 14.0f) + seed * 19.0f, (float)SCREEN_HEIGHT);
        Color ember_c = (i % 3 == 0) ? (Color){ 50, 255, 130, 150 } : (Color){ 255, 70, 50, 170 };
        float r = (i % 4 == 0) ? 3.0f : 2.0f;
        DrawCircleV((Vector2){ px, py }, r, ember_c);
    }

    float hover_y = sinf(menu_timer * 1.6f) * 8.0f;
    float art_size = 490.0f;
    Rectangle src_rec = (Rectangle){ 0.0f, 0.0f, (float)aura_tex.width, (float)aura_tex.height };
    Rectangle shadow_dst = (Rectangle){ head_cx - art_size / 2.0f + 12.0f, head_cy - art_size / 2.0f + hover_y + 14.0f, art_size, art_size };
    Rectangle art_dst = (Rectangle){ head_cx - art_size / 2.0f, head_cy - art_size / 2.0f + hover_y, art_size, art_size };

    DrawTexturePro(aura_tex, src_rec, shadow_dst, (Vector2){ 0.0f, 0.0f }, 0.0f, (Color){ 0, 0, 0, 170 });
    DrawTexturePro(aura_tex, src_rec, art_dst, (Vector2){ 0.0f, 0.0f }, 0.0f, WHITE);

    int banner_x = 68;
    int banner_y = 68;
    int banner_w = 590;
    int banner_h = 98;

    DrawRectangleGradientV(banner_x, banner_y, 16, 480,
                           (Color){ 175, 18, 28, 230 }, (Color){ 45, 5, 10, 0 });
    DrawRectangleGradientV(banner_x + 16, banner_y + 98, 6, 390,
                           (Color){ 110, 10, 18, 170 }, (Color){ 20, 0, 0, 0 });

    DrawRectangleGradientH(banner_x, banner_y, banner_w, banner_h,
                           (Color){ 135, 12, 22, 240 }, (Color){ 45, 8, 14, 40 });
    DrawRectangleLinesEx((Rectangle){ (float)banner_x, (float)banner_y, (float)(banner_w - 60), (float)banner_h },
                         2.0f, (Color){ 210, 35, 45, 190 });

    int emblem_x = banner_x + 258;
    int emblem_y = banner_y + 6;
    DrawRectangle(emblem_x, emblem_y, 72, 86, (Color){ 70, 28, 8, 230 });
    DrawRectangleLinesEx((Rectangle){ (float)emblem_x, (float)emblem_y, 72.0f, 86.0f }, 3.0f, (Color){ 255, 200, 60, 255 });
    DrawText("67", emblem_x + 14, emblem_y + 24, 38, (Color){ 255, 225, 110, 255 });

    Color gold_bright = (Color){ 255, 215, 75, 255 };
    Color gold_sub = (Color){ 235, 195, 110, 255 };
    Color dark_shadow = (Color){ 10, 4, 6, 255 };

    draw_gow_text("AI", banner_x + 145, banner_y + 22, 56, gold_bright, dark_shadow, 4);
    draw_gow_text("SAFETY", banner_x + 345, banner_y + 22, 56, gold_bright, dark_shadow, 4);
    draw_gow_text("A U R A - 6 7", banner_x + 230, banner_y + 110, 18, gold_sub, dark_shadow, 2);
}

/* Renderiza o Menu Principal inspirado em God of War */
static void draw_gow_menu(const GameContext *ctx, Texture2D aura_tex, int selected_item, float menu_timer) {
    draw_gow_backdrop_and_banner(aura_tex, menu_timer);

    Color dark_shadow = (Color){ 10, 4, 6, 255 };
    const char *menu_items[4];
    menu_items[0] = "NOVO JOGO";
    menu_items[1] = "CONFIGURACOES";
    menu_items[2] = "RANKING E ESTATISTICAS";
    menu_items[3] = "SAIR";

    int list_x = 122;
    int list_y = 240;
    int item_step = 56;

    for (int i = 0; i < 4; i++) {
        int iy = list_y + i * item_step;
        bool is_sel = (i == selected_item);

        if (is_sel) {
            DrawRectangleGradientH(list_x - 24, iy - 6, 440, 42,
                                   (Color){ 165, 22, 32, 190 }, (Color){ 40, 5, 10, 0 });
            DrawRectangle(list_x - 24, iy - 6, 5, 42, (Color){ 255, 220, 110, 255 });

            float d_cx = (float)(list_x - 10);
            float d_cy = (float)(iy + 15);
            DrawPoly((Vector2){ d_cx, d_cy }, 4, 6.0f, 0.0f, (Color){ 255, 230, 140, 255 });

            Color sel_color = (Color){ 255, 238, 185, 255 };
            draw_gow_text(menu_items[i], list_x + 8, iy, 30, sel_color, dark_shadow, 3);
        } else {
            Color unsel_color = (Color){ 205, 42, 48, 255 };
            draw_gow_text(menu_items[i], list_x, iy + 4, 23, unsel_color, dark_shadow, 2);
        }
    }

    /* Resumo rapido das configuracoes ativas */
    const char *diff_txt = (ctx->difficulty == DIFFICULTY_HARD) ? "DIFICIL" : "NORMAL";
    const char *ctrl_txt = get_control_mode_name(ctx->control_mode);
    draw_gow_text(TextFormat("ATIVO: MODO %s  |  MOVIMENTO: %s", diff_txt, ctrl_txt),
                  122, 495, 15, (Color){ 170, 180, 200, 220 }, dark_shadow, 2);

    /* Rodape de Comandos */
    DrawRectangleGradientH(68, SCREEN_HEIGHT - 62, 680, 38,
                           (Color){ 25, 12, 16, 200 }, (Color){ 12, 12, 20, 0 });
    DrawCircle(92, SCREEN_HEIGHT - 43, 12.0f, (Color){ 180, 30, 40, 255 });
    DrawCircleLines(92, SCREEN_HEIGHT - 43, 12.0f, (Color){ 255, 215, 90, 255 });
    DrawText("E", 88, SCREEN_HEIGHT - 50, 16, WHITE);
    draw_gow_text("= SELECIONAR [ENTER/ESPACO]   |   [W/S ou SETAS] = NAVEGAR   |   [F11] = MAXIMIZAR",
                  114, SCREEN_HEIGHT - 51, 16, (Color){ 230, 230, 235, 255 }, dark_shadow, 2);
}

/* Renderiza o Menu de Configuracoes (Esquema de Controle, Dificuldade, Audio e Janela) */
static void draw_gow_settings(const GameContext *ctx, Texture2D aura_tex, int selected_item, float menu_timer) {
    draw_gow_backdrop_and_banner(aura_tex, menu_timer);

    Color dark_shadow = (Color){ 10, 4, 6, 255 };
    draw_gow_text("=== CONFIGURACOES DO SISTEMA ===", 122, 205, 22, (Color){ 255, 215, 75, 255 }, dark_shadow, 2);

    char item_ctrl[96];
    char item_diff[96];
    char item_vol[96];
    char item_win[96];

    snprintf(item_ctrl, sizeof(item_ctrl), "MOVIMENTO: < %s >", get_control_mode_name(ctx->control_mode));
    snprintf(item_diff, sizeof(item_diff), "DIFICULDADE: < %s >",
             (ctx->difficulty == DIFFICULTY_HARD) ? "DIFICIL (ANOMALIAS)" : "NORMAL (PADRAO)");
    snprintf(item_vol, sizeof(item_vol), "VOLUME DO AUDIO: < %d%% >", ctx->volume_pct);
    snprintf(item_win, sizeof(item_win), "TELA: < %s >",
             IsWindowMaximized() ? "MAXIMIZADA (TELA CHEIA)" : "JANELA (1280x720)");

    const char *settings_items[5];
    settings_items[0] = item_ctrl;
    settings_items[1] = item_diff;
    settings_items[2] = item_vol;
    settings_items[3] = item_win;
    settings_items[4] = "VOLTAR AO MENU PRINCIPAL";

    int list_x = 122;
    int list_y = 250;
    int item_step = 52;

    for (int i = 0; i < 5; i++) {
        int iy = list_y + i * item_step;
        bool is_sel = (i == selected_item);

        if (is_sel) {
            DrawRectangleGradientH(list_x - 24, iy - 6, 540, 40,
                                   (Color){ 165, 22, 32, 190 }, (Color){ 40, 5, 10, 0 });
            DrawRectangle(list_x - 24, iy - 6, 5, 40, (Color){ 255, 220, 110, 255 });

            float d_cx = (float)(list_x - 10);
            float d_cy = (float)(iy + 14);
            DrawPoly((Vector2){ d_cx, d_cy }, 4, 6.0f, 0.0f, (Color){ 255, 230, 140, 255 });

            Color sel_color = (Color){ 255, 238, 185, 255 };
            draw_gow_text(settings_items[i], list_x + 8, iy, 23, sel_color, dark_shadow, 3);
        } else {
            Color unsel_color = (Color){ 205, 42, 48, 255 };
            draw_gow_text(settings_items[i], list_x, iy + 3, 20, unsel_color, dark_shadow, 2);
        }
    }

    /* Explicacao detalhada da opcao selecionada */
    const char *help_line = "";
    if (selected_item == 0) {
        if (ctx->control_mode == CONTROL_ARROWS_ONLY) {
            help_line = "DICA: Move apenas nas SETAS. As teclas W, A, S, D ficam 100% dedicadas a digitacao!";
        } else if (ctx->control_mode == CONTROL_MOUSE) {
            help_line = "DICA: O personagem segue o cursor do MOUSE na arena, deixando as 2 maos livres para digitar!";
        } else {
            help_line = "DICA: Modo classico (move tanto com WASD quanto com as Setas direcionais).";
        }
    } else if (selected_item == 1) {
        help_line = "DICA: Escolha entre o Modo Normal equilibrado ou o Modo Dificil com anomalias intensas.";
    } else if (selected_item == 2) {
        help_line = "DICA: Ajusta o volume dos efeitos sonoros sintetizados.";
    } else if (selected_item == 3) {
        help_line = "DICA: Alterna entre janela 1280x720 e janela maximizada centralizada (Atalho: F11).";
    } else {
        help_line = "DICA: Retorna ao Menu Principal com as configuracoes salvas.";
    }
    draw_gow_text(help_line, 122, 530, 15, (Color){ 80, 230, 140, 255 }, dark_shadow, 2);

    /* Rodape de Comandos */
    DrawRectangleGradientH(68, SCREEN_HEIGHT - 62, 740, 38,
                           (Color){ 25, 12, 16, 200 }, (Color){ 12, 12, 20, 0 });
    DrawCircle(92, SCREEN_HEIGHT - 43, 12.0f, (Color){ 180, 30, 40, 255 });
    DrawCircleLines(92, SCREEN_HEIGHT - 43, 12.0f, (Color){ 255, 215, 90, 255 });
    DrawText("E", 88, SCREEN_HEIGHT - 50, 16, WHITE);
    draw_gow_text("= MUDAR [SETAS LADO / CLIQUE]  |  [ENTER / ESC] = CONFIRMAR E VOLTAR",
                  114, SCREEN_HEIGHT - 51, 16, (Color){ 230, 230, 235, 255 }, dark_shadow, 2);
}

int main(int argc, char **argv) {
#ifdef __linux__
    if (argc > 1 && strcmp(argv[1], "--warmup") == 0) {
        SetTraceLogLevel(LOG_NONE);
        InitWindow(64, 64, "WSLg Init");
        for (int attempt = 0; attempt < 40; attempt++) {
            BeginDrawing();
            ClearBackground(BLACK);
            EndDrawing();
            if (system("grep -q 'weston-rdprail-shell' /mnt/wslg/weston.log >/dev/null 2>&1") == 0) {
                break;
            }
            WaitTime(0.1);
        }
        WaitTime(0.6);
        CloseWindow();
        return 0;
    }
    if (system("grep -q 'weston-rdprail-shell' /mnt/wslg/weston.log >/dev/null 2>&1") != 0) {
        int rc = system("LD_LIBRARY_PATH=lib ./bin/jogo --warmup");
        (void)rc;
    }
#else
    (void)argc;
    (void)argv;
#endif
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "AI Safety");
    SetExitKey(KEY_NULL);
    SetTargetFPS(TARGET_FPS);
    audio_init();

    Image aura_icon_img = {
        .data = (void *)AURA67_ART_RGBA,
        .width = AURA67_ART_WIDTH,
        .height = AURA67_ART_HEIGHT,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    SetWindowIcon(aura_icon_img);
    Texture2D aura_art_tex = LoadTextureFromImage(aura_icon_img);
    SetTextureFilter(aura_art_tex, TEXTURE_FILTER_POINT);

    GameContext ctx;
    game_state_init(&ctx);

    char player_name[MAX_NAME_LEN] = "";
    int letter_count = 0;
    const char *name_error_msg = NULL;
    int menu_selected = 0;
    int settings_selected = 0;
    float menu_timer = 0.0f;
    bool should_quit = false;

    while (!WindowShouldClose() && !should_quit) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;
        menu_timer += dt;

        if (IsKeyPressed(KEY_F11)) {
            if (IsWindowMaximized()) {
                RestoreWindow();
            } else {
                MaximizeWindow();
            }
        }

        /* Calcula o deslocamento para centralizar o canvas 1280x720 em qualquer tamanho de janela */
        float center_x = (GetScreenWidth() - SCREEN_WIDTH) / 2.0f;
        float center_y = (GetScreenHeight() - SCREEN_HEIGHT) / 2.0f;
        if (center_x < 0.0f) center_x = 0.0f;
        if (center_y < 0.0f) center_y = 0.0f;

        Vector2 raw_mouse = GetMousePosition();
        Vector2 mouse_arena_pos = (Vector2){
            raw_mouse.x - center_x,
            raw_mouse.y - center_y
        };
        Vector2 mouse_delta = GetMouseDelta();
        bool mouse_moved = (fabsf(mouse_delta.x) > 0.5f || fabsf(mouse_delta.y) > 0.5f);
        bool mouse_clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

        /* --- INPUT & UPDATE --- */
        if (ctx.state == STATE_MENU) {
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                menu_selected = (menu_selected + 1) % 4;
                audio_play_key_ok();
            }
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                menu_selected = (menu_selected + 3) % 4;
                audio_play_key_ok();
            }

            /* Suporte a Hover e Clique do Mouse no Menu Principal */
            for (int i = 0; i < 4; i++) {
                Rectangle item_rec = (Rectangle){ 98.0f, (float)(234 + i * 56), 440.0f, 44.0f };
                if (CheckCollisionPointRec(mouse_arena_pos, item_rec)) {
                    if ((mouse_moved || mouse_clicked) && menu_selected != i) {
                        menu_selected = i;
                        audio_play_key_ok();
                    }
                }
            }

            if (IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_N)) {
                ctx.difficulty = DIFFICULTY_NORMAL;
                audio_play_key_ok();
            }
            if (IsKeyPressed(KEY_TWO)) {
                ctx.difficulty = DIFFICULTY_HARD;
                audio_play_key_ok();
            }

            bool confirm_menu = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_ENTER);
            if (mouse_clicked) {
                Rectangle active_rec = (Rectangle){ 98.0f, (float)(234 + menu_selected * 56), 440.0f, 44.0f };
                if (CheckCollisionPointRec(mouse_arena_pos, active_rec)) {
                    confirm_menu = true;
                }
            }

            if (IsKeyPressed(KEY_K)) {
                audio_play_key_ok();
                ctx.state = STATE_RANKING;
            } else if (IsKeyPressed(KEY_O)) {
                audio_play_key_ok();
                settings_selected = 0;
                ctx.state = STATE_SETTINGS;
            } else if (confirm_menu) {
                if (menu_selected == 0) {
                    audio_play_patch_complete();
                    game_state_reset_combat(&ctx);
                } else if (menu_selected == 1) {
                    audio_play_key_ok();
                    settings_selected = 0;
                    ctx.state = STATE_SETTINGS;
                } else if (menu_selected == 2) {
                    audio_play_key_ok();
                    ctx.state = STATE_RANKING;
                } else if (menu_selected == 3) {
                    should_quit = true;
                }
            }
        } else if (ctx.state == STATE_SETTINGS) {
            if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                settings_selected = (settings_selected + 1) % 5;
                audio_play_key_ok();
            }
            if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                settings_selected = (settings_selected + 4) % 5;
                audio_play_key_ok();
            }

            /* Suporte a Hover e Clique do Mouse nas Configuracoes */
            bool clicked_setting_row = false;
            for (int i = 0; i < 5; i++) {
                Rectangle row_rec = (Rectangle){ 98.0f, (float)(244 + i * 52), 540.0f, 42.0f };
                if (CheckCollisionPointRec(mouse_arena_pos, row_rec)) {
                    if ((mouse_moved || mouse_clicked) && settings_selected != i) {
                        settings_selected = i;
                        audio_play_key_ok();
                    }
                    if (mouse_clicked) {
                        clicked_setting_row = true;
                    }
                }
            }

            bool right_pressed = IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D) || IsKeyPressed(KEY_SPACE) || (clicked_setting_row && settings_selected < 4);
            bool left_pressed = IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT);

            /* ENTER ou ESC (ou clicar em VOLTAR) confirma as configuracoes escolhidas e volta ao Menu! */
            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ENTER) ||
                (settings_selected == 4 && (IsKeyPressed(KEY_SPACE) || clicked_setting_row))) {
                audio_play_patch_complete();
                ctx.state = STATE_MENU;
            } else if (settings_selected == 0 && (right_pressed || left_pressed)) {
                if (right_pressed) {
                    ctx.control_mode = (ctx.control_mode + 1) % 3;
                } else {
                    ctx.control_mode = (ctx.control_mode + 2) % 3;
                }
                ctx.typing_engine.control_mode = ctx.control_mode;
                audio_play_key_ok();
            } else if (settings_selected == 1 && (right_pressed || left_pressed)) {
                ctx.difficulty = (ctx.difficulty == DIFFICULTY_NORMAL) ? DIFFICULTY_HARD : DIFFICULTY_NORMAL;
                audio_play_key_ok();
            } else if (settings_selected == 2 && (right_pressed || left_pressed)) {
                if (right_pressed) {
                    ctx.volume_pct += 25;
                    if (ctx.volume_pct > 100) ctx.volume_pct = 0;
                } else {
                    ctx.volume_pct -= 25;
                    if (ctx.volume_pct < 0) ctx.volume_pct = 100;
                }
                SetMasterVolume((float)ctx.volume_pct / 100.0f);
                audio_play_key_ok();
            } else if (settings_selected == 3 && (right_pressed || left_pressed)) {
                if (IsWindowMaximized()) {
                    RestoreWindow();
                } else {
                    MaximizeWindow();
                }
                audio_play_key_ok();
            }
        } else if (ctx.state == STATE_COMBAT) {
            combat_process_round(&ctx, dt, mouse_arena_pos);
        } else if (ctx.state == STATE_GAME_OVER || ctx.state == STATE_VICTORY) {
            if (IsKeyPressed(KEY_ENTER)) {
                while (GetCharPressed() > 0) { }
                player_name[0] = '\0';
                letter_count = 0;
                name_error_msg = NULL;
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
                    name_error_msg = NULL;
                    audio_play_key_ok();
                }
                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                letter_count--;
                if (letter_count < 0) letter_count = 0;
                player_name[letter_count] = '\0';
                name_error_msg = NULL;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (letter_count == 0) {
                    audio_play_key_error();
                    name_error_msg = "DIGITE UM NOME VALIDO ANTES DE CONFIRMAR!";
                } else if (ranking_name_exists(player_name)) {
                    audio_play_key_error();
                    name_error_msg = "ESTE NOME JA ESTA NO RANKING! ESCOLHA OUTRO NOME.";
                } else {
                    audio_play_patch_complete();
                    ranking_add_score(player_name, ctx.score);
                    player_name[0] = '\0';
                    letter_count = 0;
                    name_error_msg = NULL;
                    ctx.state = STATE_RANKING;
                }
            } else if (IsKeyPressed(KEY_ESCAPE)) {
                name_error_msg = NULL;
                ctx.state = STATE_RANKING;
            }
        } else if (ctx.state == STATE_RANKING) {
            if (IsKeyPressed(KEY_M) || IsKeyPressed(KEY_ESCAPE)) {
                ctx.state = STATE_MENU;
            }
        }

        /* --- RENDER CENTRALIZADO NA TELA --- */
        BeginDrawing();
        ClearBackground(COLOR_BG);

        float shake_x = 0.0f;
        float shake_y = 0.0f;
        if (ctx.ui.shake_timer > 0.0f) {
            shake_x = (float)GetRandomValue((int)-ctx.ui.shake_intensity, (int)ctx.ui.shake_intensity);
            shake_y = (float)GetRandomValue((int)-ctx.ui.shake_intensity, (int)ctx.ui.shake_intensity);
        }

        Camera2D center_cam = { 0 };
        center_cam.offset = (Vector2){ center_x, center_y };
        center_cam.target = (Vector2){ 0.0f, 0.0f };
        center_cam.rotation = 0.0f;
        center_cam.zoom = 1.0f;

        if (ctx.state == STATE_MENU) {
            BeginMode2D(center_cam);
            draw_gow_menu(&ctx, aura_art_tex, menu_selected, menu_timer);
            EndMode2D();
        } else if (ctx.state == STATE_SETTINGS) {
            BeginMode2D(center_cam);
            draw_gow_settings(&ctx, aura_art_tex, settings_selected, menu_timer);
            EndMode2D();
        } else if (ctx.state == STATE_RANKING) {
            BeginMode2D(center_cam);

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

            EndMode2D();
        } else if (ctx.state == STATE_NAME_INPUT) {
            BeginMode2D(center_cam);

            DrawText("DIGITE SEU NOME PARA O RANKING:", SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 60, 20, RAYWHITE);
            Color box_border = (name_error_msg != NULL) ? COLOR_TEXT_ERROR : RAYWHITE;
            DrawRectangleLines(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2 - 20, 300, 40, box_border);
            DrawText(player_name, SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 - 10, 20, GREEN);
            DrawText("Pressione [ENTER] para confirmar  |  [ESC] Pular", SCREEN_WIDTH / 2 - 210, SCREEN_HEIGHT / 2 + 40, 18, GRAY);
            if (name_error_msg != NULL) {
                int ew = MeasureText(name_error_msg, 18);
                DrawText(name_error_msg, SCREEN_WIDTH / 2 - ew / 2, SCREEN_HEIGHT / 2 + 80, 18, COLOR_TEXT_ERROR);
            }

            EndMode2D();
        } else {
            Camera2D combat_cam = { 0 };
            combat_cam.offset = (Vector2){ center_x, center_y };
            combat_cam.target = (Vector2){ -shake_x, -shake_y };
            combat_cam.rotation = 0.0f;
            combat_cam.zoom = 1.0f;

            BeginMode2D(combat_cam);
            ui_draw_arena_grid();
            if (ctx.control_mode == CONTROL_MOUSE || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                /* Mira guia do cursor do mouse na arena */
                float mx = mouse_arena_pos.x;
                float my = mouse_arena_pos.y;
                if (mx >= (float)ARENA_MARGIN_X && mx <= (float)(SCREEN_WIDTH - ARENA_MARGIN_X) &&
                    my >= (float)ARENA_MARGIN_TOP && my <= (float)(SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM)) {
                    DrawCircleLines((int)mx, (int)my, 10.0f, (Color){ 0, 240, 255, 160 });
                    DrawLine((int)mx - 14, (int)my, (int)mx + 14, (int)my, (Color){ 0, 240, 255, 130 });
                    DrawLine((int)mx, (int)my - 14, (int)mx, (int)my + 14, (Color){ 0, 240, 255, 130 });
                }
            }
            bullet_mgr_draw(&ctx.bullet_mgr);
            player_draw(&ctx.player);
            boss_draw(&ctx.boss);
            ui_draw_particles(&ctx.ui);
            ui_draw_floating_texts(&ctx.ui);
            EndMode2D();

            BeginMode2D(center_cam);
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
            EndMode2D();
        }

        EndDrawing();
    }

    UnloadTexture(aura_art_tex);
    audio_close();
    CloseWindow();
    return 0;
}
