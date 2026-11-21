/* =========================================================================
 * Verificador do certificado de alinhamento etico (US20 / PI2-246, CA04)
 * Recalcula o hash de integridade de bin/certificado.txt e compara com o
 * hash gravado no arquivo. Uso: make verificar-certificado
 * ========================================================================= */
#include <stdio.h>
#include "report.h"

int main(int argc, char **argv) {
    const char *path = (argc > 1) ? argv[1] : REPORT_TXT_FILE;
    int r = report_verify_txt(path);

    if (r == 1) {
        printf("OK: certificado integro (%s)\n", path);
        return 0;
    }
    if (r == 0) {
        printf("ALTERADO: o hash de %s nao confere. O certificado foi modificado.\n", path);
        return 1;
    }
    printf("ERRO: nao foi possivel ler %s ou encontrar a linha do hash.\n", path);
    return 2;
}
