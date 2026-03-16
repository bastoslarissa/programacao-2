#include "lista.h"

struct fila_t *lista_cria () {

    struct fila_t *lista = malloc(sizeof(struct fila_t));

    // verifica se a lista é válida
    if (!lista)
        return NULL;
    
    // inicializa a lista
    lista -> primeiro = NULL;
    lista -> ultimo = NULL;
    lista -> num = 0;

    return lista;

}

struct fila_t *lista_destroi (struct fila_t *lista) {

    for (int i = 0; i < (lista -> num); i++) {

        struct nodo_t *aux = lista -> primeiro;
        lista -> primeiro = lista -> primeiro -> prox;
        free(aux);
    }

    free(lista);

    return NULL;
}

int *lista_insere (struct fila_t *lista, void *item) {

    // cria um novo nodo
    struct nodo_t *novo_nodo = malloc(sizeof(struct nodo_t));

    // verificação
    if (!lista || !item || !novo_nodo) 
        return -1;

    // inicialização
    novo_nodo -> item = item;
    novo_nodo -> prox = lista -> primeiro;

    // muda o ultimo nodo
    lista -> ultimo -> prox = novo_nodo;
    lista -> ultimo = novo_nodo;

    return 1;

}

struct fila_t *fila_retira (struct fila_t *lista, void *item) {

    if (!lista || !item)
        return NULL;
    
    struct nodo_t *aux = lista -> primeiro;
    struct nodo_t *aux_anterior = lista -> ultimo;
    void *item_retirado;

    for (int i = 0; i < lista -> num; i++) {

        if (aux -> item == item) {

            item_retirado = aux -> item;
            aux_anterior -> prox = aux -> prox;
        }
    }
}