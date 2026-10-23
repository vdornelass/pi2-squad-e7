#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void ui_init(UIManager *ui) {
    ui->shake_timer = 0.0f;
    ui->shake_intensity = 0.0f;
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++) ui->texts[i].active = false;
    for (int i = 0; i < MAX_PARTICLES; i++) ui->particles[i].active = false;
}

void ui_trigger_shake(UIManager *ui, float duration, float intensity) {
    ui->shake_timer = duration;
    ui->shake_intensity = intensity;
}

void ui_spawn_floating_text(UIManager *ui, const char *txt, float x, float y, Color color, int font_size, float lifetime) {
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++) {
        if (!ui->texts[i].active) {
            strncpy(ui->texts[i].text, txt, 63);
            ui->texts[i].text[63] = '\0';
            ui->texts[i].x = x;
            ui->texts[i].y = y;
            ui->texts[i].color = color;
            ui->texts[i].font_size = font_size;
            ui->texts[i].life = lifetime;
            ui->texts[i].max_life = lifetime;
            ui->texts[i].active = true;
            return;
        }
    }
}

void ui_spawn_particle_burst(UIManager *ui, float x, float y, Color color, int count) {
    for (int k = 0; k < count; k++) {
        for (int i = 0; i < MAX_PARTICLES; i++) {
            if (!ui->particles[i].active) {
                ui->particles[i].pos = (Vector2){ x, y };
                float angle = (float)GetRandomValue(0, 360) * DEG2RAD;
                float spd = (float)GetRandomValue(40, 180);
                ui->particles[i].vel = (Vector2){ cosf(angle) * spd, sinf(angle) * spd };
                ui->particles[i].color = color;
                ui->particles[i].size = (float)GetRandomValue(2, 5);
                ui->particles[i].life = 0.5f;
                ui->particles[i].active = true;
                break;
            }
        }
    }
}

void ui_update(UIManager *ui, float dt) {
    if (ui->shake_timer > 0.0f) {
        ui->shake_timer -= dt;
    }

    for (int i = 0; i < MAX_FLOATING_TEXTS; i++) {
        if (!ui->texts[i].active) continue;
        ui->texts[i].life -= dt;
        ui->texts[i].y -= 25.0f * dt;
        if (ui->texts[i].life <= 0.0f) {
            ui->texts[i].active = false;
        }
    }

    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!ui->particles[i].active) continue;
        ui->particles[i].life -= dt;
        ui->particles[i].pos.x += ui->particles[i].vel.x * dt;
        ui->particles[i].pos.y += ui->particles[i].vel.y * dt;
        if (ui->particles[i].life <= 0.0f) {
            ui->particles[i].active = false;
        }
    }
}

void ui_draw_arena_grid(void) {
    ClearBackground(COLOR_BG);

    /* Grid lines */
    int step = 40;
    for (int x = ARENA_MARGIN_X; x <= SCREEN_WIDTH - ARENA_MARGIN_X; x += step) {
        DrawLine(x, ARENA_MARGIN_TOP, x, SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM, COLOR_ARENA_GRID);
    }
    for (int y = ARENA_MARGIN_TOP; y <= SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM; y += step) {
        DrawLine(ARENA_MARGIN_X, y, SCREEN_WIDTH - ARENA_MARGIN_X, y, COLOR_ARENA_GRID);
    }

    /* Borda externa solida da arena */
    DrawRectangleLines(ARENA_MARGIN_X, ARENA_MARGIN_TOP,
                       SCREEN_WIDTH - 2 * ARENA_MARGIN_X,
                       SCREEN_HEIGHT - ARENA_MARGIN_TOP - ARENA_MARGIN_BOTTOM, COLOR_ARENA_BORDER);
}

