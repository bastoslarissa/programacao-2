#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "gbv.h"

int main(int argc, char *argv[]) {

Library lib;

gbv_create("biblioteca.gbv");
gbv_open(&lib, "biblioteca.gbv");

gbv_add(&lib, "biblioteca.gbv", "doc1.txt");
gbv_list(&lib);

free(lib.docs);

    return 0;
}

