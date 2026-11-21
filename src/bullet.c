#include "bullet.h"
#include <math.h>
#include <stddef.h>

static float rand_float(float min_val, float max_val) {
    int r = GetRandomValue(0, 10000);
    float t = (float)r / 10000.0f;
    return min_val + t * (max_val - min_val);
}

void bullet_mgr_init(BulletManager *bm) {
    bullet_mgr_clear(bm);
}

void bullet_mgr_clear(BulletManager *bm) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        bm->bullets[i].active = false;
    }
    for (int i = 0; i < MAX_LASERS; i++) {
        bm->lasers[i].active = false;
    }
    bm->vortex.active = false;
}

void bullet_mgr_spawn_ex(BulletManager *bm, Vector2 pos, Vector2 vel, float radius, Color color, BulletType type, float life) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bm->bullets[i].active) {
            bm->bullets[i].pos = pos;
            bm->bullets[i].vel = vel;
            bm->bullets[i].radius = radius;
            bm->bullets[i].color = color;
            bm->bullets[i].type = type;
            if (type == BULLET_HOMING) {
                bm->bullets[i].homing_timer = 2.8f;
            } else if (type == BULLET_BLIND || type == BULLET_CONFUSE) {
                bm->bullets[i].homing_timer = 1.4f;
            } else {
                bm->bullets[i].homing_timer = 0.0f;
            }
            bm->bullets[i].life = life;
            bm->bullets[i].max_life = life;
            bm->bullets[i].active = true;
            return;
        }
    }
}

void bullet_mgr_spawn(BulletManager *bm, Vector2 pos, Vector2 vel, float radius, BulletType type, float life) {
    Color c = COLOR_BULLET_DEFAULT;
    if (type == BULLET_HOMING) c = COLOR_BULLET_HOMING;
    else if (type == BULLET_BLIND) c = COLOR_BULLET_BLIND;
    else if (type == BULLET_CONFUSE) c = COLOR_BULLET_CONFUSE;
    bullet_mgr_spawn_ex(bm, pos, vel, radius, c, type, life);
}

void bullet_mgr_spawn_ring_ex(BulletManager *bm, Vector2 pos, int count, float speed, Color color, float angle_offset) {
    float step = (2.0f * PI) / (float)count;
    for (int i = 0; i < count; i++) {
        float angle = i * step + angle_offset;
        Vector2 vel = (Vector2){ cosf(angle) * speed, sinf(angle) * speed };
        bullet_mgr_spawn_ex(bm, pos, vel, 6.0f, color, BULLET_NORMAL, 10.0f);
    }
}

void bullet_mgr_spawn_ring(BulletManager *bm, Vector2 pos, int count, float speed, BulletType type) {
    Color c = (type == BULLET_NORMAL) ? COLOR_BULLET_RING : COLOR_BULLET_FAST;
    bullet_mgr_spawn_ring_ex(bm, pos, count, speed, c, 0.0f);
}

void bullet_mgr_spawn_spiral(BulletManager *bm, Vector2 pos, float angle, float speed, Color color) {
    Vector2 v1 = (Vector2){ cosf(angle) * speed, sinf(angle) * speed };
    Vector2 v2 = (Vector2){ -v1.x, -v1.y };
    bullet_mgr_spawn_ex(bm, pos, v1, 6.0f, color, BULLET_NORMAL, 10.0f);
    bullet_mgr_spawn_ex(bm, pos, v2, 6.0f, color, BULLET_NORMAL, 10.0f);
}

void bullet_mgr_spawn_aimed_ex(BulletManager *bm, Vector2 pos, Vector2 target, float speed, float spread, Color color) {
    float dx = target.x - pos.x;
    float dy = target.y - pos.y;
    float base_angle = atan2f(dy, dx) + rand_float(-spread, spread);
    Vector2 vel = (Vector2){ cosf(base_angle) * speed, sinf(base_angle) * speed };
    bullet_mgr_spawn_ex(bm, pos, vel, 7.0f, color, BULLET_NORMAL, 10.0f);
}