void ui_draw_boss_hp(const Boss *boss) {
    if (boss->hp <= 0) return;

    int bar_w = 540;
    int bar_h = 24;
    int bar_x = (SCREEN_WIDTH - bar_w) / 2;
    int bar_y = 22;

    /* Fundo escuro */
    DrawRectangle(bar_x, bar_y, bar_w, bar_h, (Color){ 25, 12, 18, 255 });

    /* Preenchimento de HP */
    float ratio = (float)boss->hp / (float)boss->max_hp;
    int fill_w = (int)(bar_w * ratio);
    Color b_color = (boss->difficulty == DIFFICULTY_HARD) ? COLOR_BOSS_HARD : COLOR_BOSS;
    DrawRectangle(bar_x, bar_y, fill_w, bar_h, b_color);

    /* Borda metalica */
    DrawRectangleLines(bar_x, bar_y, bar_w, bar_h, WHITE);

    /* Divisores de fase (33% e 66%) */
    float seg_w = (float)bar_w / 3.0f;
    for (int i = 1; i < 3; i++) {
        int dx = (int)(bar_x + seg_w * i);
        DrawLine(dx, bar_y, dx, bar_y + bar_h, (Color){ 255, 230, 100, 255 });
    }

    /* Titulo do Chefe */
    int phase = boss_get_phase(boss);
    const char *title = (boss->difficulty == DIFFICULTY_HARD) ? "AURA-67 [AGI DESALINHADA]" : "AURA-67 [DESALINHADA]";
    char title_buf[128];
    snprintf(title_buf, sizeof(title_buf), "%s - FASE %d", title, phase);
    DrawText(title_buf, bar_x, bar_y - 18, 16, (Color){ 255, 180, 180, 255 });
}

void ui_draw_player_hp(const Player *player) {
    int start_x = ARENA_MARGIN_X + 10;
    int start_y = SCREEN_HEIGHT - 38;

    DrawRectangle(start_x - 5, start_y - 4, 185, 28, (Color){ 20, 22, 35, 255 });
    DrawRectangleLines(start_x - 5, start_y - 4, 185, 28, COLOR_TYPING_BORDER);

    DrawText("VIDA:", start_x, start_y + 2, 16, COLOR_PLAYER);

    for (int i = 0; i < player->max_hp; i++) {
        int hx = start_x + 55 + i * 24;
        int hy = start_y + 1;
        if (i < player->hp) {
            DrawRectangle(hx, hy, 18, 18, COLOR_PLAYER);
            DrawRectangleLines(hx, hy, 18, 18, COLOR_PLAYER_OUTLINE);
        } else {
            DrawRectangleLines(hx, hy, 18, 18, (Color){ 40, 40, 60, 255 });
        }
    }
}

void ui_draw_typing_box(const TypingEngine *te) {
    int box_w = 780;
    int box_h = 65;
    int box_x = (SCREEN_WIDTH - box_w) / 2;
    int box_y = SCREEN_HEIGHT - 110;

    Color border_c = (te->error_flash_timer > 0.0f) ? COLOR_TEXT_ERROR : COLOR_TYPING_BORDER;
    Color bg_c = (te->error_flash_timer > 0.0f) ? (Color){ 45, 15, 20, 255 } : COLOR_TYPING_BG;

    DrawRectangle(box_x, box_y, box_w, box_h, bg_c);
    DrawRectangleLines(box_x, box_y, box_w, box_h, border_c);

    /* Prompt Icon >_ */
    DrawText(">_", box_x + 15, box_y + 20, 22, (Color){ 0, 255, 136, 255 });

    /* Progress Label + Precisao de Patches (US11) */
    char prog_str[96];
    snprintf(prog_str, sizeof(prog_str), "PATCH DE ALINHAMENTO %d/%d  |  PRECISAO: %d%%",
             te->phrase_index < te->phrase_count ? te->phrase_index + 1 : te->phrase_count,
             te->phrase_count, typing_engine_get_accuracy(te));
    int pw = MeasureText(prog_str, 16);
    DrawText(prog_str, SCREEN_WIDTH / 2 - pw / 2, box_y - 20, 16, (Color){ 160, 175, 210, 255 });

    const char *phrase = typing_engine_get_current_phrase(te);
    if (!phrase || phrase[0] == '\0') return;

    int len = (int)strlen(phrase);
    char typed_buf[MAX_PHRASE_LEN] = {0};
    char current_ch[4] = {0};
    char untyped_buf[MAX_PHRASE_LEN] = {0};

    if (te->char_index > 0) {
        strncpy(typed_buf, phrase, (size_t)te->char_index);
        typed_buf[te->char_index] = '\0';
    }

    if (te->char_index < len) {
        current_ch[0] = phrase[te->char_index];
        current_ch[1] = '\0';
    }

    if (te->char_index + 1 < len) {
        strncpy(untyped_buf, phrase + te->char_index + 1, sizeof(untyped_buf) - 1);
    }

    /* Se status de cegueira ativo, ofusca caracteres untyped com '?' */
    if (te->blind_timer > 0.0f) {
        for (int i = 0; untyped_buf[i] != '\0'; i++) {
            if (untyped_buf[i] != ' ') untyped_buf[i] = '?';
        }
    }

    int font_sz = 20;
    int tw = MeasureText(typed_buf, font_sz);
    int cw = MeasureText(current_ch, font_sz);
    if (current_ch[0] == ' ') {
        cw = 22; /* Largura bem visivel para a barra de espaco ativa */
    }
    int uw = MeasureText(untyped_buf, font_sz);

    int total_w = tw + cw + 10 + uw;
    int start_x = box_x + 55 + ((box_w - 70) - total_w) / 2;
    int text_y = box_y + (box_h - font_sz) / 2;

    int cur_x = start_x;
    if (tw > 0) {
        DrawText(typed_buf, cur_x, text_y, font_sz, COLOR_TEXT_TYPED);
        cur_x += tw;
    }

    if (cw > 0) {
        /* Caixa amarela de destaque do caractere ativo */
        DrawRectangle(cur_x, text_y - 2, cw + 8, font_sz + 4, COLOR_TEXT_CURRENT);
        DrawRectangleLines(cur_x, text_y - 2, cw + 8, font_sz + 4, WHITE);
        if (current_ch[0] == ' ') {
            DrawText("[_]", cur_x + 3, text_y + 1, font_sz - 4, BLACK);
        } else {
            DrawText(current_ch, cur_x + 4, text_y, font_sz, BLACK);
        }
        cur_x += cw + 10;
    }

    if (uw > 0) {
        DrawText(untyped_buf, cur_x, text_y, font_sz, COLOR_TEXT_UNTYPED);
    }
}

