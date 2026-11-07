#include "tutorial.h"
#include <stdio.h>
#include <string.h>

/* Rotulos das teclas do passo 1, na mesma ordem de key_used[] */
static const char *KEY_LABELS[TUTORIAL_KEY_COUNT] = { "W", "A", "S", "D" };

/* Desenha um texto centralizado horizontalmente na tela */
static void draw_text_centered(const char *txt, int y, int font_size, Color color) {
    int w = MeasureText(txt, font_size);
    DrawText(txt, SCREEN_WIDTH / 2 - w / 2, y, font_size, color);
}

/* Descarta caracteres pendentes na fila do raylib (ex.: o 'T' usado no menu ou as
   letras WASD do passo 1), para nao virarem "erro de sintaxe" na digitacao. */
static void drain_char_queue(void) {
    while (GetCharPressed() > 0) { }
}

void tutorial_init(Tutorial *t) {
    t->step = TUTORIAL_STEP_MOVE;
    for (int i = 0; i < TUTORIAL_KEY_COUNT; i++) {
        t->key_used[i] = false;
    }

    /* Mesma posicao inicial do combate real */
    player_init(&t->player, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 200.0f);
    ui_init(&t->ui);

    /* Motor de digitacao com UMA unica frase de teste */
    typing_engine_init(&t->typing_engine);
    t->typing_engine.phrase_count = 1;
    strncpy(t->typing_engine.phrases[0], TUTORIAL_PHRASE, MAX_PHRASE_LEN - 1);
    t->typing_engine.phrases[0][MAX_PHRASE_LEN - 1] = '\0';

    /* Esferas de treino em posicoes e velocidades fixas (sem aleatoriedade) */
    t->orbs[0] = (TrainingOrb){ { 200.0f, 160.0f }, { 140.0f,  90.0f }, 0.0f };
    t->orbs[1] = (TrainingOrb){ { 700.0f, 220.0f }, { -120.0f, 110.0f }, 0.0f };
    t->orbs[2] = (TrainingOrb){ { 450.0f, 380.0f }, { 100.0f, -130.0f }, 0.0f };
}

/* Move as esferas, faz quicar nas bordas da arena e avisa (sem dano) se tocarem no jogador */
static void tutorial_update_orbs(Tutorial *t, float dt) {
    float min_x = ARENA_MARGIN_X + TUTORIAL_ORB_RADIUS;
    float max_x = SCREEN_WIDTH - ARENA_MARGIN_X - TUTORIAL_ORB_RADIUS;
    float min_y = ARENA_MARGIN_TOP + TUTORIAL_ORB_RADIUS;
    float max_y = SCREEN_HEIGHT - ARENA_MARGIN_BOTTOM - TUTORIAL_ORB_RADIUS;

    for (int i = 0; i < TUTORIAL_MAX_ORBS; i++) {
        TrainingOrb *orb = &t->orbs[i];

        orb->pos.x += orb->vel.x * dt;
        orb->pos.y += orb->vel.y * dt;

        if (orb->pos.x < min_x) { orb->pos.x = min_x; orb->vel.x = -orb->vel.x; }
        if (orb->pos.x > max_x) { orb->pos.x = max_x; orb->vel.x = -orb->vel.x; }
        if (orb->pos.y < min_y) { orb->pos.y = min_y; orb->vel.y = -orb->vel.y; }
        if (orb->pos.y > max_y) { orb->pos.y = max_y; orb->vel.y = -orb->vel.y; }

        if (orb->hit_cooldown > 0.0f) {
            orb->hit_cooldown -= dt;
        }

        /* Tocou no jogador: so mostra o aviso. A vida NUNCA e alterada no tutorial. */
        if (orb->hit_cooldown <= 0.0f && CheckCollisionCircleRec(orb->pos, TUTORIAL_ORB_RADIUS, t->player.rect)) {
            orb->hit_cooldown = 1.0f;
            ui_spawn_floating_text(&t->ui, "SEM DANO (TREINO)",
                                   t->player.rect.x + t->player.rect.width / 2.0f,
                                   t->player.rect.y - 30.0f, COLOR_TEXT_TYPED, 22, 0.8f);
        }
    }
}

