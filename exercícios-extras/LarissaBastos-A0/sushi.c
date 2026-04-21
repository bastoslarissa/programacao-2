#include "sushi.h"

int aleat (int min, int max) {

    int aleat = (rand()%(max - min + 1)) + min;

    return aleat;

}

void cadastrar_prato (struct fila_t *sushis_lista) {

    if (!sushis_lista)
        printf("Lista inválida!\n");

    printf("Quantos pratos deseja cadastrar?\n");

    int pratos_num;
    scanf("%d", &pratos_num);

    for (int i = 0; i < pratos_num; i++) {

        int unidades;
        
        struct prato *sushi = malloc(sizeof(struct prato));

        printf("Quantas unidades do prato %d tem?\n", i);
        scanf("%d", &unidades);

        sushi -> id = i;
        sushi -> unidades = unidades;

        lista_insere(sushis_lista, sushi);
    }

}

void executa_volta (struct fila_t *sushis_lista) {

    if (!sushis_lista)
        printf("Lista inválida\n");

    int unidades_num = aleat(0, 2);
    struct nodo_t *aux = sushis_lista -> primeiro;

    // percorre a lista
    for (int i = 0; i < sushis_lista -> num; i++) {

        for (int j = 0; j < unidades_num; j++) {

            int id_aleat = aleat(0, sushis_lista -> num);
        
            if (aux -> item -> id == id_aleat ) {
            aux -> item -> unidades--;
            }

            aux = aux -> prox;
        }

        // verifica se há algum prato sem nenhuma unidade
        if (aux -> item[i].unidades == 0) 
            lista_retira(sushis_lista, aux);

    }
}