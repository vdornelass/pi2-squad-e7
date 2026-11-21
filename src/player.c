#include "player.h"
#include <math.h>

void player_init(Player *p, float x, float y) {
    p->rect = (Rectangle){ x - PLAYER_SIZE / 2.0f, y - PLAYER_SIZE / 2.0f, PLAYER_SIZE, PLAYER_SIZE };
    p->speed = PLAYER_SPEED;
    p->max_hp = PLAYER_MAX_HP;
    p->hp = PLAYER_MAX_HP;
    p->iframe_timer = 0.0f;
    p->confuse_timer = 0.0f;
    p->ext_fx = 0.0f;
    p->ext_fy = 0.0f;
    p->is_alive = true;
    p->trail_len = 0;
}

void player_handle_input_ex(Player *p, int control_mode, Vector2 mouse_arena_pos) {
    float dx = 0.0f;
    float dy = 0.0f;

    if (control_mode == CONTROL_WASD_ARROWS) {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    dy -= 1.0f;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  dy += 1.0f;
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  dx -= 1.0f;
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) dx += 1.0f;
    } else if (control_mode == CONTROL_ARROWS_ONLY) {
        if (IsKeyDown(KEY_UP))    dy -= 1.0f;
        if (IsKeyDown(KEY_DOWN))  dy += 1.0f;
        if (IsKeyDown(KEY_LEFT))  dx -= 1.0f;
        if (IsKeyDown(KEY_RIGHT)) dx += 1.0f;
    } else if (control_mode == CONTROL_MOUSE) {
        /* Setas continuam funcionando como apoio, mas se nao pressionadas segue o mouse */
        if (IsKeyDown(KEY_UP))    dy -= 1.0f;
        if (IsKeyDown(KEY_DOWN))  dy += 1.0f;
        if (IsKeyDown(KEY_LEFT))  dx -= 1.0f;
        if (IsKeyDown(KEY_RIGHT)) dx += 1.0f;

        if (dx == 0.0f && dy == 0.0f) {
            float cx = p->rect.x + p->rect.width / 2.0f;
            float cy = p->rect.y + p->rect.height / 2.0f;
            float mdx = mouse_arena_pos.x - cx;
            float mdy = mouse_arena_pos.y - cy;
            float dist = sqrtf(mdx * mdx + mdy * mdy);

            if (dist > 3.0f) {
                float factor = 1.35f;
                if (dist < 28.0f) {
                    factor = (dist / 28.0f) * 1.35f;
                }
                dx = (mdx / dist) * factor;
                dy = (mdy / dist) * factor;
            }
        }
    } else if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        /* Em qualquer modo, segurar o botao esquerdo do mouse tambem guia o personagem */
        float cx = p->rect.x + p->rect.width / 2.0f;
        float cy = p->rect.y + p->rect.height / 2.0f;
        float mdx = mouse_arena_pos.x - cx;
        float mdy = mouse_arena_pos.y - cy;
        float dist = sqrtf(mdx * mdx + mdy * mdy);
        if (dist > 3.0f) {
            float factor = 1.35f;
            if (dist < 28.0f) {
                factor = (dist / 28.0f) * 1.35f;
            }
            dx = (mdx / dist) * factor;
            dy = (mdy / dist) * factor;
        }
    }

    /* Normalizacao diagonal para teclado */
    if (control_mode != CONTROL_MOUSE && dx != 0.0f && dy != 0.0f) {
        dx *= 0.7071f;
        dy *= 0.7071f;
    }

    /* Inversao de eixos se status Prompt Injection ativo */
    if (p->confuse_timer > 0.0f) {
        dx = -dx;
        dy = -dy;
    }

    float move_x = dx * p->speed * GetFrameTime() + p->ext_fx;
    float move_y = dy * p->speed * GetFrameTime() + p->ext_fy;

    p->rect.x += move_x;
    p->rect.y += move_y;

    /* Reset de forcas externas apos aplicacao */
    p->ext_fx = 0.0f;
    p->ext_fy = 0.0f;

    /* Restricao de limites da arena */
    float min_x = (float)ARENA_MARGIN_X;
    float max_x = (float)(SCREEN_WIDTH - ARENA_MARGIN_X) - p->rect.width;
    float min_y = (float)ARENA_MARGIN_TOP;
    float max_y = (float)(SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM) - p->rect.height;

    if (p->rect.x < min_x) p->rect.x = min_x;
    if (p->rect.x > max_x) p->rect.x = max_x;
    if (p->rect.y < min_y) p->rect.y = min_y;
    if (p->rect.y > max_y) p->rect.y = max_y;

    /* Historico de rastro de movimento */
    if (p->trail_len < MAX_TRAIL) {
        p->trail[p->trail_len++] = (Vector2){ p->rect.x + p->rect.width / 2.0f, p->rect.y + p->rect.height / 2.0f };
    } else {
        for (int i = 0; i < MAX_TRAIL - 1; i++) {
            p->trail[i] = p->trail[i + 1];
        }
        p->trail[MAX_TRAIL - 1] = (Vector2){ p->rect.x + p->rect.width / 2.0f, p->rect.y + p->rect.height / 2.0f };
    }
}

