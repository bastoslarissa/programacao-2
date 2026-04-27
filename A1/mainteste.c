#include <stdio.h>
#include <string.h>
#include "gbv.h"

int main(int argc, char *argv[]) {

    int resultado_funcao;
    int resultado_gbvopen;
    int resultado_remove;

    Library *lib;

    resultado_funcao = gbv_create("biblioteca");
    resultado_gbvopen = gbv_open(lib, "biblioteca");
    resultado_remove = gbv_remove(lib, "x");

    return 0;
}

