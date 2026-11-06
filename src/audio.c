#include "audio.h"
#include <stdlib.h>
#include <math.h>

#define AUDIO_SAMPLE_RATE 44100

static Sound sfx_key_ok;
static Sound sfx_key_error;
static Sound sfx_patch_complete;
static Sound sfx_player_hit;
static Sound sfx_victory;
static Sound sfx_game_over;
static bool audio_ready = false;

/* Gera um efeito sonoro sintetizado de dois estagios de frequencia com envelope linear */
static Sound generate_tone_sfx(float freq_start, float freq_end, float duration_sec, float volume, bool square_wave) {
    Sound snd = { 0 };
    if (!audio_ready) return snd;

    unsigned int frames = (unsigned int)(AUDIO_SAMPLE_RATE * duration_sec);
    if (frames == 0) return snd;

    short *pcm = (short *)malloc(frames * sizeof(short));
    if (pcm == NULL) return snd;

    float phase = 0.0f;
    for (unsigned int i = 0; i < frames; i++) {
        float t = (float)i / (float)frames;
        float freq = freq_start + (freq_end - freq_start) * t;
        float envelope = 1.0f - t; /* Decay suave para evitar cliques */
        if (t < 0.05f) {
            envelope = t / 0.05f;  /* Attack rapido */
        }

        phase += (2.0f * PI * freq) / (float)AUDIO_SAMPLE_RATE;
        if (phase > 2.0f * PI) {
            phase -= 2.0f * PI;
        }

        float sample_val = sinf(phase);
        if (square_wave) {
            sample_val = (sample_val >= 0.0f) ? 0.8f : -0.8f;
        }

        float amp = sample_val * envelope * volume * 32000.0f;
        if (amp > 32767.0f) amp = 32767.0f;
        if (amp < -32767.0f) amp = -32767.0f;
        pcm[i] = (short)amp;
    }

    Wave wave;
    wave.frameCount = frames;
    wave.sampleRate = AUDIO_SAMPLE_RATE;
    wave.sampleSize = 16;
    wave.channels = 1;
    wave.data = pcm;

    snd = LoadSoundFromWave(wave);
    free(pcm);
    return snd;
}

void audio_init(void) {
    InitAudioDevice();
    audio_ready = IsAudioDeviceReady();
    if (!audio_ready) return;

    SetMasterVolume(0.75f);

    /* Clique curto de terminal ao digitar caractere correto */
    sfx_key_ok = generate_tone_sfx(880.0f, 1120.0f, 0.035f, 0.25f, false);

    /* Buzzer grave de erro de sintaxe (CT-US06-01) */
    sfx_key_error = generate_tone_sfx(210.0f, 130.0f, 0.14f, 0.55f, true);

    /* Acorde ascendente de confirmacao de patch / diretriz concluida (CT-US07-05) */
    sfx_patch_complete = generate_tone_sfx(523.25f, 1046.50f, 0.26f, 0.50f, false);

    /* Alerta de colisao / dano sofrido pelo jogador */
    sfx_player_hit = generate_tone_sfx(180.0f, 75.0f, 0.22f, 0.65f, true);

    /* Fanfarra sintetica de vitoria (convergencia etica) */
    sfx_victory = generate_tone_sfx(440.0f, 1320.0f, 0.50f, 0.55f, false);

    /* Tom descendente de falha critica (Game Over) */
    sfx_game_over = generate_tone_sfx(360.0f, 90.0f, 0.55f, 0.60f, true);
}

void audio_close(void) {
    if (!audio_ready) return;

    UnloadSound(sfx_key_ok);
    UnloadSound(sfx_key_error);
    UnloadSound(sfx_patch_complete);
    UnloadSound(sfx_player_hit);
    UnloadSound(sfx_victory);
    UnloadSound(sfx_game_over);

    CloseAudioDevice();
    audio_ready = false;
}

void audio_play_key_ok(void) {
    if (audio_ready) PlaySound(sfx_key_ok);
}

void audio_play_key_error(void) {
    if (audio_ready) PlaySound(sfx_key_error);
}

void audio_play_patch_complete(void) {
    if (audio_ready) PlaySound(sfx_patch_complete);
}

void audio_play_player_hit(void) {
    if (audio_ready) PlaySound(sfx_player_hit);
}

void audio_play_victory(void) {
    if (audio_ready) PlaySound(sfx_victory);
}

void audio_play_game_over(void) {
    if (audio_ready) PlaySound(sfx_game_over);
}
