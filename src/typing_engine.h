#ifndef TYPING_ENGINE_H
#define TYPING_ENGINE_H

#include "config.h"

#define MAX_PHRASES 10
#define MAX_PHRASE_LEN 128

typedef struct {
    char phrases[MAX_PHRASES][MAX_PHRASE_LEN];
    int phrase_count;
    int phrase_index;
    int char_index;
    float error_flash_timer;
    float blind_timer;
    int current_phrase_errors;
    int total_completed;
    int total_typed;
    int total_errors;
} TypingEngine;

void typing_engine_init(TypingEngine *te);
void typing_engine_reset(TypingEngine *te);
void typing_engine_update(TypingEngine *te, float dt);
const char *typing_engine_handle_key(TypingEngine *te, int key, int *errors_out);
void typing_engine_on_player_hit(TypingEngine *te);
void typing_engine_apply_blindness(TypingEngine *te, float duration);
const char *typing_engine_get_current_phrase(const TypingEngine *te);
bool typing_engine_is_finished(const TypingEngine *te);
int typing_engine_get_accuracy(const TypingEngine *te);

#endif /* TYPING_ENGINE_H */