void bullet_mgr_spawn_aimed(BulletManager *bm, Vector2 pos, Vector2 target, float speed, BulletType type) {
    Color c = COLOR_BULLET_FAST;
    if (type == BULLET_BLIND) c = COLOR_BULLET_BLIND;
    else if (type == BULLET_CONFUSE) c = COLOR_BULLET_CONFUSE;
    float dx = target.x - pos.x;
    float dy = target.y - pos.y;
    float dist = sqrtf(dx * dx + dy * dy);
    if (dist > 0.001f) {
        Vector2 vel = (Vector2){ (dx / dist) * speed, (dy / dist) * speed };
        bullet_mgr_spawn_ex(bm, pos, vel, 7.0f, c, type, 10.0f);
    }
}

void bullet_mgr_spawn_homing(BulletManager *bm, Vector2 pos, float speed) {
    float angle = rand_float(0.0f, 2.0f * PI);
    Vector2 vel = (Vector2){ cosf(angle) * speed, sinf(angle) * speed };
    bullet_mgr_spawn_ex(bm, pos, vel, 7.0f, COLOR_BULLET_HOMING, BULLET_HOMING, 8.0f);
}

void bullet_mgr_spawn_blind_bullet(BulletManager *bm, Vector2 pos, float speed) {
    float angle = rand_float(0.0f, 2.0f * PI);
    Vector2 vel = (Vector2){ cosf(angle) * speed, sinf(angle) * speed };
    bullet_mgr_spawn_ex(bm, pos, vel, 8.0f, COLOR_BULLET_BLIND, BULLET_BLIND, 8.0f);
}

void bullet_mgr_spawn_confuse_bullet(BulletManager *bm, Vector2 pos, float speed) {
    float angle = rand_float(0.0f, 2.0f * PI);
    Vector2 vel = (Vector2){ cosf(angle) * speed, sinf(angle) * speed };
    bullet_mgr_spawn_ex(bm, pos, vel, 8.0f, COLOR_BULLET_CONFUSE, BULLET_CONFUSE, 8.0f);
}

void bullet_mgr_spawn_cross(BulletManager *bm, Vector2 pos, float speed, float angle_offset) {
    for (int i = 0; i < 8; i++) {
        float angle = (float)i * (PI / 4.0f) + angle_offset;
        Vector2 vel = (Vector2){ cosf(angle) * speed, sinf(angle) * speed };
        bullet_mgr_spawn_ex(bm, pos, vel, 6.0f, COLOR_BULLET_WALL, BULLET_NORMAL, 10.0f);
    }
}

void bullet_mgr_spawn_shockwave(BulletManager *bm, Vector2 pos, int rings, float speed) {
    for (int r = 0; r < rings; r++) {
        int count = 16 + r * 4;
        float ring_spd = speed - (float)r * 42.0f;
        bullet_mgr_spawn_ring_ex(bm, pos, count, ring_spd, COLOR_BULLET_RING, (float)r * 0.1f);
    }
}

void bullet_mgr_spawn_rain(BulletManager *bm, float speed, int gap_x, int gap_width) {
    int arena_left = ARENA_MARGIN_X + 12;
    int arena_right = SCREEN_WIDTH - ARENA_MARGIN_X - 12;
    float start_y = (float)(ARENA_MARGIN_TOP + 10);
    int step = 32;

    for (int x = arena_left; x <= arena_right; x += step) {
        if (x >= (gap_x - gap_width / 2) && x <= (gap_x + gap_width / 2)) {
            continue;
        }
        bullet_mgr_spawn_ex(bm, (Vector2){ (float)x, start_y }, (Vector2){ 0.0f, speed }, 5.0f, COLOR_BULLET_DEFAULT, BULLET_NORMAL, 10.0f);
    }
}