/* Passo 1: marca W/A/S/D (ou setas) que o jogador ja usou. Retorna true quando as 4 foram usadas. */
static bool tutorial_track_movement_keys(Tutorial *t) {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    t->key_used[0] = true;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  t->key_used[1] = true;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  t->key_used[2] = true;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) t->key_used[3] = true;

    for (int i = 0; i < TUTORIAL_KEY_COUNT; i++) {
        if (!t->key_used[i]) return false;
    }
    return true;
}

/* Passo 2: envia uma tecla ao motor de digitacao. Erros nao tiram vida, so mostram o aviso. */
static void tutorial_feed_key(Tutorial *t, int key) {
    int errors = 0;
    const char *res = typing_engine_handle_key(&t->typing_engine, key, &errors);
    if (res == NULL) return;

    if (strcmp(res, "COMPLETED") == 0) {
        t->step = TUTORIAL_STEP_DONE;
        ui_spawn_particle_burst(&t->ui, SCREEN_WIDTH / 2.0f, 300.0f, COLOR_TEXT_TYPED, 24);
        ui_spawn_floating_text(&t->ui, "PATCH DE TREINO APLICADO!", SCREEN_WIDTH / 2.0f, 280.0f,
                               COLOR_TEXT_TYPED, 28, 1.5f);
    } else if (strcmp(res, "ERROR") == 0) {
        /* Dentro da arena, para nao colidir com o rotulo "PATCH DE ALINHAMENTO" da caixa de digitacao */
        ui_spawn_floating_text(&t->ui, "ERRO DE SINTAXE! (SEM DANO)", SCREEN_WIDTH / 2.0f,
                               SCREEN_HEIGHT - 170.0f, COLOR_TEXT_ERROR, 24, 0.6f);
    }
}

/* Passo 2: le os caracteres digitados neste frame (mesma logica do combate, inclusive o
   fallback da barra de espaco quando o sistema nao a entrega em GetCharPressed). */
static void tutorial_process_typing(Tutorial *t) {
    bool space_handled = false;
    int key = GetCharPressed();
    while (key > 0) {
        if (key == ' ') space_handled = true;
        tutorial_feed_key(t, key);
        key = GetCharPressed();
    }

    if (!space_handled && IsKeyPressed(KEY_SPACE)) {
        tutorial_feed_key(t, ' ');
    }
}

void tutorial_update(Tutorial *t, float dt) {
    /* Movimento igual ao do combate real */
    player_handle_input(&t->player);
    player_update(&t->player, dt);

    tutorial_update_orbs(t, dt);
    typing_engine_update(&t->typing_engine, dt);

    if (t->step == TUTORIAL_STEP_MOVE) {
        bool all_keys_used = tutorial_track_movement_keys(t);
        drain_char_queue();
        if (all_keys_used) {
            t->step = TUTORIAL_STEP_TYPE;
            ui_spawn_floating_text(&t->ui, "MOVIMENTO DOMINADO!", SCREEN_WIDTH / 2.0f, 280.0f,
                                   COLOR_TEXT_TYPED, 28, 1.5f);
        }
    } else if (t->step == TUTORIAL_STEP_TYPE) {
        tutorial_process_typing(t);
    } else {
        drain_char_queue();
    }

    ui_update(&t->ui, dt);
}

bool tutorial_is_complete(const Tutorial *t) {
    return t->step == TUTORIAL_STEP_DONE;
}

/* Desenha as 4 caixas de tecla do passo 1 (verde = ja usada) */
static void tutorial_draw_key_boxes(const Tutorial *t, int y) {
    int box = 44;
    int gap = 14;
    int total_w = TUTORIAL_KEY_COUNT * box + (TUTORIAL_KEY_COUNT - 1) * gap;
    int x = SCREEN_WIDTH / 2 - total_w / 2;

    for (int i = 0; i < TUTORIAL_KEY_COUNT; i++) {
        int bx = x + i * (box + gap);
        if (t->key_used[i]) {
            DrawRectangle(bx, y, box, box, COLOR_TEXT_TYPED);
            DrawText(KEY_LABELS[i], bx + box / 2 - MeasureText(KEY_LABELS[i], 24) / 2, y + 10, 24, BLACK);
        } else {
            DrawRectangleLines(bx, y, box, box, COLOR_TEXT_UNTYPED);
            DrawText(KEY_LABELS[i], bx + box / 2 - MeasureText(KEY_LABELS[i], 24) / 2, y + 10, 24, COLOR_TEXT_UNTYPED);
        }
    }
}

