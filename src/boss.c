#include "boss.h"
#include <math.h>

void boss_init(Boss *b, float x, float y, int difficulty) {
    b->rect = (Rectangle){ x - BOSS_SIZE / 2.0f, y - BOSS_SIZE / 2.0f, BOSS_SIZE, BOSS_SIZE };
    b->base_x = x;
    b->base_y = y;
    b->max_hp = BOSS_MAX_HP;
    b->hp = BOSS_MAX_HP;
    b->difficulty = difficulty;
    b->move_timer = 0.0f;
    b->pulse_timer = 0.0f;
    b->hit_flash_timer = 0.0f;

    b->timer_ring = 0.0f;
    b->timer_aimed = 0.0f;
    b->timer_spiral = 0.0f;
    b->timer_rain = 0.0f;
    b->timer_homing = 0.0f;
    b->timer_cross = 0.0f;
    b->timer_shockwave = 0.0f;
    b->timer_special = 0.0f;
    b->timer_laser = 0.0f;
    b->timer_vortex = 0.0f;

    b->spiral_angle = 0.0f;
    b->spiral_angle_2 = 0.0f;
    b->alignment_pct = 0;
}

int boss_get_phase(const Boss *b) {
    float ratio = (float)b->hp / (float)b->max_hp;
    if (ratio > 0.66f) return 1;
    if (ratio > 0.33f) return 2;
    return 3;
}

void boss_take_damage(Boss *b, int damage) {
    b->hp -= damage;
    if (b->hp < 0) b->hp = 0;
    b->hit_flash_timer = 0.35f;
}

