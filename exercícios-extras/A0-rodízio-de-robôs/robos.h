#include "lista.h"

struct robo_t {

    int id;
    int ciclos;

};

/* Funções */

int aleat(int min, int max);
void cadastra_robo (struct fila_t *robos_lista, int robos_num);
void executa_ciclo (struct fila_t *robos_lista, int ciclos_num);