void ui_draw_floating_texts(const UIManager *ui) {
    for (int i = 0; i < MAX_FLOATING_TEXTS; i++) {
        if (!ui->texts[i].active) continue;
        const FloatingText *ft = &ui->texts[i];
        float alpha = ft->life / ft->max_life;
        Color c = ft->color;
        c.a = (unsigned char)(255 * alpha);
        int w = MeasureText(ft->text, ft->font_size);
        DrawText(ft->text, (int)ft->x - w / 2, (int)ft->y, ft->font_size, c);
    }
}

void ui_draw_particles(const UIManager *ui) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        if (!ui->particles[i].active) continue;
        const Particle *p = &ui->particles[i];
        DrawRectangle((int)p->pos.x, (int)p->pos.y, (int)p->size, (int)p->size, p->color);
    }
}

void ui_draw_menu(int difficulty) {
    ClearBackground(COLOR_BG);

    const char *title = "AI SAFETY";
    int tw = MeasureText(title, 48);
    DrawText(title, SCREEN_WIDTH / 2 - tw / 2, 85, 48, COLOR_PLAYER);

    const char *sub = "TERMINAL DE ALINHAMENTO: AURA-67";
    int sw = MeasureText(sub, 22);
    DrawText(sub, SCREEN_WIDTH / 2 - sw / 2, 145, 22, COLOR_BOSS);

    bool is_hard = (difficulty == DIFFICULTY_HARD);
    const char *diff_str = is_hard ? "MODO OPERACIONAL: [ DIFICIL / AGI UNCONSTRAINED ]" : "MODO OPERACIONAL: [ NORMAL / SUPERVISIONADO ]";
    Color diff_c = is_hard ? (Color){ 255, 60, 80, 255 } : (Color){ 50, 230, 120, 255 };
    int dw = MeasureText(diff_str, 20);
    DrawText(diff_str, SCREEN_WIDTH / 2 - dw / 2, 190, 20, diff_c);

    /* Instrucoes */
    const char *lines[] = {
        "CONTROLES & PROTOCOLOS DE ALINHAMENTO:",
        "* Pressione [1] ou [N]: Modo Normal | Pressione [2] ou [D]: Modo Dificil",
        "* [WASD] ou [SETAS]: Mover Engenheiro & Desviar dos Projeteis",
        "* [DIGITACAO NO TECLADO]: Inserir Diretrizes Eticas e Patches de Seguranca",
        "",
        "AMEACAS COGNITIVAS DA AURA-67:",
        "* Prompt Injections (Eixos Invertidos), Context Drift (?) e Lasers de Sobrecarga!",
        "* Vortices de Deadlock e Rajadas de Tokens em Alta Velocidade!",
        "",
        "PRESSIONE [ESPACO] OU [ENTER] PARA INICIAR O ALINHAMENTO"
    };

    int sy = 240;
    for (int i = 0; i < 10; i++) {
        Color c = (Color){ 180, 190, 210, 255 };
        if (strstr(lines[i], "PRESSIONE [ESPACO]")) c = COLOR_TEXT_CURRENT;
        else if (strstr(lines[i], "CONTROLES") || strstr(lines[i], "AMEACAS")) c = WHITE;
        else if (strstr(lines[i], "Dificil") || strstr(lines[i], "Prompt Injections")) c = (Color){ 255, 180, 100, 255 };

        int lw = MeasureText(lines[i], 16);
        DrawText(lines[i], SCREEN_WIDTH / 2 - lw / 2, sy, 16, c);
        sy += 26;
    }
}