void boss_update(Boss *b, float dt, BulletManager *bm, Vector2 player_pos) {
    if (b->hp <= 0) return;

    bool is_hard = (b->difficulty == DIFFICULTY_HARD);

    /* Velocidade de movimento e pulsacao */
    float speed_mult = is_hard ? 2.0f : 1.35f;
    b->move_timer += dt * speed_mult;
    b->pulse_timer += dt * (is_hard ? 6.0f : 4.0f);
    if (b->hit_flash_timer > 0.0f) b->hit_flash_timer -= dt;

    /* Oscilacao horizontal suave pelo topo da arena */
    float sway_amp = is_hard ? 180.0f : 145.0f;
    float sway_y = is_hard ? 25.0f : 15.0f;
    b->rect.x = b->base_x + sinf(b->move_timer) * sway_amp - b->rect.width / 2.0f;
    b->rect.y = b->base_y + cosf(b->move_timer * 0.7f) * sway_y - b->rect.height / 2.0f;

    Vector2 center = (Vector2){ b->rect.x + b->rect.width / 2.0f, b->rect.y + b->rect.height / 2.0f };
    int current_phase = boss_get_phase(b);

    /* --- 1. Lasers Telegrafados (Fases 2 e 3: Cooldown 9.6s Normal / 7.2s Hard) --- */
    b->timer_laser += dt;
    float laser_cd = is_hard ? 7.2f : 9.6f;
    if (b->timer_laser >= laser_cd && current_phase >= 2) {
        b->timer_laser = 0.0f;
        bool is_vert = (GetRandomValue(0, 1) == 0);
        bullet_mgr_spawn_laser_warning(bm, is_vert, player_pos.x, player_pos.y);
    }

    /* --- 2. Projeteis Especiais Teleguiados (Blindness & Confuse: 17.0s Normal / 13.0s Hard) --- */
    b->timer_special += dt;
    float special_cd = is_hard ? 13.0f : 17.0f;
    if (b->timer_special >= special_cd) {
        b->timer_special = 0.0f;
        if (GetRandomValue(0, 99) < 50) {
            bullet_mgr_spawn_blind_bullet(bm, center, 2.0f * 60.0f);
        } else {
            bullet_mgr_spawn_confuse_bullet(bm, center, 2.0f * 60.0f);
        }
    }

    /* =========================================================================
     * MODO NORMAL (~20% mais lento e espacado para jogabilidade equilibrada)
     * ========================================================================= */
    if (!is_hard) {
        if (current_phase == 1) {
            b->timer_ring += dt;
            if (b->timer_ring >= 2.65f) {
                b->timer_ring = 0.0f;
                bullet_mgr_spawn_ring_ex(bm, center, 12, 2.55f * 60.0f, COLOR_BULLET_RING, 0.0f);
            }

            b->timer_aimed += dt;
            if (b->timer_aimed >= 1.25f) {
                b->timer_aimed = 0.0f;
                bullet_mgr_spawn_aimed_ex(bm, center, player_pos, 3.6f * 60.0f, 0.15f, COLOR_BULLET_FAST);
            }
        } else if (current_phase == 2) {
            b->timer_spiral += dt;
            if (b->timer_spiral >= 0.22f) {
                b->timer_spiral = 0.0f;
                b->spiral_angle += 0.35f;
                bullet_mgr_spawn_spiral(bm, center, b->spiral_angle, 3.05f * 60.0f, COLOR_BULLET_DEFAULT);
            }

            b->timer_rain += dt;
            if (b->timer_rain >= 3.6f) {
                b->timer_rain = 0.0f;
                int gap_x = GetRandomValue(ARENA_MARGIN_X + 130, SCREEN_WIDTH - ARENA_MARGIN_X - 130);
                bullet_mgr_spawn_rain(bm, 2.25f * 60.0f, gap_x, 190);
            }
        } else if (current_phase == 3) {
            b->timer_spiral += dt;
            if (b->timer_spiral >= 0.18f) {
                b->timer_spiral = 0.0f;
                b->spiral_angle += 0.45f;
                bullet_mgr_spawn_spiral(bm, center, b->spiral_angle, 3.35f * 60.0f, COLOR_BULLET_RING);
            }

            b->timer_ring += dt;
            if (b->timer_ring >= 2.2f) {
                b->timer_ring = 0.0f;
                float offset = (float)GetRandomValue(0, 628) / 100.0f;
                bullet_mgr_spawn_ring_ex(bm, center, 15, 3.05f * 60.0f, COLOR_BULLET_FAST, offset);
            }

            b->timer_aimed += dt;
            if (b->timer_aimed >= 1.0f) {
                b->timer_aimed = 0.0f;
                bullet_mgr_spawn_aimed_ex(bm, center, player_pos, 4.15f * 60.0f, 0.20f, COLOR_BULLET_FAST);
            }
        }
    }
    /* =========================================================================
     * MODO DIFICIL / HARD MODE (~20% mais lento e espacado)
     * ========================================================================= */
    else {
        if (current_phase == 1) {
            b->timer_cross += dt;
            if (b->timer_cross >= 1.7f) {
                b->timer_cross = 0.0f;
                b->spiral_angle += 0.2f;
                bullet_mgr_spawn_cross(bm, center, 3.35f * 60.0f, b->spiral_angle);
            }

            b->timer_aimed += dt;
            if (b->timer_aimed >= 1.0f) {
                b->timer_aimed = 0.0f;
                bullet_mgr_spawn_aimed_ex(bm, center, player_pos, 4.0f * 60.0f, 0.0f, COLOR_BULLET_FAST);
                bullet_mgr_spawn_aimed_ex(bm, center, player_pos, 3.85f * 60.0f, 0.25f, COLOR_BULLET_FAST);
                bullet_mgr_spawn_aimed_ex(bm, center, player_pos, 3.85f * 60.0f, -0.25f, COLOR_BULLET_FAST);
            }
        } else if (current_phase == 2) {
            b->timer_spiral += dt;
            if (b->timer_spiral >= 0.15f) {
                b->timer_spiral = 0.0f;
                b->spiral_angle += 0.4f;
                b->spiral_angle_2 -= 0.4f;
                bullet_mgr_spawn_spiral(bm, center, b->spiral_angle, 3.5f * 60.0f, COLOR_BULLET_RING);
                bullet_mgr_spawn_spiral(bm, center, b->spiral_angle_2, 3.5f * 60.0f, COLOR_BULLET_DEFAULT);
            }

            b->timer_homing += dt;
            if (b->timer_homing >= 2.65f) {
                b->timer_homing = 0.0f;
                bullet_mgr_spawn_homing(bm, center, 2.8f * 60.0f);
            }

            b->timer_rain += dt;
            if (b->timer_rain >= 2.9f) {
                b->timer_rain = 0.0f;
                int gap_x = GetRandomValue(ARENA_MARGIN_X + 130, SCREEN_WIDTH - ARENA_MARGIN_X - 130);
                bullet_mgr_spawn_rain(bm, 2.85f * 60.0f, gap_x, 150);
            }
        } else if (current_phase == 3) {
            b->timer_shockwave += dt;
            if (b->timer_shockwave >= 3.4f) {
                b->timer_shockwave = 0.0f;
                bullet_mgr_spawn_shockwave(bm, center, 3, 4.15f * 60.0f);
            }

            b->timer_spiral += dt;
            if (b->timer_spiral >= 0.13f) {
                b->timer_spiral = 0.0f;
                b->spiral_angle += 0.45f;
                b->spiral_angle_2 -= 0.45f;
                bullet_mgr_spawn_spiral(bm, center, b->spiral_angle, 3.85f * 60.0f, COLOR_BULLET_FAST);
                bullet_mgr_spawn_spiral(bm, center, b->spiral_angle_2, 3.85f * 60.0f, COLOR_BULLET_DEFAULT);
            }

            b->timer_homing += dt;
            if (b->timer_homing >= 2.2f) {
                b->timer_homing = 0.0f;
                bullet_mgr_spawn_homing(bm, center, 3.05f * 60.0f);
            }
        }
    }
}

