#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Pilha{
    int *Dados;
    int Tamanho;
    int Topo;
}Pilha;

void Inicio(Pilha *P1, int Tamanho){
    P1->Dados = (int*)malloc(sizeof(int) * Tamanho);
    if(P1->Dados == NULL){
        printf("\nFalha na Aloca��o de Mem�ria");
    }
    P1->Tamanho = Tamanho;
    P1->Topo = -1;
}

int Vazia(Pilha *P1){
    if(P1->Topo == -1){
        return 0;
    }
    else{
        return 1;
    }
}

int Cheia(Pilha *P1){
    if(P1->Tamanho == P1->Topo+1){
        return 0;
    }
    else{
        return 1;
    }
}

int Pop(Pilha *P1){
    if(Vazia(P1) == 0){
        printf("\nPilha j� est� vazia!");
        return -1;
    }
    else{
        return P1->Dados[P1->Topo--];
    }
}

int Push(Pilha *P1, int Dado){
    if(Cheia(P1) == 0){
        printf("\nPilha j� est� cheia");
        return -1;
    }
    else{
        return P1->Dados[++P1->Topo] = Dado;
    }
}

// Imprime(Pilha *P1){
//     if(Vazia(P1) == 0){
//         printf("\nNão há Elementos para Mostrar");
//     }
//     else{
//         printf("Pilha: ");
//         for()
//     }
// }

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int T, N, i;
    Pilha P1;

    printf("Digite o Tamanho Desejado para a Pilha: ");
    scanf("%i", &T);
    Inicio(&P1, T);
    for(i = 0; i < T; i++){
        printf("Digite o %i� N�mero: ", i+1);
        scanf("%i", &N);
        Push(&P1, N);
    }
    while(Vazia(&P1) != 0){
        printf("%i", Pop(&P1));
    }
}