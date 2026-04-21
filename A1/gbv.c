#include <stdio.h>
#include "gbv.h"

int gbv_create(const char *filename) {

    FILE* arq;

    arq = fopen(filename, "w+");

    if (!arq) {

        perror ("Erro ao abrir arquivo");
        exit (1);
    }
}

