#include "patch_feedback.h"
#include "raylib.h"
#include <math.h>
#include <stdbool.h>

/* Compatibilidade com as APIs da raylib 5.0 e 5.5+/6.x. */
#if RAYLIB_VERSION_MAJOR > 5 || (RAYLIB_VERSION_MAJOR == 5 && RAYLIB_VERSION_MINOR >= 5)
    #define PATCH_SOUND_IS_VALID IsSoundValid
#else
    #define PATCH_SOUND_IS_VALID IsSoundReady
#endif

#define SAMPLE_RATE 22050
#define FRAME_COUNT 4410

static Sound grade_sounds[3];
static Sound error_sound;
static bool audio_ready = false;

/* Cria sons curtos sem depender de arquivos WAV. */
static Sound create_tone(float freq) {
    short samples[FRAME_COUNT];
    for (int i = 0; i < FRAME_COUNT; i++) {
        float t = (float)i / SAMPLE_RATE;
        float fade = 1.0f - (float)i / FRAME_COUNT;
        samples[i] = (short)(sinf(2.0f * PI * freq * t) * fade * 9000.0f);
    }
    Wave wave = { 0 };
    wave.frameCount = FRAME_COUNT;
    wave.sampleRate = SAMPLE_RATE;
    wave.sampleSize = 16;
    wave.channels = 1;
    wave.data = samples;
    return LoadSoundFromWave(wave);
}

void patch_feedback_init(void) {
    InitAudioDevice();
    audio_ready = IsAudioDeviceReady();
    if (!audio_ready) return;
    grade_sounds[0] = create_tone(880.0f);
    grade_sounds[1] = create_tone(660.0f);
    grade_sounds[2] = create_tone(440.0f);
    error_sound = create_tone(220.0f);
}

void patch_feedback_play_grade(int grade) {
    if (audio_ready && grade >= 0 && grade < 3 &&
        PATCH_SOUND_IS_VALID(grade_sounds[grade])) PlaySound(grade_sounds[grade]);
}

void patch_feedback_play_error(void) {
    if (audio_ready && PATCH_SOUND_IS_VALID(error_sound)) PlaySound(error_sound);
}

void patch_feedback_shutdown(void) {
    if (!audio_ready) return;
    for (int i = 0; i < 3; i++)
        if (PATCH_SOUND_IS_VALID(grade_sounds[i])) UnloadSound(grade_sounds[i]);
    if (PATCH_SOUND_IS_VALID(error_sound)) UnloadSound(error_sound);
    CloseAudioDevice();
    audio_ready = false;
}