void boss_draw(const Boss *b) {
    if (b->hp <= 0) return;

    bool is_hard = (b->difficulty == DIFFICULTY_HARD);
    float pulse = sinf(b->pulse_timer) * (is_hard ? 5.0f : 3.0f);
    Rectangle draw_rect = (Rectangle){
        b->rect.x - pulse / 2.0f,
        b->rect.y - pulse / 2.0f,
        b->rect.width + pulse,
        b->rect.height + pulse
    };

    Color fill_color = is_hard ? COLOR_BOSS_HARD : COLOR_BOSS;
    Color border_color = is_hard ? (Color){ 255, 200, 50, 255 } : COLOR_BOSS_OUTLINE;

    if (b->hit_flash_timer > 0.0f) {
        fill_color = (Color){ 255, 255, 200, 255 };
        border_color = WHITE;
    }

    /* Corpo pulsante do Chefe */
    DrawRectangleRec(draw_rect, fill_color);
    DrawRectangleLinesEx(draw_rect, is_hard ? 4.0f : 3.0f, border_color);

    /* Nucleo geometrico interno (Losango brilhante igual ao boss.py) */
    Vector2 c = (Vector2){ draw_rect.x + draw_rect.width / 2.0f, draw_rect.y + draw_rect.height / 2.0f };
    float d = is_hard ? 16.0f : 14.0f;
    Vector2 top = (Vector2){ c.x, c.y - d };
    Vector2 right = (Vector2){ c.x + d, c.y };
    Vector2 bottom = (Vector2){ c.x, c.y + d };
    Vector2 left = (Vector2){ c.x - d, c.y };

    Color core_c = is_hard ? (Color){ 255, 230, 0, 255 } : WHITE;
    float thick = is_hard ? 3.0f : 2.0f;
    DrawLineEx(top, right, thick, core_c);
    DrawLineEx(right, bottom, thick, core_c);
    DrawLineEx(bottom, left, thick, core_c);
    DrawLineEx(left, top, thick, core_c);
}
