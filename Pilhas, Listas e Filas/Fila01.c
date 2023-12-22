#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Fila{
    int *Dados;
    int Tamanho;
    int Inicio, Fim;
}Fila;

void Inicio(Fila *F1, int Tamanho){
    F1->Dados = (int*)malloc(sizeof(int) * Tamanho);
    if(F1->Dados == NULL){
        printf("\nFalha na Alocação de Memória");
    }
    F1->Tamanho = Tamanho;
    F1->Inicio = 0;
    F1->Fim = -1;
}

int Vazia(Fila *F1){
    if(F1->Inicio > F1->Fim){
        return 0;
    }
    else{
        return 1;
    }
}

int Cheia(Fila *F1){
    if(F1->Fim == F1->Tamanho-1){
        return 0;
    }
    else{
        return 1;
    }
}

int TirarDaFila(Fila *F1){
    if(Vazia(F1) == 0){
        printf("\nA fila já está vazia!");
        return -1;
    }
    else{
        return F1->Dados[F1->Inicio++];
    }
}

int ColocarNaFila(Fila *F1, int Dado){
    if(Cheia(F1) == 0){
        printf("\nA fila já está cheia");
        return -1;
    }
    else{
        return F1->Dados[++F1->Fim] = Dado;
    }
}

Liberar(Fila *P1){
    free(P1->Dados);
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int T, N, i;
    Fila F1;

    printf("Digite o Tamanho Desejado para a Fila: ");
    scanf("%i", &T);
    Inicio(&F1, T);
    
    for(i = 0; i < T; i++){
        printf("Digite o %iº Número: ", i+1);
        scanf("%i", &N);
        ColocarNaFila(&F1, N);
    }
    
    while(Vazia(&F1) != 0){
        printf("%i", TirarDaFila(&F1));
    }
}
