#include "lista.h"

int main () {

    struct fila_t *lista = lista_cria ();

    int a = 2;
    int b = 4;
    int *pa = &a;
    int *pb = &b;

    lista_insere(lista, pa);
    lista_insere(lista, pb);

    lista_destroi(lista);
}