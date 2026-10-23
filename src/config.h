#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

/* Dimensoes da Tela */
#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 700
#define TARGET_FPS 60

/* Limites da Arena de Combate */
#define ARENA_MARGIN_X 40
#define ARENA_MARGIN_TOP 70
#define ARENA_MARGIN_BOTTOM 130

/* Paleta de Cores Neon / Cyberpunk */
#define COLOR_BG            (Color){ 15, 17, 26, 255 }
#define COLOR_ARENA_BORDER  (Color){ 60, 70, 100, 255 }
#define COLOR_ARENA_GRID    (Color){ 25, 28, 45, 255 }

#define COLOR_PLAYER        (Color){ 0, 240, 255, 255 }
#define COLOR_PLAYER_OUTLINE (Color){ 255, 255, 255, 255 }

#define COLOR_BOSS          (Color){ 255, 60, 80, 255 }
#define COLOR_BOSS_HARD     (Color){ 255, 20, 50, 255 }

#define COLOR_BULLET_NORMAL (Color){ 255, 80, 80, 255 }
#define COLOR_BULLET_HOMING (Color){ 255, 200, 50, 255 }
#define COLOR_BULLET_BLIND  (Color){ 180, 70, 255, 255 }
#define COLOR_BULLET_CONFUSE (Color){ 255, 0, 180, 255 }

#define COLOR_LASER_WARNING (Color){ 255, 255, 0, 255 }
#define COLOR_LASER_BEAM    (Color){ 255, 30, 60, 255 }
#define COLOR_VORTEX        (Color){ 120, 40, 255, 255 }

#define COLOR_TEXT_TYPED    (Color){ 50, 255, 120, 255 }
#define COLOR_TEXT_CURRENT  (Color){ 255, 220, 0, 255 }
#define COLOR_TEXT_UNTYPED  (Color){ 160, 175, 210, 255 }
#define COLOR_TEXT_ERROR    (Color){ 255, 60, 80, 255 }

#define COLOR_TYPING_BG     (Color){ 20, 22, 35, 255 }
#define COLOR_TYPING_BORDER (Color){ 60, 70, 100, 255 }

/* Jogador */
#define PLAYER_SIZE 20
#define PLAYER_SPEED 220.0f
#define PLAYER_MAX_HP 5
#define PLAYER_IFRAME_DURATION 1.0f

/* Chefe */
#define BOSS_SIZE 60
#define BOSS_MAX_HP 1000

/* Dificuldades */
#define DIFFICULTY_NORMAL 1
#define DIFFICULTY_HARD 2

/* Duracoes de Efeitos */
#define DURATION_BLIND 3.5f
#define DURATION_CONFUSE 4.0f

/* Regras de Pontuacao e Alinhamento Etico (Caio Brayner - PI2-90) */
#define SCORE_PERFECT          150
#define SCORE_STABLE           100
#define SCORE_PATCHED          50
#define SCORE_ERROR_PENALTY     5
#define BOSS_DAMAGE_PER_PHRASE 100
#define BOSS_ALIGNMENT_STEP    10
#define TOTAL_DIRECTIVES       10

#endif /* CONFIG_H */
