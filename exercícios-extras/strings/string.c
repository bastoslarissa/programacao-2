#include "string.h"

int main () {

    char string[100];
    int string_tamanho;

    le_string(string);

    string_tamanho = calcula_tamanho(string);
    printf("Tamano da string: %d\n", string_tamanho);

    imprime_string_reversa(string);

/*     converte_em_minusculo(string); */

}