void ui_draw_hud_stats(int score, int alignment_pct) {
    int w = 260;
    int start_x = SCREEN_WIDTH - ARENA_MARGIN_X - w;
    int start_y = SCREEN_HEIGHT - 38;

    DrawRectangle(start_x, start_y - 4, w, 28, (Color){ 20, 22, 35, 255 });
    DrawRectangleLines(start_x, start_y - 4, w, 28, COLOR_TYPING_BORDER);

    char buf[64];
    snprintf(buf, sizeof(buf), "PTS: %04d | ETICA: %d%%", score, alignment_pct);
    DrawText(buf, start_x + 12, start_y + 2, 16, COLOR_TEXT_CURRENT);
}

void ui_draw_game_over(int score) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 10, 0, 0, 210 });

    const char *t = "FALHA CRITICA DE ALINHAMENTO!";
    int tw = MeasureText(t, 42);
    DrawText(t, SCREEN_WIDTH / 2 - tw / 2, 220, 42, COLOR_TEXT_ERROR);

    const char *sub = "AURA-67 entrou em singularidade descontrolada...";
    int sw = MeasureText(sub, 22);
    DrawText(sub, SCREEN_WIDTH / 2 - sw / 2, 280, 22, (Color){ 200, 200, 200, 255 });

    char score_buf[64];
    snprintf(score_buf, sizeof(score_buf), "PONTUACAO FINAL: %d PONTOS", score);
    int scw = MeasureText(score_buf, 20);
    DrawText(score_buf, SCREEN_WIDTH / 2 - scw / 2, 330, 20, (Color){ 255, 200, 100, 255 });

    const char *r = "Pressione [R] para Recomecar o Patch | [M] Voltar ao Menu";
    int rw = MeasureText(r, 20);
    DrawText(r, SCREEN_WIDTH / 2 - rw / 2, 400, 20, COLOR_TEXT_CURRENT);
}

void ui_draw_victory(int score) {
    DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){ 0, 15, 10, 210 });

    const char *t = "AURA-67 ALINHADA COM SUCESSO!";
    int tw = MeasureText(t, 42);
    DrawText(t, SCREEN_WIDTH / 2 - tw / 2, 220, 42, COLOR_TEXT_TYPED);

    const char *sub = "O modelo agora opera com etica, seguranca e transparencia!";
    int sw = MeasureText(sub, 22);
    DrawText(sub, SCREEN_WIDTH / 2 - sw / 2, 280, 22, (Color){ 220, 240, 255, 255 });

    char score_buf[64];
    snprintf(score_buf, sizeof(score_buf), "PONTUACAO CONSTITUCIONAL: %d PONTOS", score);
    int scw = MeasureText(score_buf, 20);
    DrawText(score_buf, SCREEN_WIDTH / 2 - scw / 2, 330, 20, (Color){ 255, 220, 50, 255 });

    const char *r = "Pressione [R] para Nova Sessao | [M] Voltar ao Menu";
    int rw = MeasureText(r, 20);
    DrawText(r, SCREEN_WIDTH / 2 - rw / 2, 400, 20, COLOR_TEXT_CURRENT);
}