void bullet_mgr_spawn_laser_warning(BulletManager *bm, bool is_vertical, float target_x, float target_y) {
    if (is_vertical) {
        float x = target_x - 25.0f;
        if (x < (float)ARENA_MARGIN_X) x = (float)ARENA_MARGIN_X;
        if (x + 50.0f > (float)(SCREEN_WIDTH - ARENA_MARGIN_X)) x = (float)(SCREEN_WIDTH - ARENA_MARGIN_X) - 50.0f;
        float h = (float)(SCREEN_HEIGHT - ARENA_MARGIN_TOP - ARENA_MARGIN_BOTTOM);
        bullet_mgr_spawn_laser(bm, x, (float)ARENA_MARGIN_TOP, 50.0f, h, LASER_WARN_TIME, LASER_BEAM_TIME);
    } else {
        float y = target_y - 25.0f;
        if (y < (float)ARENA_MARGIN_TOP) y = (float)ARENA_MARGIN_TOP;
        if (y + 50.0f > (float)(SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM)) y = (float)(SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM) - 50.0f;
        float w = (float)(SCREEN_WIDTH - 2 * ARENA_MARGIN_X);
        bullet_mgr_spawn_laser(bm, (float)ARENA_MARGIN_X, y, w, 50.0f, LASER_WARN_TIME, LASER_BEAM_TIME);
    }
}

void bullet_mgr_spawn_laser(BulletManager *bm, float x, float y, float w, float h, float warning_time, float active_time) {
    for (int i = 0; i < MAX_LASERS; i++) {
        if (!bm->lasers[i].active) {
            bm->lasers[i].rect = (Rectangle){ x, y, w, h };
            bm->lasers[i].is_vertical = (h > w);
            bm->lasers[i].warning_timer = warning_time;
            bm->lasers[i].active_timer = active_time;
            bm->lasers[i].is_firing = false;
            bm->lasers[i].has_damaged = false;
            bm->lasers[i].active = true;
            return;
        }
    }
}

void bullet_mgr_spawn_vortex(BulletManager *bm, Vector2 pos, float radius, float strength, float duration) {
    bm->vortex.pos = pos;
    bm->vortex.radius = radius;
    bm->vortex.pull_strength = strength;
    bm->vortex.duration = duration;
    bm->vortex.max_duration = duration;
    bm->vortex.angle = 0.0f;
    for (int i = 0; i < VORTEX_PARTICLES; i++) {
        bm->vortex.particles[i].r = rand_float(80.0f, 160.0f);
        bm->vortex.particles[i].angle = rand_float(0.0f, 2.0f * PI);
        bm->vortex.particles[i].speed = rand_float(80.0f, 140.0f);
    }
    bm->vortex.active = true;
}

