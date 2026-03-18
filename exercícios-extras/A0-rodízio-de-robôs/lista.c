#include "lista.h"

struct fila_t *lista_cria () {

    struct fila_t *lista = malloc(sizeof(struct fila_t));

    // verifica se a lista é válida
    if (!lista) {
        return NULL;
    }
    
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

int lista_insere (struct fila_t *lista, void *item) {

    // cria um novo nodo
    struct nodo_t *novo_nodo = malloc(sizeof(struct nodo_t));

    // verificação
    if (!lista || !item || !novo_nodo) 
        return -1;

    // inicialização
    novo_nodo -> item = item;

    // caso: primeiro elemento a ser inserido
    if (lista -> num == 0) {

        lista -> primeiro = novo_nodo;
        lista -> ultimo = novo_nodo;
        novo_nodo -> prox = NULL;
    }

    // caso: elemento a ser inserido no final
    else {

        novo_nodo -> prox = lista -> primeiro;
        lista -> ultimo -> prox = novo_nodo;
        lista -> ultimo = novo_nodo;
    }
    
    // incrementa a quantidade de elementos na lista
    lista -> num++;

    return 1;

}

struct nodo_t *lista_retira (struct fila_t *lista, void *item) {

    // verificação
    if (!lista || !item)
        return NULL;
    
    struct nodo_t *aux = lista -> primeiro;
    struct nodo_t *aux_anterior = lista -> ultimo;
    struct nodo_t *item_retirado;

    // retira o item
    for (int i = 0; i < lista -> num; i++) {

        if (aux -> item == item) {

            item_retirado = aux;
            aux_anterior -> prox = aux -> prox;
        }
    }

    // decrementa a quantidade de elementos da lista
    lista -> num--;

    return item_retirado;
}

/* void lista_imprime (struct fila_t *lista) {

    struct nodo_t *aux = lista -> primeiro;

    for (int i = 0; i < lista -> num; i++) {

        printf("%d ", aux -> item);
        aux = aux -> prox;
    }

    printf("\n");
} */