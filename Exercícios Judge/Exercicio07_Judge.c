//João Pedro da Silva Zampoli - RA: 168.880 - AED 1 I
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
 
#define TAM_NOME 50
 
typedef struct ArvGen{
    char Info[TAM_NOME];
    char NomeQuemIndicou[TAM_NOME];
    int Dia, Mes, Ano;
    struct ArvGen *PrimFilho;
    struct ArvGen *ProxIrmao;
}TArvGen;
 
typedef TArvGen *PArvGen;

//Percorre a Árvore para tentar achar um funcionário com mesmo nome 
PArvGen BuscarFuncionario(PArvGen Arvore, char *Nome){
    if(Arvore == NULL){
        return NULL;
    }
 
    if(strcmp(Arvore->Info, Nome) == 0){
        return Arvore;
    }
 
    PArvGen Resultado = BuscarFuncionario(Arvore->PrimFilho, Nome);
    if(Resultado != NULL){
        return Resultado;
    }
 
    return BuscarFuncionario(Arvore->ProxIrmao, Nome);
}
 
//Realiza Verificações para saber onde adicionar o Funcionário na Árvore por meio de comparação das datas de contratação
void InserirSubArvore(PArvGen Arvore, PArvGen SubArvore){
    if(Arvore->PrimFilho == NULL){
        Arvore->PrimFilho = SubArvore;
    }else{
        PArvGen Irmao = Arvore->PrimFilho;
        PArvGen IrmaoAnterior = NULL;
        while (Irmao != NULL && 
                (Irmao->Ano < SubArvore->Ano || 
                (Irmao->Ano == SubArvore->Ano && Irmao->Mes < SubArvore->Mes) || 
                (Irmao->Ano == SubArvore->Ano && Irmao->Mes == SubArvore->Mes && Irmao->Dia <= SubArvore->Dia))){
            IrmaoAnterior = Irmao;
            Irmao = Irmao->ProxIrmao;
        }
        if(IrmaoAnterior == NULL){
            SubArvore->ProxIrmao = Arvore->PrimFilho;
            Arvore->PrimFilho = SubArvore;
        }else{
            SubArvore->ProxIrmao = IrmaoAnterior->ProxIrmao;
            IrmaoAnterior->ProxIrmao = SubArvore;
        }
    }
}

//Criação de Nova SubArvore (Irmão ou Filho) 
PArvGen CriarArvore(PArvGen Raiz, char *Nome, int Dia, int Mes, int Ano, char *NomeQuemIndicou){
    PArvGen Arvore = (PArvGen)malloc(sizeof(TArvGen));
    if(Arvore == NULL){
        printf("Erro de Alocação de Memória");
        exit(1);
    }
    strcpy(Arvore->Info, Nome);
    Arvore->Dia = Dia;
    Arvore->Mes = Mes;
    Arvore->Ano = Ano;
    Arvore->PrimFilho = NULL;
    Arvore->ProxIrmao = NULL;
 
    if(NomeQuemIndicou != NULL){
        PArvGen Indicador = BuscarFuncionario(Raiz, NomeQuemIndicou);
        if(Indicador != NULL){
            InserirSubArvore(Indicador, Arvore);
        }
        else{
            //printf("\nERROR");
            free(Arvore);
            Arvore = NULL;
        }
    }
    return Arvore;
}
 
//Inserir Funcionário na Árvore(Empresa) e realiza a verificação de onde deve ser colocado)
void InserirFuncionario(PArvGen Raiz, char *Nome, int Dia, int Mes, int Ano, char *NomeQuemIndicou){
    PArvGen NovoFuncionario = CriarArvore(Raiz, Nome, Dia, Mes, Ano, NomeQuemIndicou);
    if(NovoFuncionario != NULL && NomeQuemIndicou == NULL){
        InserirSubArvore(Raiz, NovoFuncionario);
    }
}
 
//Impressão de Árvore
void ImprimirPresidente(PArvGen Arvore){
    if(Arvore == NULL){
        return;
    }
    printf("%s\n", Arvore->Info);
    ImprimirPresidente(Arvore->PrimFilho);
    ImprimirPresidente(Arvore->ProxIrmao);
}
 
//Função Compara informações dadas com busca na árvore na tentativa de achar alguém com mesmo nome
//Cria Árvore temporária para poder fazer a remoção do Nó atual e não quebrar a árvore
void DemitirFuncionario(PArvGen *Arvore, char *Nome){
    if(*Arvore == NULL){
        return;
    }
 
    if(strcmp((*Arvore)->Info, Nome) == 0){
        PArvGen Filho =(*Arvore)->PrimFilho;
        while(Filho != NULL){
            PArvGen ProximoFilho = Filho->ProxIrmao;
            DemitirFuncionario(&Filho, Filho->Info);
            Filho = ProximoFilho;
        }
 
        PArvGen Temp = *Arvore;
        *Arvore =(*Arvore)->ProxIrmao;
        free(Temp);
    }
    else{
        DemitirFuncionario(&(*Arvore)->PrimFilho, Nome);
        DemitirFuncionario(&(*Arvore)->ProxIrmao, Nome);
    }
}
 
//Liberação de Memória
void Liberar(PArvGen Arvore){
    if(Arvore != NULL){
        Liberar(Arvore->PrimFilho);
        Liberar(Arvore->ProxIrmao);
        free(Arvore);
    }
}
 
int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int Opcao, Dia, Mes, Ano;
    char Nome[TAM_NOME], NomeQuemIndicou[TAM_NOME];
    PArvGen Empresa = NULL;
 
    do{
        /*printf("1 - Contratação");
        printf("\n2 - Demissão");
        printf("\n3 - Impressão da Ordem de Presidentes");
        printf("\n4 - Sair");
        printf("\nOpção: ");*/
        scanf("%i", &Opcao);
        switch(Opcao){
            case 1:
                scanf("%s %d %d %d %s", Nome, &Dia, &Mes, &Ano, NomeQuemIndicou);
 
                if(Empresa == NULL){
                    if(strcmp(NomeQuemIndicou, "fundador") == 0){
                        Empresa = CriarArvore(Empresa, Nome, Dia, Mes, Ano, NULL);
                    }
                    else{
                        //printf("\nERROR! Não há fundador.\n");
                    }
                }
                else{
                    if (BuscarFuncionario(Empresa, Nome) != NULL){
                        //printf("\nERRO! Funcionário com nome já existente.\n");
                    }
                    else{
                        InserirFuncionario(Empresa, Nome, Dia, Mes, Ano, NomeQuemIndicou);
                    }
                }
                break;
            case 2:
                scanf("%s", Nome);
                DemitirFuncionario(&Empresa, Nome);
                break;
            case 3:
                ImprimirPresidente(Empresa);
                break;
        }
    }while(Opcao != 4);
 
    // Liberar a árvore antes de encerrar o programa
    Liberar(Empresa);
 
    return 0;
}