/* Painel de instrucoes do passo atual */
static void tutorial_draw_panel(const Tutorial *t) {
    Rectangle panel = { SCREEN_WIDTH / 2.0f - 330.0f, 90.0f, 660.0f, 175.0f };
    DrawRectangleRec(panel, Fade(COLOR_TYPING_BG, 0.88f));
    DrawRectangleLinesEx(panel, 1.0f, COLOR_TYPING_BORDER);

    if (t->step == TUTORIAL_STEP_MOVE) {
        draw_text_centered("PASSO 1/2 - ESQUIVA", 102, 22, COLOR_TEXT_CURRENT);
        draw_text_centered("Mova o engenheiro com [W][A][S][D] ou as SETAS.", 136, 16, RAYWHITE);
        draw_text_centered("Use cada direcao pelo menos uma vez:", 158, 16, RAYWHITE);
        tutorial_draw_key_boxes(t, 184);
        draw_text_centered("As esferas vermelhas simulam projeteis. No treino elas NAO causam dano.", 238, 14,
                           COLOR_TEXT_UNTYPED);
    } else if (t->step == TUTORIAL_STEP_TYPE) {
        draw_text_centered("PASSO 2/2 - DIGITACAO DE PATCH", 102, 22, COLOR_TEXT_CURRENT);
        draw_text_centered("Digite a frase da caixa abaixo, letra por letra.", 136, 16, RAYWHITE);
        draw_text_centered("Voce pode se mover enquanto digita, como no combate real.", 160, 16, RAYWHITE);
        draw_text_centered("Teclas WASD que nao forem a letra atual apenas movem (nao contam erro).", 192, 14,
                           COLOR_TEXT_UNTYPED);
        draw_text_centered("Errar aqui NAO tira vida: este e um treino seguro.", 214, 14, COLOR_TEXT_UNTYPED);
    } else {
        char buf[64];
        draw_text_centered("TREINO CONCLUIDO!", 102, 30, COLOR_TEXT_TYPED);
        snprintf(buf, sizeof(buf), "Precisao no treino: %d%%", typing_engine_get_accuracy(&t->typing_engine));
        draw_text_centered(buf, 150, 18, RAYWHITE);
        draw_text_centered("[ENTER] INICIAR COMBATE REAL", 190, 20, COLOR_TEXT_CURRENT);
        draw_text_centered("[ESC] VOLTAR AO MENU", 222, 20, COLOR_TEXT_UNTYPED);
    }
}

void tutorial_draw(const Tutorial *t) {
    ui_draw_arena_grid();

    /* Esferas de treino (translucidas, para diferenciar dos projeteis reais) */
    for (int i = 0; i < TUTORIAL_MAX_ORBS; i++) {
        DrawCircleV(t->orbs[i].pos, TUTORIAL_ORB_RADIUS, Fade(COLOR_BULLET_NORMAL, 0.6f));
        DrawCircleLines((int)t->orbs[i].pos.x, (int)t->orbs[i].pos.y, TUTORIAL_ORB_RADIUS, COLOR_BULLET_NORMAL);
    }

    player_draw(&t->player);
    ui_draw_particles(&t->ui);

    /* Cabecalho */
    DrawText("MODO TREINO - PROTOCOLO DE TREINO", ARENA_MARGIN_X, 18, 22, COLOR_PLAYER);
    DrawText("Nada aqui vale pontos nem entra no ranking.", ARENA_MARGIN_X, 46, 14, COLOR_TEXT_UNTYPED);
    const char *esc_hint = "[ESC] VOLTAR AO MENU";
    DrawText(esc_hint, SCREEN_WIDTH - ARENA_MARGIN_X - MeasureText(esc_hint, 16), 22, 16, COLOR_TEXT_UNTYPED);

    tutorial_draw_panel(t);
    ui_draw_floating_texts(&t->ui);

    /* HUD: vida sempre cheia, pois o tutorial nao causa dano */
    ui_draw_player_hp(&t->player);

    if (t->step == TUTORIAL_STEP_TYPE) {
        ui_draw_typing_box(&t->typing_engine);
    }
}
