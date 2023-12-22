#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Arv{
    char Info;
    struct Arv*Esq;
    struct Arv*Dir;
}TArv;

typedef TArv * PArv;

typedef struct Pilha{
    PArv Info;
    struct Pilha*Prox;
}TPilha;

typedef TPilha * PPilha;

PPilha Push(PPilha P, PArv Val){
    PPilha Novo = (PPilha)malloc(sizeof(TPilha));
    Novo->Info = Val;
    Novo->Prox = P;
    return(Novo);
}

PArv Pop (PPilha *P){
    PPilha Q = *P;
    PArv Val;

    if(*P == NULL){
        return *P;
    }
    Val = Q->Info;
    *P = Q->Prox;
    free(Q);
    return Val;
}

int BuscaNaoRecursiva(PArv A, char C){
    PPilha Pilha = NULL;
    PArv Aux;
    if(A == NULL){
        return C;
    }
    Pilha = Push(Pilha, A);
    while(Pilha != NULL){
        
    }
}

int main(){

}