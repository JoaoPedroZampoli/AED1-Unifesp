#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define MAX_LINHA 100

typedef struct No *PME;
struct No{
    int Coluna, Valor;
    PME Proximo;
};

typedef PME Matriz[MAX_LINHA];

void MaiorValor(Matriz M, int Linhas){
    int i, Maior, i_Maior;
    PME P, PMaior, PAnterior, PAnterior_Maior;
    for(i = 0; i < Linhas && M[i] == NULL; i++){
        if(i >= Linhas){
            return;
        }
        Maior = M[i]->Valor;
        for(; i < Linhas; i++){
            PAnterior = NULL;
            for(P = M[i]; P != NULL; P=P->Proximo){
                if(P->Valor >= Maior){
                    Maior = P->Valor;
                    PMaior = P;
                    PAnterior_Maior = PAnterior;
                    i_Maior = i;
                }
                PAnterior = P;
            }
            if(PAnterior_Maior == NULL){
                M[i_Maior] = PMaior->Proximo;
            }
            else{
                PAnterior_Maior->Proximo = PMaior->Proximo;
            }
            free(PMaior);
        }
    }
}

int main(){

}