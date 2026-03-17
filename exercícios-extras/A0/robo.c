#include <stdio.h>
#include "lista.h"

int main () {

    struct fila_t *lista = lista_cria ();

    lista_insere(lista, 4);
    lista_insere(lista, 2);

    lista_retira(lista, 4);

    lista_insere(lista, 3);

    lista_imprime(lista);

    lista_destroi(lista);
}