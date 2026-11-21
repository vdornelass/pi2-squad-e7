#ifndef CONFIG_H
#define CONFIG_H

#include "raylib.h"

/* Dimensoes da Tela Virtual (720p Widescreen) */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define TARGET_FPS 60

/* Limites da Arena de Combate */
#define ARENA_MARGIN_X 80
#define ARENA_MARGIN_TOP 80
#define ARENA_MARGIN_BOTTOM 150

/* Paleta de Cores Neon / Cyberpunk (Fiel ao config.py) */
#define COLOR_BG             (Color){ 12, 12, 20, 255 }
#define COLOR_ARENA_BG       (Color){ 18, 18, 30, 255 }
#define COLOR_ARENA_BORDER   (Color){ 60, 70, 100, 255 }
#define COLOR_ARENA_GRID     (Color){ 25, 28, 45, 255 }

#define COLOR_PLAYER         (Color){ 0, 200, 255, 255 }
#define COLOR_PLAYER_OUTLINE (Color){ 180, 240, 255, 255 }

#define COLOR_BOSS           (Color){ 235, 45, 60, 255 }
#define COLOR_BOSS_HARD      (Color){ 255, 30, 90, 255 }
#define COLOR_BOSS_OUTLINE   (Color){ 255, 120, 130, 255 }

/* Cores de Projeteis por Padrao (Igual ao Python) */
#define COLOR_BULLET_DEFAULT (Color){ 255, 210, 60, 255 }
#define COLOR_BULLET_FAST    (Color){ 255, 70, 70, 255 }
#define COLOR_BULLET_RING    (Color){ 170, 90, 255, 255 }
#define COLOR_BULLET_HOMING  (Color){ 50, 255, 150, 255 }
#define COLOR_BULLET_WALL    (Color){ 255, 120, 0, 255 }
#define COLOR_BULLET_BLIND   (Color){ 180, 70, 255, 255 }
#define COLOR_BULLET_CONFUSE (Color){ 255, 0, 180, 255 }
#define COLOR_BULLET_NORMAL  COLOR_BULLET_DEFAULT

/* Lasers & Vortex */
#define COLOR_LASER_WARNING  (Color){ 255, 40, 40, 255 }
#define COLOR_LASER_BEAM     (Color){ 255, 255, 200, 240 }
#define COLOR_VORTEX         (Color){ 170, 50, 240, 255 }

#define COLOR_TEXT_TYPED     (Color){ 50, 255, 120, 255 }
#define COLOR_TEXT_CURRENT   (Color){ 255, 230, 40, 255 }
#define COLOR_TEXT_UNTYPED   (Color){ 180, 190, 210, 255 }
#define COLOR_TEXT_ERROR     (Color){ 255, 60, 60, 255 }

#define COLOR_TYPING_BG      (Color){ 22, 24, 38, 255 }
#define COLOR_TYPING_BORDER  (Color){ 80, 90, 130, 255 }

/* Jogador */
#define PLAYER_SIZE 24
#define PLAYER_SPEED 280.0f
#define PLAYER_MAX_HP 5
#define PLAYER_IFRAME_DURATION 2.0f

/* Esquemas de Controle de Movimento */
#define CONTROL_ARROWS_ONLY  0
#define CONTROL_MOUSE        1
#define CONTROL_WASD_ARROWS  2

/* Chefe */
#define BOSS_SIZE 64
#define BOSS_MAX_HP 1000

/* Dificuldades */
#define DIFFICULTY_NORMAL 1
#define DIFFICULTY_HARD 2

/* Duracoes de Efeitos (Iguais ao Python) */
#define DURATION_BLIND 3.0f
#define DURATION_CONFUSE 3.5f
#define LASER_WARN_TIME 1.5f
#define LASER_BEAM_TIME 0.4f

/* Regras de Pontuacao e Alinhamento Etico */
#define SCORE_PERFECT          150
#define SCORE_STABLE           100
#define SCORE_PATCHED          50
#define BOSS_DAMAGE_PER_PHRASE 100
#define BOSS_ALIGNMENT_STEP    10
#define TOTAL_DIRECTIVES       10

#endif /* CONFIG_H */
