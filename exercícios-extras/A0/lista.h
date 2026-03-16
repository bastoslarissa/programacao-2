/* Implementação de uma Lista Encadeada Circular */

#include <stdio.h>

// Definição das estruturas
struct nodo_t {

    int item;
    struct nodo_t *prox;

};

struct fila_t {

    struct nodo_t *primeiro;
    struct nodo_t *ultimo;
    int num;

};

// Funções

// Cria uma lista vazia
// Retorna um ponteiro para a lista
struct fila_t *lista_cria ();

// Elimina todas as estruturas de dados
struct fila_t *lista_destroi (struct fila_t *lista);

// Insere um item no fim da lista
int *lista_insere (struct fila_t *lista, void *item);

// Retira um item da lista
struct fila_t *fila_retira (struct fila_t *lista, void *item);

// Imprime a lista
void lista_imprime (struct fila_t *lista);
