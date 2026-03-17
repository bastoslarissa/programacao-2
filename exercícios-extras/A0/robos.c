#include "robos.h"

void cadastra_robo (struct fila_t *robos_lista) {

    if (!robos_lista)
        printf("Fila inválida\n");
    
    int resposta;
    int id = 0;

    printf("Deseja cadastrar novo robô? (1- Sim | 2- Não)\n");
    scanf("%d", &resposta);

    while (resposta == 1) {

        struct robo_t *robo = malloc(sizeof(struct robo_t));
        robo -> id = id;

        int ciclos;
        printf("Quantos ciclos de carregamento o robô [%d] precisa?\n", id);
        scanf("%d", &ciclos);
        robo -> ciclos = ciclos;

        lista_insere(robos_lista, robo);

        id++;

        printf("Deseja cadastrar novo robô? (1- Sim | 2- Não)\n");
        scanf("%d", &resposta);

    }
    

}