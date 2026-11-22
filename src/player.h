#ifndef PLAYER_H
#define PLAYER_H

#include "config.h"

#define MAX_TRAIL 8

typedef struct {
    Rectangle rect;
    float speed;
    int hp;
    int max_hp;
    float iframe_timer;
    float confuse_timer;
    float ext_fx;
    float ext_fy;
    bool is_alive;
    Vector2 trail[MAX_TRAIL];
    int trail_len;
} Player;

void player_init(Player *p, float x, float y);
void player_handle_input(Player *p);
void player_handle_input_ex(Player *p, int control_mode, Vector2 mouse_arena_pos);
void player_apply_force(Player *p, float fx, float fy);
void player_apply_confuse(Player *p, float duration);
void player_update(Player *p, float dt);
bool player_take_damage(Player *p, int damage);
void player_draw(const Player *p);

#endif /* PLAYER_H */
