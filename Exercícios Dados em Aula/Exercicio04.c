#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Lista{
    int info;
    struct Lista* Proximo;
} TLista;
typedef TLista *Plista;

Plista inicializa_lista(){
    return NULL;
}

Plista insere(Plista L, int i){
    Plista Novo = (Plista)malloc(sizeof(TLista));
    Novo->info = i;
    Novo->Proximo = L;
    return Novo;
}

Plista Pop(Plista L, int *V){
    Plista P=1; //Ponteiro para guardar o endereço do elemento a ser retirado
    if(L==NULL){
        return (L);
    }
    *V = L->info;
    L = P->Proximo;
    free(P);
    return L;
}

void Imprimir(Plista L){
    Plista P;
    if(L == NULL){
        return;
    }
    for(P = L; P->Proximo!=NULL; P = P->Proximo){
        printf("%d", P->info);
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    printf("Aula 14/09 - Pilha Encadeada");
}