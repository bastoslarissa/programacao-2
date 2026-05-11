#include <stdio.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printf("Uso: %s <chave> <opção> <biblioteca> [documentos...]\n", argv[0]);
        return 1;
    }

    const char *chave = argv[1];
    const char *opcao = argv[2];
    const char *biblioteca = argv[3];

    Library lib;
    if (gbv_open(&lib, biblioteca) != 0) {
        printf("Erro ao abrir biblioteca %s\n", biblioteca);
        return 1;
    }

     if (strcmp(opcao, "-a") == 0) {
        for (int i = 4; i < argc; i++) {
            gbv_add(&lib, biblioteca, argv[i], chave);
        }
     } else if (strcmp(opcao, "-r") == 0) {
        for (int i = 4; i < argc; i++) {
            gbv_remove(&lib, argv[i], biblioteca, chave);
        }
    } else if (strcmp(opcao, "-l") == 0) {
        gbv_list(&lib, biblioteca, chave);
    } else if (strcmp(opcao, "-v") == 0 && argc >= 5) {
        gbv_view(&lib, argv[4], biblioteca, chave);
    } else {
        printf("Opção inválida.\n"); 
    }  

    return 0;
}

