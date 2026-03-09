#include <stdio.h>
#include <string.h>

void le_string (char *string) {

    scanf("%[^\n]", string);

}

void imprime_string (char *string) {

    int i = 0 ;
    int string_tam = strlen(string);

    char *string_reversa = NULL;

    while (string[i] != '\0') {

        string_reversa[string_tam] = string[i];

        i++;
        string_tam--;
    }
}

/* void imprime_ao_contrario (char *string) {

    int string_tam = strlen(string);

    char string_reversa[string_tam];

    for (int i =  string_tam; i > 0; i++) {

        for (int j = 0; j < string_tam; j++) {

            string_reversa[j] = string[i];
        }
    }

    printf("string ao contrário: %s", string_reversa);

} */