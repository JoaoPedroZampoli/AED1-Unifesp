//João Pedro da Silva Zampoli - RA: 168.880 - AED 1 I
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
 
struct Corredores{
    int NumeroCarro;
    char NomeCompetidor[21];
};
typedef struct Corredores *InfoCorredor;
 
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int N, i, j, Repetir, *Posicoes, Correspondencia, CarroUltrapassando, PosicaoCarroUltrapassando, Temporario;
    InfoCorredor *VetorCorredores;
 
    //Comentado para aparecer como deve aparecer no Judge
    //printf("Exercício 02 - Corrida Maluca");
    do{
        //printf("\nDigite o Número de Participantes da Corrida (Devendo estar entre 3 e 1000): ");
        scanf("%i", &N);
    }while(N < 3 || N > 1000);
 
    VetorCorredores = (InfoCorredor *)malloc(N *sizeof(InfoCorredor));
    Posicoes = (int *)malloc(N * sizeof(int));
    //Necessário Verificar se memória foi realmente alocada
    for(i = 0; i < N; i++){
        VetorCorredores[i] = (InfoCorredor)malloc(sizeof(struct Corredores));
        do{
            Repetir = 0;
            //printf("\nDigite o Número do Carro do Competidor: ");
            scanf("%i", &VetorCorredores[i]->NumeroCarro);
            if(VetorCorredores[i]->NumeroCarro <= 0){
                //printf("Número do carro deve ser um inteiro positivo");
                Repetir = 1;
            }
            else{
                for(j = 0; j < i; j++){
                    if(VetorCorredores[j]->NumeroCarro == VetorCorredores[i]->NumeroCarro){
                        Repetir = 1;
                        //printf("Número de Carro já utilizado, por favor digite outro número: ");
                    }
                }
            }
        }while(Repetir == 1);
        //printf("\nDigite o Nome do Corredor: ");
        //printf(" ");
        //Scanf da String é diferente, não precisa do &
        scanf("%s", VetorCorredores[i]->NomeCompetidor);
    }
    //printf("\nDigite a Ordem de Largada dos Carros pelos seus respectivos Números: ");
    for(i = 0; i < N; i++){
        Correspondencia = 0;
        do{
            Repetir = 0;
            scanf("%i", &Posicoes[i]);
            for(j = 0; j < N; j++){
                if(Posicoes[i] == VetorCorredores[j]->NumeroCarro){
                    Correspondencia = 1;
                    break;
                }
            }
            if(Correspondencia <= 0){
                //printf("\nNúmero de Carro Inexistente para essa Competição");
                //printf("\nDigite Novamente: ");
                Repetir = 1;
            }
        }while(Repetir == 1);
        //printf(" ");
    }
    //printf("\nApós o Começo da Corrida, Envie abaixo as alterações de posições: \n");
    do{
        //printf("\nCorredor: ");
        scanf("%i", &CarroUltrapassando);
        for(i = 0; i < N; i++){
            if(Posicoes[i] == CarroUltrapassando){
                PosicaoCarroUltrapassando = i;
                break;
            }
        }
        if(PosicaoCarroUltrapassando > 0){
            Temporario = Posicoes[PosicaoCarroUltrapassando];
            Posicoes[PosicaoCarroUltrapassando] = Posicoes[PosicaoCarroUltrapassando-1];
            Posicoes[PosicaoCarroUltrapassando - 1] = Temporario;
        }
    }while(CarroUltrapassando != -1);
    //printf("\nO pódio da Corrida é:");
    for(i = 0; i < 3; i++){
        for(j = 0; j < N; j++){
            if(VetorCorredores[j]->NumeroCarro == Posicoes[i]){
                //printf("\n%i° Lugar: %i %s", i+1, VetorCorredores[j]->NumeroCarro, VetorCorredores[j]->NomeCompetidor);
                printf("\n%i %s", VetorCorredores[j]->NumeroCarro, VetorCorredores[j]->NomeCompetidor);
                break;
            }
        }
    }
    for(i = 0; i < N; i++){
        free(VetorCorredores[i]);
    }
    free(VetorCorredores);
    free(Posicoes);
}