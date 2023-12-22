//Exercicio 04 - Ponteiros
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno{
    char Nome[80];
    int Matricula;
    char Endereco[30];
    char Telefone[20];
};

typedef struct aluno *PAluno;

void Alocar(PAluno Aluno[], int i){
    Aluno[i] = (PAluno)malloc(sizeof(struct aluno));
}

int main(){
    PAluno Aluno[100];
    int i = 0, j;
    char Resp;
    do{
        Alocar(Aluno, i);
        Ler(Aluno, i);
        i++;
        printf("\nDeseja cadastrar mais alunos?\n");
        Resp = getchar();
    }while(Resp == "S" || Resp == "s");
    for(j = 0; j < i; j++){
        Mostrar(Aluno, j);
    }
    for(j = 0; j < i; j++){
        free(Aluno[j]);
    }

    return 0;
}