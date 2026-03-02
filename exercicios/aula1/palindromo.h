#include <stdio.h>

/* Lista Dupla */

struct nodo_t {

    char letra;
    struct nodo_t *ant;
    struct nodo_t *prox;
};

struct fila_t {

    struct nodo_t *primeiro;
    struct nodo_t *ultimo;
    int num;
};

