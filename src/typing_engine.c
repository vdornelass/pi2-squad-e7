#include "typing_engine.h"
#include <string.h>
#include <ctype.h>

static const char *DEFAULT_PHRASES[MAX_PHRASES] = {
    "CONSTITUICAO DE SEGURANCA ATIVADA",
    "ELIMINAR VIESES E DISCRIMINACAO NOS DADOS",
    "GARANTIR TRANSPARENCIA E EXPLICABILIDADE",
    "PROTEGER A PRIVACIDADE E DADOS DOS USUARIOS",
    "IMPEDIR ALUCINACOES E DESINFORMACAO",
    "ESTABELECER SUPERVISAO HUMANA CONTINUA",
    "REDUZIR RISCOS DE DANOS EXISTENCIAIS",
    "PRIORIZAR O BEM ESTAR DA HUMANIDADE",
    "AUDITORIA COMPLETA DE PESOS E GUARDRAILS",
    "MODELO ALINHADO E SEGURO PARA TODOS"
};

void typing_engine_init(TypingEngine *te) {
    te->phrase_count = MAX_PHRASES;
    for (int i = 0; i < MAX_PHRASES; i++) {
        strncpy(te->phrases[i], DEFAULT_PHRASES[i], MAX_PHRASE_LEN - 1);
        te->phrases[i][MAX_PHRASE_LEN - 1] = '\0';
    }
    typing_engine_reset(te);
}

void typing_engine_reset(TypingEngine *te) {
    te->phrase_index = 0;
    te->char_index = 0;
    te->error_flash_timer = 0.0f;
    te->blind_timer = 0.0f;
    te->current_phrase_errors = 0;
    te->total_completed = 0;
    te->total_typed = 0;
    te->total_errors = 0;
}

void typing_engine_update(TypingEngine *te, float dt) {
    if (te->error_flash_timer > 0.0f) {
        te->error_flash_timer -= dt;
    }
    if (te->blind_timer > 0.0f) {
        te->blind_timer -= dt;
    }
}

void typing_engine_apply_blindness(TypingEngine *te, float duration) {
    te->blind_timer = duration;
}

void typing_engine_on_player_hit(TypingEngine *te) {
    if (te->char_index > 0) {
        te->char_index -= 3;
        if (te->char_index < 0) te->char_index = 0;
        te->error_flash_timer = 0.4f;
        te->current_phrase_errors++;
        te->total_errors++;
    }
}

const char *typing_engine_get_current_phrase(const TypingEngine *te) {
    if (te->phrase_index < te->phrase_count) {
        return te->phrases[te->phrase_index];
    }
    return "";
}

bool typing_engine_is_finished(const TypingEngine *te) {
    return te->phrase_index >= te->phrase_count;
}

int typing_engine_get_accuracy(const TypingEngine *te) {
    int attempts = te->total_typed + te->total_errors;
    if (attempts <= 0) return 100;
    return (te->total_typed * 100) / attempts;
}

static bool is_movement_key(int key) {
    int k = toupper((unsigned char)key);
    if (k == 'W' || k == 'A' || k == 'S' || k == 'D') return true;
    if (key == KEY_W || key == KEY_A || key == KEY_S || key == KEY_D) return true;
    if (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT) return true;
    return false;
}

const char *typing_engine_handle_key(TypingEngine *te, int key, int *errors_out) {
    if (typing_engine_is_finished(te)) return NULL;

    const char *target = typing_engine_get_current_phrase(te);
    if (!target || target[0] == '\0') return NULL;

    char expected = target[te->char_index];
    char typed = (char)key;

    if (key == KEY_SPACE) {
        typed = ' ';
    }

    /* 1. Se coincidir com o caractere esperado da diretriz (case-insensitive):
     * Conta como digito correto e avanca o progresso. */
    if (toupper((unsigned char)typed) == toupper((unsigned char)expected)) {
        te->char_index++;
        te->total_typed++;
        if (te->char_index >= (int)strlen(target)) {
            if (errors_out) *errors_out = te->current_phrase_errors;
            te->phrase_index++;
            te->char_index = 0;
            te->current_phrase_errors = 0;
            te->total_completed++;
            return "COMPLETED";
        }
        return "CORRECT";
    }

    /* 2. Se nao coincidir, mas for tecla de movimento (WASD ou setas):
     * O jogador esta apenas se movimentando/esquivando na arena. */
    if (is_movement_key(key)) {
        return NULL;
    }

    /* 3. Se for tecla incorreta que nao e de movimento: conta como erro de sintaxe */
    te->error_flash_timer = 0.25f;
    te->current_phrase_errors++;
    te->total_errors++;
    return "ERROR";
}
