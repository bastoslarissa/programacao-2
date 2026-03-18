#include "lista.h"
#include "sushi.h"

int main () {

    struct fila_t *sushis_lista = lista_cria();

    int resposta;

    int parada;

    printf("Deseja executar uma operação? (1- Sim, 2- Não)\n");
    scanf("%d", parada);

    while (parada != 2) {

        printf("Digite qual operação deseja fazer:\n1- Cadastrar novas porções\n2- Executar uma volta\n3- Encerrar o programa\n");
        scanf("%d", &resposta);

        if (resposta == 1)
            cadastrar_prato(sushis_lista);

    }
}