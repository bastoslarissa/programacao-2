#include "lista.h"
#include "robos.h"

int main () {

    int robos_num;

    printf("Quantos robôs você deseja cadastrar?\n");
    scanf("%d", &robos_num);

    struct fila_t *robos_lista = lista_cria();

    cadastra_robo(robos_lista, robos_num);

    int resposta;
    printf("Deseja executar um ciclo de carregamento? (1 - SIM 2- NAO)\n");
    scanf("%d", &resposta);

    if (resposta == 1) {

        executa_ciclo(robos_lista, aleat(1, 2));

    }

}