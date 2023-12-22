#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int Coluna, Valor;
    struct No *Proximo;
} No;

typedef No *PonteiroME;
typedef PonteiroME *Matriz;

void InicializarMatriz(Matriz ME, int Linhas, int Colunas) {
    int i;
    for (i = 0; i < Linhas; i++) {
        ME[i] = NULL;
    }
}

int VerificarLocal(Matriz ME, int Linhas, int Colunas, int i, int j) {
    if (i < 0 || i >= Linhas || j < 0 || j >= Colunas) {
        return -2;
    }
    PonteiroME P = ME[i];
    while (P != NULL) {
        if (P->Coluna == j) {
            return P->Valor;
        }
        P = P->Proximo;
    }
    return 0;
}

int InserirBombaNaMatriz(Matriz ME, int Linhas, int Colunas, int i, int j) {
    int Verificador = VerificarLocal(ME, Linhas, Colunas, i, j);
    
    if (Verificador >= 0) {
        PonteiroME Novo, P;
        Novo = (PonteiroME)malloc(sizeof(No));
        Novo->Valor = -1;
        Novo->Coluna = j;
        Novo->Proximo = NULL;

        if (ME[i] == NULL || ME[i]->Coluna > j) {
            // Inserir no início da lista ou se a lista está vazia
            Novo->Proximo = ME[i];
            ME[i] = Novo;
        } else {
            P = ME[i];
            while (P->Proximo != NULL && P->Proximo->Coluna < j) {
                P = P->Proximo;
            }
            
            Novo->Proximo = P->Proximo;
            P->Proximo = Novo;
        }
        return 0;
    } else {
        if (Verificador == -1) {
            return -1;
        } else {
            return -2;
        }
    }
}


void CasasAdjacentes(Matriz ME, int Linhas, int Colunas, int i, int j) {
    int Verificador, Linha, Coluna;

    for (Linha = i - 1; Linha <= i + 1; Linha++) {
        for (Coluna = j - 1; Coluna <= j + 1; Coluna++) {
            if (Linha >= 0 && Linha < Linhas && Coluna >= 0 && Coluna < Colunas && !(Linha == i && Coluna == j)) {
                Verificador = VerificarLocal(ME, Linhas, Colunas, Linha, Coluna);

                PonteiroME P = ME[Linha];
                PonteiroME Anterior = NULL;

                while (P != NULL && P->Coluna < Coluna) {
                    Anterior = P;
                    P = P->Proximo;
                }

                if (P != NULL && P->Coluna == Coluna) {
                    P->Valor += (P->Valor != -1) ? 1 : 0;  // Increment only if not a bomb
                } else {
                    PonteiroME Novo = (PonteiroME)malloc(sizeof(struct No));
                    Novo->Valor = (Verificador != -1) ? 1 : 0;  // Set 1 if not a bomb, else 0
                    Novo->Coluna = Coluna;
                    Novo->Proximo = P;

                    if (Anterior == NULL) {
                        ME[Linha] = Novo;
                    } else {
                        Anterior->Proximo = Novo;
                    }
                }
            }
        }
    }
}

void ImprimirMatriz(Matriz ME, int Linhas, int Colunas) {
    int i, j;
    for (i = 0; i < Linhas; i++) {
        for (j = 0; j < Colunas; j++) {
            PonteiroME P = ME[i];
            int bombaEncontrada = 0;

            while (P != NULL) {
                if (P->Coluna == j) {
                    if (P->Valor == -1) {
                        bombaEncontrada = 1;
                        break;
                    }
                }
                P = P->Proximo;
            }

            if (bombaEncontrada) {
                printf("X ");
            } else {
                int Contador = VerificarLocal(ME, Linhas, Colunas, i, j);
                if (Contador == -1) {
                    printf("x ");  // x para célula contendo bomba
                } else {
                    printf("%i ", Contador);
                }
            }
        }
        printf("\n");
    }
}


int main() {
    Matriz ME;
    int Linhas, Colunas, i, j, Contador, QtdBombas, Verificador;
    do {
        scanf("%i", &Linhas);
    } while (Linhas < 0);
    do {
        scanf("%i", &Colunas);
    } while (Colunas < 0 || Colunas > 100);

    ME = (Matriz)malloc(Linhas * sizeof(PonteiroME));
    for (int k = 0; k < Linhas; k++) {
        ME[k] = NULL;
    }

    do {
        scanf("%i", &QtdBombas);
    } while (QtdBombas < 0 || QtdBombas > 60);

    for (Contador = 0; Contador < QtdBombas; Contador++) {
        scanf("%d %d", &i, &j);
        if (InserirBombaNaMatriz(ME, Linhas, Colunas, i, j) >= 0) {
            CasasAdjacentes(ME, Linhas, Colunas, i, j);
        }
    }

    ImprimirMatriz(ME, Linhas, Colunas);

    for (i = 0; i < Linhas; i++) {
        PonteiroME P = ME[i];
        while (P != NULL) {
            PonteiroME temp = P;
            P = P->Proximo;
            free(temp);
        }
    }
    free(ME);

    return 0;
}