void player_handle_input(Player *p) {
    player_handle_input_ex(p, CONTROL_WASD_ARROWS, (Vector2){ 0.0f, 0.0f });
}

void player_apply_force(Player *p, float fx, float fy) {
    p->ext_fx += fx;
    p->ext_fy += fy;
}

void player_apply_confuse(Player *p, float duration) {
    p->confuse_timer = duration;
}

void player_update(Player *p, float dt) {
    if (p->iframe_timer > 0.0f) {
        p->iframe_timer -= dt;
    }
    if (p->confuse_timer > 0.0f) {
        p->confuse_timer -= dt;
    }
}

bool player_take_damage(Player *p, int damage) {
    if (p->iframe_timer <= 0.0f) {
        p->hp -= damage;
        p->iframe_timer = PLAYER_IFRAME_DURATION;
        if (p->hp <= 0) {
            p->hp = 0;
            p->is_alive = false;
        }
        return true;
    }
    return false;
}

void player_draw(const Player *p) {
    if (!p->is_alive) return;

    /* Desenha rastro com desvanecimento */
    for (int i = 0; i < p->trail_len; i++) {
        float alpha = (float)(i + 1) / (float)(p->trail_len + 1);
        float sz = p->rect.width * (0.3f + 0.5f * alpha);
        Color c = (Color){ (unsigned char)(COLOR_PLAYER.r * 0.4f),
                           (unsigned char)(COLOR_PLAYER.g * 0.6f),
                           (unsigned char)(COLOR_PLAYER.b * 0.8f),
                           (unsigned char)(255 * alpha * 0.5f) };
        DrawRectangleLines((int)(p->trail[i].x - sz / 2.0f), (int)(p->trail[i].y - sz / 2.0f), (int)sz, (int)sz, c);
    }

    /* Piscar durante iframe ou indicador de confusao */
    Color body_color = COLOR_PLAYER;
    Color outline_color = COLOR_PLAYER_OUTLINE;

    if (p->iframe_timer > 0.0f && ((int)(p->iframe_timer * 18.0f) % 2 == 0)) {
        body_color = WHITE;
        outline_color = (Color){ 255, 100, 100, 255 };
    } else if (p->confuse_timer > 0.0f) {
        body_color = COLOR_BULLET_CONFUSE;
        outline_color = YELLOW;
    }

    DrawRectangleRec(p->rect, body_color);
    DrawRectangleLinesEx(p->rect, 2.0f, outline_color);

    /* Core central branco */
    DrawRectangle((int)(p->rect.x + p->rect.width / 2.0f - 3.0f),
                  (int)(p->rect.y + p->rect.height / 2.0f - 3.0f), 6, 6, WHITE);

    /* Indicador textual acima da cabeca quando confuso */
    if (p->confuse_timer > 0.0f) {
        const char *txt = "PROMPT INJECTION! [EIXOS INVERTIDOS]";
        int w = MeasureText(txt, 14);
        DrawText(txt, (int)(p->rect.x + p->rect.width / 2.0f - w / 2.0f), (int)p->rect.y - 20, 14, COLOR_BULLET_CONFUSE);
    }
}
