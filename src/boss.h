#ifndef BOSS_H
#define BOSS_H

#include "config.h"
#include "bullet.h"

typedef struct {
    Rectangle rect;
    int hp;
    int max_hp;
    int difficulty;
    float base_x;
    float base_y;
    float move_timer;
    float pulse_timer;
    float hit_flash_timer;

    /* Timers de Padroes de Ataque (Fieis ao boss.py) */
    float timer_ring;
    float timer_aimed;
    float timer_spiral;
    float timer_rain;
    float timer_homing;
    float timer_cross;
    float timer_shockwave;
    float timer_special;
    float timer_laser;
    float timer_vortex;

    float spiral_angle;
    float spiral_angle_2;
    int alignment_pct;
} Boss;

void boss_init(Boss *b, float x, float y, int difficulty);
int boss_get_phase(const Boss *b);
void boss_take_damage(Boss *b, int damage);
void boss_update(Boss *b, float dt, BulletManager *bm, Vector2 player_pos);
void boss_draw(const Boss *b);

#endif /* BOSS_H */
