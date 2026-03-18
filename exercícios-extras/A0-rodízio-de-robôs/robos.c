#include "robos.h"

int aleat (int min, int max) {

    int aleat = (rand()%(max - min + 1)) + min;

    return aleat;

}

void cadastra_robo (struct fila_t *robos_lista, int robos_num) {

    if (!robos_lista || !robos_num)
        printf("Fila inválida\n");
    
    int ciclos = 0;

    // inicializa robôs
    for (int i = 0; i < robos_num; i++) {

        // recebe do usuário a quantidade de ciclos de carregamento que o robô precisa
        printf("Quantos ciclos o robô %d precisa?\n", i);
        scanf("%d", &ciclos);

        struct robo_t *robo = malloc(sizeof(struct robo_t));
        robo -> id = i;
        robo -> ciclos = ciclos;
        lista_insere(robos_lista, robo);
    }

}

void executa_ciclo (struct fila_t *robos_lista, int ciclos_num) {

    struct nodo_t *aux = robos_lista -> primeiro;

    if (ciclos_num == 1) {
    }
}