#ifndef UTIL_H
#define UTIL_H

#include <time.h>


// Converte time_t para string formatada
void format_date(time_t t, char *buffer, int max);

// Calcula o tamanho do arquivo
long arq_tam (FILE* arq);

#endif

