#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ponto{
    double x;
    double y;
};

int main(){
    struct ponto *P;
    P = (struct Ponto*)malloc(sizeof(struct ponto));
    P->x = 12.0;
}