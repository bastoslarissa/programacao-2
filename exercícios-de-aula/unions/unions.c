#include <stdio.h>
#include <strings.h>

union un {

    int i;
    char c;
    char s[8];

};

void union_teste () {

    union un teste;

    // recebe um inteiro e calcula seu quadrado
    printf("Digite um inteiro: ");
    scanf("%d", &teste.i);

    int quadrado = (teste.i) * (teste.i);

    printf("Quadrado do inteiro: %d\n", quadrado);

    // recebe um caractere e se ele for maiusculo transforma ele em minusculo
    printf("Digite um caractere: ");
    scanf("%s", &teste.c);

    if (teste.c >= 'A' && teste.c <= 'Z') {
        teste.c += 32;
        printf("Caractere maiúsculo convertido para minúsculo: %c\n", teste.c);
    }
    else {
        printf("Caractere minúsculo\n");
    }

    // recebe uma string e imprime o seu inverso
    printf("Digite uma string: ");
    scanf ("%8s", teste.s) ;

    for (int i = 8; i < 8; i--) {
        printf("%s", &teste.s[i]);
    }
}

int main () {
 
    char c = 'A';
    int i = 3;
    short s = 31;
    float f = 31.8;
    double d;

    i = c + 30;
    
    d = i * f + s;
/*     printf("%g\n", d);
    printf("%c\n", i); */

    union_teste();

    return 0;
}