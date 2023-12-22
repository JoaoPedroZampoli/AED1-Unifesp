#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int menor(int *, int, int *);
int maior(int *, int, int *);
int busca(int *, int, int);

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    int tamanho, *n, i, opcao, valor;
    //n � o vetor
    printf("Exerc�cio 01 - Dado em Sala de Aula");
    printf("\nDigite o Tamanho do Vetor: ");
    scanf("%d", &tamanho);
    n = (int *)malloc(tamanho*sizeof(int));
    //Verificar se mem�ria foi alocada
    for(i = 0; i < tamanho; i++){
        printf("Posi��o [%d]: ", i);
        scanf("%d", (n+i));
    }
    do{
        do{
            printf("\nO Que Voc� Pretende Procurar no Vetor?\n");
            printf("1) Menor Valor \n2) Maior Valor \n3) Um Valor Espec�fico \n4) Finalizar\n\nOp��o:");
            scanf("%d", &opcao);
        }while(opcao < 1 || opcao > 4);
        if(opcao == 1){
            i = menor(n, tamanho, &valor);
            printf("\nO menor valor � %d e est� na posi��o %d\n", valor, i);
        }
        else if(opcao == 2){
            i = maior(n, tamanho, &valor);
            printf("\nO maior valor � %d e est� na posi��o %d\n", valor, i);
        }
        else if(opcao == 3){
            printf("\nDigite o valor a ser buscado: ");
            scanf("%d", &valor);
            i = busca(n, tamanho, valor);
            if(i < 0){
                printf("\nValor n�o Encontrado!\n");
            }
            else{
                printf("\nO valor est� na posi��o: %d", i);
            }
        }
    }while(opcao != 4);
    free(n);
    return(0);
}

int menor(int *v, int tamanho, int *a){
    int i, pos = 0;
    *a = *v;
    for(i = 1; i < tamanho; i++){
        if(*(v+i) < *a){
            *a = *(v+i);
            pos = i;
        }
    }
    return(pos);
}

int maior(int *v, int tamanho, int *a){
    int i, pos = 0;
    *a = *v;
    for(i = 1; i < tamanho; i++){
        if(*(v+i) > *a){
            *a = *(v+i);
            pos = i;
        }
    }
    return(pos);
}

int busca(int *v, int tamanho, int valor){
    int i;
    for(i = 0; i < tamanho; i++){
        if(*(v+i) == valor){
            return i;
        }
    }
    return -1;
}
