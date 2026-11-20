/* =========================================================================
 * Testes de validacao logica (LMC - Unidade 2) - PI2-31
 * Responsavel: Theo Monteiro Pinho
 *
 * Verifica, contra o codigo real em C99, as propriedades descritas em
 * docs/relatorio_lmc_unidade2.md:
 *   T1. Tabela-verdade da classificacao de teclas (typing_engine_handle_key)
 *   T2. Particao da avaliacao de precisao (0 / 1-2 / 3+ erros)
 *   T3. Fases da AURA-67 em funcao das frases concluidas (boss_get_phase)
 *   T4. Invariantes de vida e alinhamento (hp + 100k = 1000, alinhamento = 10k)
 *   T5. Limites da formula de precisao (0 <= P <= 100)
 *
 * Compilar e rodar:  make test-lmc
 * ========================================================================= */
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "typing_engine.h"
#include "boss.h"

static int falhas = 0;
static int total = 0;

#define CHECK(cond, msg) do { total++; if (!(cond)) { falhas++; printf("  [FALHOU] %s\n", msg); } } while (0)

/* Classificacao das frases de rating usada em main.c (combat_process_round) */
static int pontos_por_erros(int e) {
    if (e == 0) return SCORE_PERFECT;
    else if (e <= 2) return SCORE_STABLE;
    return SCORE_PATCHED;
}

static void t1_tabela_verdade_teclas(void) {
    printf("T1. Tabela-verdade: C (tecla certa) x M (tecla de movimento)\n");
    TypingEngine te;

    /* Frase 0 = "CONSTITUICAO DE SEGURANCA ATIVADA": primeiro caractere 'C' */
    /* C=V, M=F  -> CORRECT */
    typing_engine_init(&te);
    const char *r = typing_engine_handle_key(&te, 'c', NULL);
    CHECK(r && strcmp(r, "CORRECT") == 0, "C=V,M=F deveria ser CORRECT (aceita minuscula)");
    CHECK(te.char_index == 1 && te.total_errors == 0, "C=V avanca 1 posicao sem erro");

    /* C=F, M=F  -> ERROR  (esperado 'O', digitado 'X') */
    r = typing_engine_handle_key(&te, 'X', NULL);
    CHECK(r && strcmp(r, "ERROR") == 0, "C=F,M=F deveria ser ERROR");
    CHECK(te.char_index == 1 && te.total_errors == 1, "ERROR nao avanca e conta 1 erro");

    /* C=F, M=V  -> ignorado (NULL)  (esperado 'O', digitado 'W') */
    r = typing_engine_handle_key(&te, 'W', NULL);
    CHECK(r == NULL, "C=F,M=V deveria ser ignorado (NULL)");
    CHECK(te.total_errors == 1, "tecla de movimento nao conta erro");

    /* C=V, M=V  -> CORRECT  (o caractere esperado e uma letra de movimento: 'A')
       Em "CONSTITUICAO DE SEGURANCA ATIVADA" o indice 10 e 'A'. */
    typing_engine_init(&te);
    te.char_index = 10;
    CHECK(typing_engine_get_current_phrase(&te)[10] == 'A', "pre-condicao: caractere esperado e 'A'");
    r = typing_engine_handle_key(&te, 'a', NULL);
    CHECK(r && strcmp(r, "CORRECT") == 0, "C=V,M=V deveria ser CORRECT (acerto tem prioridade)");
}

static void t2_particao_rating(void) {
    printf("T2. Particao da avaliacao de precisao por numero de erros\n");
    for (int e = 0; e <= 50; e++) {
        int p0 = (e == 0), p12 = (e >= 1 && e <= 2), p3 = (e >= 3);
        CHECK(p0 + p12 + p3 == 1, "cada valor de erros cai em exatamente 1 faixa");
        int esperado = p0 ? 150 : (p12 ? 100 : 50);
        CHECK(pontos_por_erros(e) == esperado, "pontuacao bate com a faixa");
    }
}

