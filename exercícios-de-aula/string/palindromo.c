#include "palindromo.h"
#include <stdbool.h>
#include <string.h>

#define SIZE 100

void le_caracteres (struct fila_t *frase) {

    struct nodo_t *aux = frase -> primeiro;

    while (aux -> letra != '\0') {

        scanf("%s", aux -> letra);

    }

}

void imprime_fila (struct fila_t *fila) {

    struct nodo_t *aux = fila -> primeiro;
    
    for (int i = 0; i < fila -> num; i++) {

        printf("%s\n", aux -> letra);
    }

}

int main () {

    struct fila_t *frase1;
/*     struct fila_t *frase2;
    bool eh_palindromo = true; */

    le_caracteres(frase1);
    imprime_fila(frase1);
/*     le_caracteres(frase2);

    eh_palindromo = compara_caracteres(frase1, frase2);

    if (eh_palindromo == true) {
        printf("é palíndromo\n");
    }
    else {
        printf("não é palíndromo\n");
    } */

    return 0;
    
}