//Jo�o Pedro da Silva Zampoli - RA: 168.880 - AED 1 I
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//Coment�rios para ficar no Padr�o do Judge
int ChecagemInvalido = 0;

typedef struct Pilha{
    int Dados;
    struct Pilha*Proximo;
}NoPilha;
typedef NoPilha *PPilha;

PPilha NovaPilha(int Dados){
    PPilha Pilha = (PPilha)malloc(sizeof(NoPilha));
    if(Pilha == NULL){
        //printf("\nOcorreu um Erro ao Alocar um Espa�o de Mem�ria");
        ChecagemInvalido = 1;
        exit(1);
    }
    Pilha->Dados = Dados;
    Pilha->Proximo = NULL;
    return Pilha;
}

void push(PPilha* Topo, int Dados){
    PPilha Pilha = NovaPilha(Dados);
    Pilha->Proximo = *Topo;
    *Topo = Pilha;
}

int VerificarListaVazia(PPilha Topo){
    if(Topo == NULL){
        return 1;
    }
    else{
        return 0;
    }
}

int pop(PPilha* Topo){
    if(VerificarListaVazia(*Topo)){
        //printf("\nExpress�o Inv�lida");
        ChecagemInvalido = 1;
        printf("\nInvalid Expression");
        exit(1);
    }
    PPilha Temporario = *Topo;
    *Topo = (*Topo)->Proximo;
    int Poppou = Temporario->Dados;
    free(Temporario);
    return(Poppou);
}

int OperacionarNotacao(char* Expressao){
    PPilha Pilha = NULL;
    int i;
    for(i = 0; Expressao[i]!='\0'; i++){
        if(Expressao[i] >= '0' && Expressao[i] <= '9'){
            int Valor = Expressao[i] - '0';
            push(&Pilha, Valor);
        }
        else{
            if(VerificarListaVazia(Pilha) || VerificarListaVazia(Pilha->Proximo)){
                //printf("\nExpress�o Inv�lida");
                ChecagemInvalido = 1;
                printf("\nInvalid Expression");
                exit(1);
            }
            int Valor1 = pop(&Pilha);
            int Valor2 = pop(&Pilha);
            switch (Expressao[i]){
                case '+': 
                    push(&Pilha, Valor2 + Valor1); 
                break;
                case '-': 
                    push(&Pilha, Valor2 - Valor1);
                break;
                case '*': 
                    push(&Pilha, Valor2 * Valor1);
                break;
                case '/':
                    if(Valor1 == 0){
                        ChecagemInvalido = 1;
                        printf("\nInvalid Expression");
                        exit(1);
                    }
                else{
                    push(&Pilha, Valor2/Valor1);
                }
                break;
            }
        }
    }
    if(VerificarListaVazia(Pilha)){
        //printf("\nExpress�o Inv�lida");
        ChecagemInvalido = 1;
        //printf("\nInvalid Expression");
        exit(1);
    }
    return pop(&Pilha);
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    char Expressao[1024];
    int Resultado, ChecagemResultado = 0;
    PPilha Pilha = NULL;

    //printf("\nExerc�cio 03 - Judge");
    //printf("\nNota��o Polonesa P�s Fixa");
    fgets(Expressao, sizeof(Expressao), stdin);
    Expressao[strcspn(Expressao, "\n")] = 0;
    if(strlen(Expressao) <= 1 || strlen(Expressao) > 1024){
        //printf("\nInforme a Express�o Matem�tica na Nota��o Polonesa P�s-Fixa:");
        printf("\nInvalid Expression");
        exit(1);
    }
    Resultado = OperacionarNotacao(Expressao);
    if(ChecagemInvalido == 1){
        printf("\nInvalid Expression");
        exit(1);
    }
    else{
        //printf("\nO Resultado �: %d", Resultado);
        printf("%d", Resultado);
    }

    while (!VerificarListaVazia(Pilha)) {
        pop(&Pilha);
    }

    free(Pilha);
    return 0;
}
