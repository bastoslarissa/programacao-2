#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Exercício 1: Ler uma string da entrada padrão e escrevê-la na saída padrão ao contrário 
  (do final para o início), de forma similar ao comando rev do shell UNIX.*/

void le_string (char *string) {

    printf("Digite uma string: ");
    scanf("%[^\n]", string);

}

void imprime_string_reversa (char *string) {

    int i = 0 ;
    int string_tam = strlen(string);

    char *string_reversa = malloc(sizeof(char) * string_tam);

    while (string[i] != '\0') {

        string_reversa[string_tam - 1] = string[i];

        i++;
        string_tam--;
    }

    printf("string ao contrário: %s\n", string_reversa);

    free(string_reversa);
}

/* Exercício 2: Calcular o tamanho de uma string sem usar strlen */

int tamanho (char *string) {

    int i = 0;
    int contador = 0;

    while (string[i] != 0) {

        contador++;
        i++;
    }

    return contador;
}

/* Exercício 3: Converter as letras de uma string em minúsculas 
  (dica: estude a estrutura da tabela ASCII antes de implementar)*/

/* void converte_em_minusculo (char *string) {

    int string_tam = strlen(string);

    char *string_aux = malloc(sizeof(char) * string_tam);
    strcpy(string_aux, string);

    for (int i = 0; i < string_tam; i++) {

        if (string[i] >= 'A' && string[i] <= 'Z') {

            string_aux[i] -= 32;
        }
    }

    printf("String convertida em letras minúsculas: %s\n", string_aux);
} */

/* Exercício 4: Ler linhas da entrada padrão e escrevê-las na saída padrão em ordem alfabética 
   crescente, de forma similar ao comando sort do shell UNIX.*/

// Ordena a string usando o algoritmo Selection Sort (talvez mudar p\ quick sort(?))
void ordena (char *string) {
    
    int i = 0;
    char *menor = '\0';

    while(string[i] != '/0') {

        for (int i = 0; i < (tamanho(string) - 1); i++) {

            menor = string[i];
            int j = i - 1;

            while (j >= 0 && string[j] > menor) {

                string[j + 1] = string[j];
                j = j - 1;
            }
        string[j + 1] = menor;
        }
    }
}

void imprime_ordenado (char *string) {

    ordena(string);

    for (int i = 0; i < tamanho(string); i++) {

        printf("%s ", string[i]);
    }

    printf("\n");

}