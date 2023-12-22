#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Horas {
    int Horas, Minutos;
};

struct Estacionamento {
    struct Horas HorarioEntrada, HorarioSaida;
};

typedef struct Estacionamento Gerenciamento;

void LerVeiculo(Gerenciamento *, int *);
void SaidaVeiculo(Gerenciamento *, int *, float *);

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    Gerenciamento *P;
    int N_Vagas, Opcao, TamanhoVetor = 0, i;
    float Faturamento = 0;

    do {
        printf("\nDigite a Quantidade de Vagas no Estacionamento: ");
        scanf("%d", &N_Vagas);
        if (N_Vagas < 1) {
            printf("\nDigite uma Quantidade Maior que 0: ");
        }
    } while (N_Vagas < 1);

    P = (Gerenciamento *)malloc(N_Vagas * sizeof(Gerenciamento));

    do {
        printf("\n\n1) Estacionar");
        printf("\n2) Retirar Veículo");
        printf("\n3) Faturamento");
        printf("\n4) Sair");
        printf("\n\nOpção: ");
        scanf("%d", &Opcao);

        switch (Opcao) {
            case 1:
                if (TamanhoVetor == N_Vagas) {
                    printf("\n\nEstacionamento Cheio");
                } else {
                    LerVeiculo(P, &TamanhoVetor);
                }
                break;
            case 2:
                SaidaVeiculo(P, &TamanhoVetor, &Faturamento);
                break;
            case 3:
                printf("\n\nO Faturamento é de: R$ %.2f", Faturamento);
                break;
        }

        if (Opcao < 1 || Opcao > 4) {
            printf("\n\nOpção Inválida. Tente Novamente");
        }
    } while (Opcao != 4);

    free(P);
    return 0;
}

void LerVeiculo(Gerenciamento *P, int *TamanhoVetor) {
    printf("\nDigite o Horário de Chegada (hh:mm):");
    scanf("%d %d", &P[*TamanhoVetor].HorarioEntrada.Horas, &P[*TamanhoVetor].HorarioEntrada.Minutos);
    (*TamanhoVetor)++;
}

void SaidaVeiculo(Gerenciamento *P, int *Tamanho, float *Faturamento) {
    int Vaga, Horas, Minutos;

    if (*Tamanho == 0) {
        printf("Não há Veículos Estacionados!\n");
        return;
    }

    printf("Digite o Número da Vaga do Veículo: ");
    scanf("%d", &Vaga);
    Vaga--;

    printf("\nDigite o Horário de Saída (hh:mm): ");
    scanf("%d %d", &P[Vaga].HorarioSaida.Horas, &P[Vaga].HorarioSaida.Minutos);

    Horas = P[Vaga].HorarioSaida.Horas - P[Vaga].HorarioEntrada.Horas;
    if (Horas < 0) {
        Horas += 24;
    }

    Minutos = P[Vaga].HorarioSaida.Minutos - P[Vaga].HorarioEntrada.Minutos + Horas * 60;

    if (Minutos < 0) {
        printf("Hora Inválida!\n");
        return;
    }

    if (Minutos > 15) {
        *Faturamento += (Minutos / 60) * 3;
        if (Minutos % 60 > 0) {
            *Faturamento += 3;
        }
    }

    for (int i = Vaga; i < *Tamanho - 1; i++) {
        P[i] = P[i + 1];
    }

    (*Tamanho)--;
}
