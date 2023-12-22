//Lista Encadeada Circular - AED 1 - 26/09
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Lista{
    int Info;
    struct Lista*Prox;
}TLista;
typedef TLista *PLista;

void Imprime_Circular(PLista Ultimo){
    PLista P;
    if(Ultimo != NULL){
        P = Ultimo->Prox;
    }
    do{
        printf("\n%d", P->Info);
        P = P->Prox;
    }while(P != Ultimo->Prox);
}

PLista Insere_Circ(PLista Ultimo, int V){
    PLista Novo;
    Novo = (PLista)malloc(sizeof(TLista));
    Novo->Info = V;
    if(Ultimo == NULL){
        Novo->Prox = Novo;
        return(Novo);
    }
    Novo->Prox = Ultimo->Prox;
    Ultimo->Prox = Novo;
    return(Ultimo);
}

void Libera_Circ(PLista Ultimo){
    PLista P;
    if(Ultimo == NULL){
        return;
    }
    P = Ultimo->Prox;
    while(P != Ultimo){
        Ultimo->Prox = P->Prox;
        free(P);
        P = Ultimo->Prox;
    }
}

PLista Push(PLista Ultimo, int V){
    //Insere no Início da Lista Circular
    PLista Novo;
    Novo = (PLista)malloc(sizeof(TLista));
    Novo->Info = V;
    if(Ultimo == NULL){
        Novo->Prox = Novo;
        return(Novo);
    }
    else{
        Novo->Prox = Ultimo->Prox;
        Ultimo->Prox = Novo;
        return (Ultimo);
    }
}

/*PLista Push(PLista Ultimo, int V){
    //Insere no Final da Lista Circular
    PLista Novo;
    Novo = (PLista)malloc(sizeof(TLista));
    Novo->Info = V;
    if(Ultimo == NULL){
        Novo->Prox = Novo;
    }
    else{
        Novo->Prox = Ultimo->Prox;
        Ultimo->Prox = Novo;
    }
    return(Novo);
}*/

PLista Pop(PLista Ultimo, int *V){
    PLista P;
    if(Ultimo == NULL){
        return(Ultimo);
    }
    P = Ultimo->Prox;
    if(P == Ultimo){
        Ultimo = NULL;
    }
    else{
        Ultimo->Prox = P->Prox;
        *V = P->Info;
        free(P);
        return(Ultimo);
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");

}