bool bullet_mgr_update(BulletManager *bm, float dt, Player *player, TypingEngine *te, const char **status_applied_out) {
    bool hit_player = false;
    if (status_applied_out) *status_applied_out = NULL;

    Vector2 p_center = (Vector2){ player->rect.x + player->rect.width / 2.0f, player->rect.y + player->rect.height / 2.0f };

    /* 1. Vortex Gravitacional no Centro da Arena (Igual ao VortexHazard do Python) */
    if (bm->vortex.active) {
        bm->vortex.duration -= dt;
        bm->vortex.angle += dt * 5.0f;
        if (bm->vortex.duration <= 0.0f) {
            bm->vortex.active = false;
        } else {
            for (int i = 0; i < VORTEX_PARTICLES; i++) {
                bm->vortex.particles[i].r -= bm->vortex.particles[i].speed * dt;
                bm->vortex.particles[i].angle += dt * 2.0f;
                if (bm->vortex.particles[i].r <= 10.0f) {
                    bm->vortex.particles[i].r = rand_float(100.0f, 170.0f);
                    bm->vortex.particles[i].angle = rand_float(0.0f, 2.0f * PI);
                }
            }

            float vdx = bm->vortex.pos.x - p_center.x;
            float vdy = bm->vortex.pos.y - p_center.y;
            float dist = sqrtf(vdx * vdx + vdy * vdy);
            if (dist > 1.0f) {
                float pull_speed = bm->vortex.pull_strength * (1.0f - dist / 650.0f);
                if (pull_speed < 72.0f) pull_speed = 72.0f;
                player_apply_force(player, (vdx / dist) * pull_speed * dt, (vdy / dist) * pull_speed * dt);
            }
        }
    }

    /* 2. Atualiza Projeteis */
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bm->bullets[i].active) continue;

        Bullet *b = &bm->bullets[i];
        b->life -= dt;
        if (b->life <= 0.0f) {
            b->active = false;
            continue;
        }

        /* Curva suave de Homing (HOMING, BLIND e CONFUSE perseguem por 3.0s igual ao Python) */
        if ((b->type == BULLET_HOMING || b->type == BULLET_BLIND || b->type == BULLET_CONFUSE) && b->homing_timer > 0.0f) {
            b->homing_timer -= dt;
            float hdx = p_center.x - b->pos.x;
            float hdy = p_center.y - b->pos.y;
            float hdist = sqrtf(hdx * hdx + hdy * hdy);
            if (hdist > 1.0f) {
                float target_spd = (b->type == BULLET_HOMING) ? 192.0f : 120.0f;
                float target_vx = (hdx / hdist) * target_spd;
                float target_vy = (hdy / hdist) * target_spd;
                float steer = 1.0f - powf(0.95f, dt * 60.0f);
                b->vel.x = b->vel.x * (1.0f - steer) + target_vx * steer;
                b->vel.y = b->vel.y * (1.0f - steer) + target_vy * steer;
            }
        }

        b->pos.x += b->vel.x * dt;
        b->pos.y += b->vel.y * dt;

        /* Despawn nos limites da Arena de Combate (evita vazar sobre a caixa de texto) */
        if (b->pos.x < (float)ARENA_MARGIN_X || b->pos.x > (float)(SCREEN_WIDTH - ARENA_MARGIN_X) ||
            b->pos.y < (float)ARENA_MARGIN_TOP || b->pos.y > (float)(SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM)) {
            b->active = false;
            continue;
        }

        /* Colisao Circulo vs Retangulo do Player */
        if (CheckCollisionCircleRec(b->pos, b->radius, player->rect)) {
            b->active = false;

            if (b->type == BULLET_BLIND) {
                typing_engine_apply_blindness(te, DURATION_BLIND);
                if (status_applied_out) *status_applied_out = "BLIND";
            } else if (b->type == BULLET_CONFUSE) {
                player_apply_confuse(player, DURATION_CONFUSE);
                if (status_applied_out) *status_applied_out = "CONFUSE";
            } else {
                if (player_take_damage(player, 1)) {
                    hit_player = true;
                }
            }
        }
    }

    /* 3. Atualiza Lasers */
    for (int i = 0; i < MAX_LASERS; i++) {
        if (!bm->lasers[i].active) continue;

        Laser *l = &bm->lasers[i];
        if (l->warning_timer > 0.0f) {
            l->warning_timer -= dt;
            if (l->warning_timer <= 0.0f) {
                l->is_firing = true;
            }
        } else if (l->active_timer > 0.0f) {
            l->active_timer -= dt;
            if (!l->has_damaged && CheckCollisionRecs(l->rect, player->rect)) {
                if (player_take_damage(player, 1)) {
                    l->has_damaged = true;
                    hit_player = true;
                }
            }
            if (l->active_timer <= 0.0f) {
                l->active = false;
            }
        }
    }

    return hit_player;
}

