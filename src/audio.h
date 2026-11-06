#ifndef AUDIO_H
#define AUDIO_H

#include "config.h"

/* =========================================================================
 * Modulo de Feedback Sonoro Sintetizado (PI2-214 / PI2-33 - Joao Gabriel)
 * Gera ondas PCM 16-bit proceduralmente em memoria via Raylib Audio API,
 * eliminando dependencia de arquivos externos (.wav/.ogg) e resolvendo a
 * Issue #3 (CT-US06-01 e CT-US07-05).
 * ========================================================================= */

void audio_init(void);
void audio_close(void);

void audio_play_key_ok(void);
void audio_play_key_error(void);
void audio_play_patch_complete(void);
void audio_play_player_hit(void);
void audio_play_victory(void);
void audio_play_game_over(void);

#endif /* AUDIO_H */
