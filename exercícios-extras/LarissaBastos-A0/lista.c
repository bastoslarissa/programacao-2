#include "lista.h"
#include "sushi.h"

struct fila_t *lista_cria () {

    struct fila_t *lista = malloc(sizeof(struct fila_t));

    if (!lista) {
        return NULL;
    }

    // atribuições
    lista -> primeiro = NULL;
    lista -> ultimo = NULL;
    lista -> num = 0;
         printf("lista criada\n");

    return lista;
}

void *lista_destroi (struct fila_t *lista) {

    if (!lista) {
        printf("Lista inválida\n");
    }

    else {
        for (int i = 0; i < lista -> num; i++) {

            struct nodo_t *aux = lista -> primeiro;
            lista -> primeiro = lista -> primeiro -> prox;
            free(aux);
        }
    }

    printf("lista destruída\n");

    free(lista);

    return NULL;
}

int lista_insere (struct fila_t *lista, struct prato *item) {

    if (!lista || !item)
        return -1;

    // cria um nodo 
    struct nodo_t *novo_nodo = malloc(sizeof(struct nodo_t));

    if (novo_nodo) {

        // insere no início
        if (lista -> num == 0) {

            lista -> primeiro = novo_nodo;
            novo_nodo -> item = item;
            novo_nodo -> prox = NULL;
            printf("inseriu no inicio\n");
        }

        // insere no final
        else {

            lista -> ultimo -> prox = novo_nodo;
            lista -> ultimo = novo_nodo;
            novo_nodo -> prox = lista -> primeiro;
            novo_nodo -> item = item;
            printf("inseriu no final\n");
        }
    }

    lista -> num++;
    return 1;

}

struct nodo_t *lista_retira (struct fila_t *lista, struct prato *item) {

    if (!lista || !item) 
        return NULL;

    struct nodo_t *aux = lista -> primeiro;
    struct nodo_t *aux_anterior = lista -> ultimo;
    struct nodo_t *item_retirado;

    if (lista -> num > 0) {

        for (int i = 0; i < lista -> num; i++) {

            if (aux -> item == item) {

                aux_anterior -> prox = aux -> prox;
                item_retirado = aux;
            }
        
            aux = aux -> prox;
            aux_anterior = aux_anterior -> prox;
        }
        
        lista -> num--;
        printf("item retirado\n");

        return item_retirado;
    }

}