/*
          Aula 184: O que é e como criar um ponteiro?
*/
#include <stdio.h>
#include <locale.h>

int main(){
    char letra = 'f';
    char *p;

    p = &letra;

    printf("Variavel Letra:\n");
    printf("Valor de letra: %c\n", letra);
    printf("Endereco de letra: %p\n", &letra);
    
    printf("\n\nVariavel *P:\n");
    printf("Valor de p: %p\n", p);
    printf("Endereco de p: %p\n", &p);
    printf("Valor apontado por p: %c\n", *p);

    return 0;
}