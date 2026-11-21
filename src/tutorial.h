
#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "config.h"
#include "player.h"
#include "typing_engine.h"
#include "ui.h"

/* Modo Tutorial Guiado de AI Safety - atalho [T] no menu */

#define TUTORIAL_PHRASE "IA SEGURA PROTEGE AS PESSOAS"

#define TUTORIAL_MAX_ORBS 3
#define TUTORIAL_ORB_RADIUS 12.0f
#define TUTORIAL_KEY_COUNT 4

/* Passos do treino */
typedef enum {
    TUTORIAL_STEP_INTRO,
    TUTORIAL_STEP_BIAS,
    TUTORIAL_STEP_JAILBREAK,
    TUTORIAL_STEP_AGI,
    TUTORIAL_STEP_MOVE,
    TUTORIAL_STEP_TYPE,
    TUTORIAL_STEP_DONE
} TutorialStep;

/* Esfera de treino */
typedef struct {
    Vector2 pos;
    Vector2 vel;
    float hit_cooldown;
} TrainingOrb;

/* Estado completo do tutorial */
typedef struct {
    TutorialStep step;
    bool key_used[TUTORIAL_KEY_COUNT];
    Player player;
    TypingEngine typing_engine;
    UIManager ui;
    TrainingOrb orbs[TUTORIAL_MAX_ORBS];
} Tutorial;

/* Inicializa o tutorial */
void tutorial_init(Tutorial *t);

/* Atualiza o tutorial */
void tutorial_update(Tutorial *t, float dt);

/* Verifica se foi concluído */
bool tutorial_is_complete(const Tutorial *t);

/* Desenha a tela do tutorial */
void tutorial_draw(const Tutorial *t);

#endif /* TUTORIAL_H */
