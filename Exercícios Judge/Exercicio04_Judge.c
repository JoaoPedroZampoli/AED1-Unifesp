#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

// Definindo o Tipo de Dado da Fila
typedef struct Cliente {
    int Id;
    int Tempo;
    struct Cliente* Proximo;
} Cliente;

// Criação da Fila em si, declarando o 1º e o último elemento, além disso tem o tamanho da Fila
typedef struct Fila {
    Cliente* Inicio;
    Cliente* Fim;
    int Tamanho;
} Fila;

// Inicializando Lista Vazia
void InicializarFila(Fila* F) {
    F->Inicio = NULL;
    F->Fim = NULL;
    F->Tamanho = 0;
}

// Inserindo Cliente
void InserirCliente(Fila* F, int Id, int Tempo) {
    Cliente* Novo = (Cliente*)malloc(sizeof(Cliente));
    if (Novo == NULL) {
        exit(1);
    }
    Novo->Id = Id;
    Novo->Tempo = Tempo;
    Novo->Proximo = NULL;

    if (F->Tamanho == 0) {
        F->Inicio = Novo;
        F->Fim = Novo;
    }
    else {
        F->Fim->Proximo = Novo;
        F->Fim = Novo;
    }
    F->Tamanho++;
}

void Remover(Fila* F) {
    if (F->Tamanho > 0) {
        Cliente* Auxiliar = F->Inicio;
        F->Inicio = F->Inicio->Proximo;
        free(Auxiliar);
        F->Tamanho--;
        if (F->Tamanho == 0) {
            F->Fim = NULL;
        }
    }
    else {
        exit(1);
    }
}

void Atender(Fila *Clientes, int Atendentes) {
    int i, j, k;
    int TempoTotal = 0;
    int *Caixa = (int *)malloc(Atendentes * sizeof(int));
    int **Atendimento = (int **)malloc(Atendentes * sizeof(int*)); 

    for(i = 0; i < Atendentes; i++){
        Atendimento[i] = (int *)malloc(Clientes->Tamanho * sizeof(int));
    }

    for(i = 0; i < Atendentes; i++){
        Caixa[i] = 0;
        for(j = 0; j < Clientes->Tamanho; j++){
            Atendimento[i][j] = -1;
        }
    }

    int clienteId = 1;

    while (Clientes->Tamanho > 0) {
        for (k = 0; k < Atendentes; k++) {
            if (Caixa[k] == 0 && Clientes->Tamanho > 0) {
                Caixa[k] = Clientes->Inicio->Tempo;
                Atendimento[k][clienteId - 1] = clienteId;
                clienteId++;
                Remover(Clientes);
            }
            if (Caixa[k] > 0) {
                Caixa[k]--;
            }
        }
        TempoTotal++;
    }

    for(k = 0; k < Atendentes; k++){
        printf("%d:", k + 1);
        for(j = 0; j < Clientes->Tamanho + clienteId - 1; j++){
            if (Atendimento[k][j] != -1) {
                printf(" %d", Atendimento[k][j]);
            }
        }
        printf("\n");
        free(Atendimento[k]);
    }

    free(Atendimento);
    free(Caixa);
}


int main() {
    setlocale(LC_ALL, "Portuguese_Brazil");
    Fila Clientes;
    int NumeroClientes, Atendentes, Id = 1, TempoAtendimento, i;
    InicializarFila(&Clientes);

    do {
        scanf("%i", &NumeroClientes);
    } while (NumeroClientes < 1 || NumeroClientes > 1023);
    do {
        scanf("%i", &Atendentes);
    } while (Atendentes < 1 || Atendentes > 25);

    for (i = 0; i < NumeroClientes; i++) {
        do {
            scanf("%i", &TempoAtendimento);
        } while (TempoAtendimento < 0 || TempoAtendimento > 1000);
        InserirCliente(&Clientes, Id, TempoAtendimento);
        Id++;
    }

    Atender(&Clientes, Atendentes);

    Cliente* current = Clientes.Inicio;
    while (current != NULL) {
        Cliente* temp = current;
        current = current->Proximo;
        free(temp);
    }

    exit(0);
}
