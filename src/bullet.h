#ifndef BULLET_H
#define BULLET_H

#include "config.h"
#include "player.h"
#include "typing_engine.h"

#define MAX_BULLETS 1000
#define MAX_LASERS 6
#define VORTEX_PARTICLES 24

typedef enum {
    BULLET_NORMAL,
    BULLET_HOMING,
    BULLET_BLIND,
    BULLET_CONFUSE
} BulletType;

typedef struct {
    Vector2 pos;
    Vector2 vel;
    float radius;
    Color color;
    BulletType type;
    float homing_timer;
    float life;
    float max_life;
    bool active;
} Bullet;

typedef struct {
    Rectangle rect;
    bool is_vertical;
    float warning_timer;
    float active_timer;
    bool is_firing;
    bool has_damaged;
    bool active;
} Laser;

typedef struct {
    float r;
    float angle;
    float speed;
} VortexParticle;

typedef struct {
    Vector2 pos;
    float radius;
    float pull_strength;
    float duration;
    float max_duration;
    float angle;
    VortexParticle particles[VORTEX_PARTICLES];
    bool active;
} Vortex;

typedef struct {
    Bullet bullets[MAX_BULLETS];
    Laser lasers[MAX_LASERS];
    Vortex vortex;
} BulletManager;

void bullet_mgr_init(BulletManager *bm);
void bullet_mgr_clear(BulletManager *bm);

/* Spawners base e avancados (fieis ao bullet.py) */
void bullet_mgr_spawn_ex(BulletManager *bm, Vector2 pos, Vector2 vel, float radius, Color color, BulletType type, float life);
void bullet_mgr_spawn(BulletManager *bm, Vector2 pos, Vector2 vel, float radius, BulletType type, float life);
void bullet_mgr_spawn_ring_ex(BulletManager *bm, Vector2 pos, int count, float speed, Color color, float angle_offset);
void bullet_mgr_spawn_ring(BulletManager *bm, Vector2 pos, int count, float speed, BulletType type);
void bullet_mgr_spawn_spiral(BulletManager *bm, Vector2 pos, float angle, float speed, Color color);
void bullet_mgr_spawn_aimed_ex(BulletManager *bm, Vector2 pos, Vector2 target, float speed, float spread, Color color);
void bullet_mgr_spawn_aimed(BulletManager *bm, Vector2 pos, Vector2 target, float speed, BulletType type);
void bullet_mgr_spawn_homing(BulletManager *bm, Vector2 pos, float speed);
void bullet_mgr_spawn_blind_bullet(BulletManager *bm, Vector2 pos, float speed);
void bullet_mgr_spawn_confuse_bullet(BulletManager *bm, Vector2 pos, float speed);
void bullet_mgr_spawn_cross(BulletManager *bm, Vector2 pos, float speed, float angle_offset);
void bullet_mgr_spawn_shockwave(BulletManager *bm, Vector2 pos, int rings, float speed);
void bullet_mgr_spawn_rain(BulletManager *bm, float speed, int gap_x, int gap_width);
void bullet_mgr_spawn_laser_warning(BulletManager *bm, bool is_vertical, float target_x, float target_y);
void bullet_mgr_spawn_laser(BulletManager *bm, float x, float y, float w, float h, float warning_time, float active_time);
void bullet_mgr_spawn_vortex(BulletManager *bm, Vector2 pos, float radius, float strength, float duration);

/* Atualizacao e deteccao de colisao */
bool bullet_mgr_update(BulletManager *bm, float dt, Player *player, TypingEngine *te, const char **status_applied_out);
void bullet_mgr_draw(const BulletManager *bm);

#endif /* BULLET_H */
