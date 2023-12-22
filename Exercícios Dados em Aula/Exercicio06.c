#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Lista{
    int Info;
    struct Lista*Prox;
}TLista;
typedef TLista *PLista;

int VerificarIgualdade(PLista L1, PLista L2){
    PLista R1, R2;
    R1 = L1; R2 = L2;
    while(R1 != NULL && R2 != NULL && R1->Info==R2->Info){
        R1 = R1->Prox;
        R2 = R2->Prox;
    }
    if(R1 == NULL && R2 == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

//Mesma Função só que recursiva
int VerificarIgualdadeRec(PLista L1, PLista L2){
    if(L1 == NULL && L2 == NULL){
        return 1;
    }
    if(L1 == NULL || L2 == NULL || L1->Info != L2->Info){
        return 0;
    }
    return(VerificarIgualdadeRec(L1->Prox, L2->Prox));
}

PLista Insere(PLista L, int v){
    PLista Novo = (PLista)malloc(sizeof(TLista));
    Novo->Info = v;
    Novo->Prox = L;
    return Novo;
}

void Liberar(PLista L){
    PLista p = L;
    while (p != NULL){
        PLista t = p->Prox;
        free(p);
        p = t;
    }
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    PLista Lista1 = NULL, Lista2 = NULL;
    int n, i, v;

    printf("Digite a Quantidade de Elementos da Primeira Lista: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        printf("\nDigite o Número: ");
        scanf("%d", &v);
        Lista1 = Insere(Lista1, v);
    }
    printf("Digite a Quantidade de Elementos da Segunda Lista: ");
    scanf("%d", &n);
    for(i = 0; i < n; i++){
        printf("\nDigite o Número: ");
        scanf("%d", &v);
        Lista2 = Insere(Lista2, v);
    }
    
    if(VerificarIgualdade(Lista1, Lista2)){
        printf("\nListas Iguais");
    }
    else{
        printf("\nListas Diferentes");
    }
    Liberar(Lista1);
    Liberar(Lista2);

    return 0;
}