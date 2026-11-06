int boss_get_phase(const Boss *b) {
    if (b->alignment_pct <= 33) return 1;
    if (b->alignment_pct <= 66) return 2;
    return 3;
}
    /* Cadência: cada fase atira mais rápido */
    float rate = diff_mult * ((phase == 1) ? 1.0f : (phase == 2) ? 0.85f : 0.7f);

    /* --- Base (todas as fases): tiro mirado + anel --- */
    b->timer_aimed += dt;
    if (b->timer_aimed >= 1.4f * rate) {
        b->timer_aimed = 0.0f;
        bullet_mgr_spawn_aimed(bm, center, player_pos, 180.0f, BULLET_NORMAL);
    }
    b->timer_ring += dt;
    if (b->timer_ring >= 2.6f * rate) {
        b->timer_ring = 0.0f;
        bullet_mgr_spawn_ring(bm, center, (b->difficulty == DIFFICULTY_HARD) ? 14 : 10, 140.0f, BULLET_NORMAL);
    }

    /* --- FASE 1 (0-33%): Espiral Dupla Rotativa --- */
    if (phase == 1) {
        b->timer_spiral += dt;
        if (b->timer_spiral >= 0.18f * diff_mult) {
            b->timer_spiral = 0.0f;
            b->spiral_angle += 0.35f;
            Vector2 v1 = { cosf(b->spiral_angle) * 150.0f, sinf(b->spiral_angle) * 150.0f };
            Vector2 v2 = { cosf(b->spiral_angle + PI) * 150.0f, sinf(b->spiral_angle + PI) * 150.0f };
            bullet_mgr_spawn(bm, center, v1, 5.0f, BULLET_SPIRAL, 8.0f);
            bullet_mgr_spawn(bm, center, v2, 5.0f, BULLET_SPIRAL, 8.0f);
        }
    }

    /* --- FASE 2 (34-66%): Chuva de Dados + Prompt Injection --- */
    if (phase >= 2) {
        b->timer_rain += dt;   /* já era o timer do confuse */
        if (b->timer_rain >= 3.5f * rate) {
            b->timer_rain = 0.0f;
            bullet_mgr_spawn_aimed(bm, center, player_pos, 160.0f, BULLET_CONFUSE);
        }
    }
    if (phase == 2) {
        b->timer_cascade += dt;
        if (b->timer_cascade >= 0.06f * rate) {
            b->timer_cascade = 0.0f;
            float x = (float)GetRandomValue(ARENA_MARGIN_X, SCREEN_WIDTH - ARENA_MARGIN_X);
            float speed = (float)GetRandomValue(180, 300);
            BulletType bt = (GetRandomValue(0, 11) == 0) ? BULLET_BLIND : BULLET_RAIN;
            bullet_mgr_spawn(bm, (Vector2){ x, (float)ARENA_MARGIN_TOP },
                             (Vector2){ 0.0f, speed }, 4.0f, bt, 6.0f);
        }
    }

    /* --- FASE 3 (67-100%): Leque + Laser + Vórtex --- */
    if (phase == 3) {
        b->timer_fan += dt;
        if (b->timer_fan >= 0.9f * rate) {
            b->timer_fan = 0.0f;
            const int count = 9;
            const float arc = 80.0f * DEG2RAD;
            float base = atan2f(player_pos.y - center.y, player_pos.x - center.x);
            float step = arc / (float)(count - 1);
            for (int i = 0; i < count; i++) {
                float a = base - arc / 2.0f + step * (float)i;
                Vector2 vel = { cosf(a) * 210.0f, sinf(a) * 210.0f };
                bullet_mgr_spawn(bm, center, vel, 5.0f, BULLET_SPREAD, 8.0f);
            }
        }

        b->timer_laser += dt;
        if (b->timer_laser >= 4.0f * rate) {
            b->timer_laser = 0.0f;
            bullet_mgr_spawn_laser(bm, player_pos.x - 20.0f, ARENA_MARGIN_TOP, 40.0f,
                                   SCREEN_HEIGHT - ARENA_MARGIN_TOP - ARENA_MARGIN_BOTTOM, 1.0f, 0.6f);
        }
        b->timer_vortex += dt;
        if (b->timer_vortex >= 7.0f) {
            b->timer_vortex = 0.0f;
            bullet_mgr_spawn_vortex(bm, center, 220.0f, 150.0f, 4.0f);
        }
    }


    int phase = boss_get_phase(b);
Color fill_color = (phase == 1) ? COLOR_BOSS_PHASE1
                 : (phase == 2) ? COLOR_BOSS_PHASE2
                 : COLOR_BOSS_PHASE3;