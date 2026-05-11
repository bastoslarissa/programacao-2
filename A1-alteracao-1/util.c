#include "util.h"
#include <stdio.h>
#include <time.h>

void format_date(time_t t, char *buffer, int max) {
    struct tm *info = localtime(&t);
    strftime(buffer, max, "%d/%m/%Y %H:%M:%S", info);
}

long arq_tam (FILE* arq) {

    fseek(arq, 0, SEEK_END);
    long tamanho = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    return tamanho;
}
