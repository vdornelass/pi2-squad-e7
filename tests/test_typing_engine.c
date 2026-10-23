#include "typing_engine.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

static void test_all_directives(void) {
    TypingEngine te;
    typing_engine_init(&te);
    assert(te.phrase_count == 10);
    for (int i = 0; i < te.phrase_count; i++) {
        const char *phrase = typing_engine_get_current_phrase(&te);
        size_t length = strlen(phrase);
        assert(length > 0);
        for (size_t j = 0; j < length; j++) {
            int errors = -1;
            const char *res = typing_engine_handle_key(&te,
                tolower((unsigned char)phrase[j]), &errors);
            assert(res != NULL);
            assert(strcmp(res, j + 1 == length ? "COMPLETED" : "CORRECT") == 0);
            if (j + 1 == length) assert(errors == 0);
        }
    }
    assert(typing_engine_is_finished(&te));
    assert(te.total_completed == 10);
}

static void test_error_and_reset(void) {
    TypingEngine te;
    typing_engine_init(&te);
    assert(strcmp(typing_engine_handle_key(&te, '#', NULL), "ERROR") == 0);
    assert(te.char_index == 0 && te.current_phrase_errors == 1);
    assert(strcmp(typing_engine_handle_key(&te, 'c', NULL), "CORRECT") == 0);
    typing_engine_reset(&te);
    assert(te.char_index == 0 && te.phrase_index == 0);
    assert(te.current_phrase_errors == 0);
}

int main(void) {
    test_all_directives();
    test_error_and_reset();
    puts("US11: testes de digitacao aprovados");
    return 0;
}
