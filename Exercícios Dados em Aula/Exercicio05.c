//AED 1 - Lista Din√¢mica - 19/09/23

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct no{
    int info;
    struct no* prox;
} TNo;
typedef TNo *PNo;

typedef struct fila{
    PNo ini;
    PNo fim;
} TFila;
typedef TFila *PFila;

PFila cria(){
    PFila f = (PFila)malloc(sizeof(TFila));
    f->ini = f->fim = NULL;
    return (f);
}

PFila insere(PFila f, int v){
    PNo novo;

    novo = (PNo)malloc(sizeof(TNo));
    novo->info = v;
    novo->prox = NULL;
    if(f->ini==NULL){
        f->ini=novo;
    }
    else{
        f->fim->prox=novo;
    }
    f->fim=novo;
    return (f);
}

PFila remover(PFila f, int *v){
    if(f == NULL || f->ini == NULL){
        printf("A fila est· vazia.\n");
        return f;
    }

    PNo p = f->ini;
    *v = p->info;
    f->ini = p->prox;

    if(f->ini == NULL){
        f->fim = NULL;
    }

    free(p);
    return f;
}


void imprime(PFila f){
    PNo p;
    
    for(p=f->ini; p!=NULL; p=p->prox){
        printf("%d\n", p->info);
    }
}

void libera(PFila f){
    PNo p;

    for(p=f->ini; p!=NULL; p=f->ini){
        f->ini=f->ini->prox;
        free(p);
    }
    free(f);
}

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");

    PFila f = cria();    
    int n, i, v;
    
    printf("Digite a quantidade de elementos que deseja inserir na lista: ");
    scanf("%d", &n);
    
    for(i=0; i<n; i++){
        printf("Digite o valor do elemento %d: ", i+1);
        scanf("%d", &v);
        f = insere(f, v);
    }
    
    printf("Os elementos da lista s„o: ");
    imprime(f);
    libera(f);
    
    return 0;
}