static void t3_t4_fases_e_invariantes(void) {
    printf("T3/T4. Fases da AURA-67 e invariantes por frase concluida\n");
    Boss b;
    boss_init(&b, 0, 0, DIFFICULTY_NORMAL);
    int fase_anterior = boss_get_phase(&b);
    CHECK(fase_anterior == 1, "partida comeca na fase 1");
    CHECK(BOSS_DAMAGE_PER_PHRASE * TOTAL_DIRECTIVES == BOSS_MAX_HP, "10 frases x 100 = 1000 de vida");
    CHECK(BOSS_ALIGNMENT_STEP * TOTAL_DIRECTIVES == 100, "10 frases x 10% = 100% de alinhamento");
    CHECK(MAX_PHRASES == TOTAL_DIRECTIVES, "numero de frases = numero de diretrizes");

    int esperado[11] = {1,1,1,1,2,2,2,3,3,3,3};
    for (int k = 0; k <= TOTAL_DIRECTIVES; k++) {
        CHECK(b.hp + BOSS_DAMAGE_PER_PHRASE * k == BOSS_MAX_HP, "invariante hp = 1000 - 100k");
        CHECK(b.alignment_pct == BOSS_ALIGNMENT_STEP * k, "invariante alinhamento = 10k");
        int f = boss_get_phase(&b);
        printf("    k=%2d  hp=%4d  alinhamento=%3d%%  fase=%d\n", k, b.hp, b.alignment_pct, f);
        CHECK(f == esperado[k], "fase esperada para k frases");
        CHECK(f >= fase_anterior, "fase nunca volta (monotonica)");
        fase_anterior = f;
        if (k < TOTAL_DIRECTIVES) {
            boss_take_damage(&b, BOSS_DAMAGE_PER_PHRASE);
            b.alignment_pct += BOSS_ALIGNMENT_STEP;
        }
    }
    CHECK(b.hp == 0, "apos 10 frases a vida chega exatamente a 0");
}

static void t3b_partida_completa(void) {
    printf("T3b. Digitar todas as frases sem erro termina o motor\n");
    TypingEngine te;
    typing_engine_init(&te);
    int concluidas = 0;
    while (!typing_engine_is_finished(&te)) {
        const char *frase = typing_engine_get_current_phrase(&te);
        int erros = -1;
        const char *r = typing_engine_handle_key(&te, frase[te.char_index], &erros);
        if (r && strcmp(r, "COMPLETED") == 0) { concluidas++; CHECK(erros == 0, "frase perfeita tem 0 erros"); }
    }
    CHECK(concluidas == TOTAL_DIRECTIVES, "10 frases concluidas");
    CHECK(typing_engine_get_accuracy(&te) == 100, "precisao 100% sem erros");
    CHECK(typing_engine_handle_key(&te, 'A', NULL) == NULL, "apos terminar, novas teclas sao ignoradas");
}

static void t5_limites_precisao(void) {
    printf("T5. Limites da formula de precisao P = acertos*100/(acertos+erros)\n");
    TypingEngine te;
    typing_engine_init(&te);
    CHECK(typing_engine_get_accuracy(&te) == 100, "sem tentativas, P = 100 (evita divisao por zero)");
    int casos[][2] = {{0,1},{1,1},{4,1},{8,2},{0,500},{500,0},{123,77}};
    for (size_t i = 0; i < sizeof(casos)/sizeof(casos[0]); i++) {
        te.total_typed = casos[i][0];
        te.total_errors = casos[i][1];
        int p = typing_engine_get_accuracy(&te);
        CHECK(p >= 0 && p <= 100, "0 <= P <= 100");
    }
    te.total_typed = 4; te.total_errors = 1;
    CHECK(typing_engine_get_accuracy(&te) == 80, "4 acertos e 1 erro = 80%");
}

int main(void) {
    printf("=== Validacao Logica LMC - Unidade 2 (PI2-31) ===\n");
    t1_tabela_verdade_teclas();
    t2_particao_rating();
    t3_t4_fases_e_invariantes();
    t3b_partida_completa();
    t5_limites_precisao();
    printf("\nResultado: %d/%d verificacoes passaram.\n", total - falhas, total);
    return falhas == 0 ? 0 : 1;
}
