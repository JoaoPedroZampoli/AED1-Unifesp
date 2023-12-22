//João Pedro da Silva Zampoli - RA: 168.880 - Turma AED 1 I
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_LINHA 100

typedef struct No *PonteiroME;
struct No{
    int Coluna, Valor;
    PonteiroME Proximo;
};
typedef PonteiroME Matriz[MAX_LINHA];

void InicializarMatriz(Matriz ME, int Linhas){
    int i;
    for(i = 0; i < Linhas; i++){
        ME[i] = NULL;
    }
}

void InserirNaMatriz(Matriz ME, int Linhas, int Colunas, int Valor){
    PonteiroME Novo, P;
    Novo = (PonteiroME)malloc(sizeof(struct No));
    Novo->Valor = Valor;
    Novo->Coluna = Colunas;
    Novo->Proximo = NULL;
    if(ME[Linhas] == NULL){
        ME[Linhas] = Novo;
    }
    else{
        P = ME[Linhas];
        while(P->Proximo != NULL){
            P = P->Proximo;
        }
        P->Proximo = Novo;
    }
}


void ImprimirMatriz(Matriz ME, int Linhas, int Colunas){
    int i, j;
    PonteiroME P;
    for(i = 0; i < Linhas; i++){
        P = ME[i];
        for(j = 0; j < Colunas; j++){
            if(P==NULL || P->Coluna != j){
                printf("0\t");
            }
            else{
                printf("%d\t", P->Valor);
                P = P->Proximo;
            }
        }
        printf("\n");
    }
}

void Liberar(PonteiroME *ME, int Linhas){
    PonteiroME P, Temporario;
    int i;
    for(i = 0; i < Linhas; i++){
        P = ME[i];
        while(P != NULL){
            Temporario = P;
            P = P->Proximo;
            free(Temporario);
        }
        ME[i] = NULL;
    }
}


int main(){
    Matriz ME;
    int Linhas, Colunas, i, j, Valor;
    do{
        printf("Quantidade de Linhas: ");
        scanf("%i", &Linhas);
    }while(Linhas <= 0 || Linhas > MAX_LINHA);
    do{
        printf("Quantidade de Colunas: ");
        scanf("%i", &Colunas);
    }while(Colunas <= 0 || Colunas > 100);
    InicializarMatriz(ME, Linhas);
    for(i = 0; i < Linhas; i++){
        for(j = 0; j < Colunas; j++){
            printf("Ponto[%d][%d] = ", i+1, j+1);
            scanf("%d", &Valor);
            if(Valor != 0){
                InserirNaMatriz(ME, i, j , Valor);
            }
        }
    }
    ImprimirMatriz(ME, Linhas, Colunas);
    Liberar(ME, Linhas);
    return(0);
}