void bullet_mgr_draw(const BulletManager *bm) {
    /* 1. Lasers Telegrafados (Faixa pulsante vermelha -> Feixe branco/amarelo intenso) */
    for (int i = 0; i < MAX_LASERS; i++) {
        if (!bm->lasers[i].active) continue;
        const Laser *l = &bm->lasers[i];
        if (!l->is_firing) {
            float elapsed = LASER_WARN_TIME - l->warning_timer;
            float pulse = fabsf(sinf(elapsed * 14.0f));
            unsigned char alpha = (unsigned char)(45.0f + pulse * 135.0f);
            DrawRectangleRec(l->rect, (Color){ 255, 30, 30, alpha });
            DrawRectangleLinesEx(l->rect, 2.0f, (Color){ 255, 80, 80, 255 });
        } else {
            DrawRectangleRec(l->rect, COLOR_LASER_BEAM);
            DrawRectangleLinesEx(l->rect, 4.0f, (Color){ 255, 230, 60, 255 });
        }
    }

    /* 2. Vortex Gravitacional com Particulas de Succao */
    if (bm->vortex.active) {
        float progress = bm->vortex.duration / bm->vortex.max_duration;
        if (progress < 0.0f) progress = 0.0f;
        float r_vis = 55.0f + sinf(bm->vortex.angle * 2.0f) * 6.0f;

        for (int i = 0; i < VORTEX_PARTICLES; i++) {
            float px = bm->vortex.pos.x + cosf(bm->vortex.particles[i].angle) * bm->vortex.particles[i].r;
            float py = bm->vortex.pos.y + sinf(bm->vortex.particles[i].angle) * bm->vortex.particles[i].r;
            unsigned char pa = (unsigned char)(210.0f * (bm->vortex.particles[i].r / 170.0f) * progress);
            DrawCircleV((Vector2){ px, py }, 2.5f, (Color){ 180, 70, 255, pa });
        }

        unsigned char a = (unsigned char)(160.0f * progress);
        DrawCircleV(bm->vortex.pos, r_vis, (Color){ 30, 10, 60, a });
        DrawCircleLines((int)bm->vortex.pos.x, (int)bm->vortex.pos.y, r_vis * 0.75f, (Color){ 170, 50, 240, a });
        DrawCircleLines((int)bm->vortex.pos.x, (int)bm->vortex.pos.y, r_vis * 0.50f, (Color){ 220, 120, 255, 220 });
        DrawCircleV(bm->vortex.pos, r_vis * 0.35f, (Color){ 0, 0, 0, 240 });
    }

    /* 3. Projeteis com Rastro de Movimento (Tail/Streak) e Nucleo Brilhante */
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bm->bullets[i].active) continue;
        const Bullet *b = &bm->bullets[i];

        /* Rastro de velocidade */
        if (fabsf(b->vel.x) > 10.0f || fabsf(b->vel.y) > 10.0f) {
            Vector2 tail = (Vector2){
                b->pos.x - (b->vel.x / 60.0f) * 3.5f,
                b->pos.y - (b->vel.y / 60.0f) * 3.5f
            };
            float thick = (b->radius - 1.5f > 2.0f) ? (b->radius - 1.5f) : 2.0f;
            DrawLineEx(tail, b->pos, thick, b->color);
        }

        /* Corpo principal */
        DrawCircleV(b->pos, b->radius, b->color);

        /* Nucleo interno brilhante igual ao Python */
        Color core_c = WHITE;
        if (b->type == BULLET_HOMING) core_c = (Color){ 200, 255, 200, 255 };
        else if (b->type == BULLET_BLIND) core_c = (Color){ 255, 180, 255, 255 };
        else if (b->type == BULLET_CONFUSE) core_c = (Color){ 255, 255, 100, 255 };

        float core_r = (b->radius - 3.0f > 2.0f) ? (b->radius - 3.0f) : 2.0f;
        DrawCircleV(b->pos, core_r, core_c);
    }
}
