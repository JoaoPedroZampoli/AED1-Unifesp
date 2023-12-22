#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define RET 0
#define TRI 1
#define CIR 2
#define PI (3.141592653589793)

typedef struct Retangulo{
    float b;
    float h;
}TRetangulo;

typedef struct Triangulo{
    float b;
    float h;
}TTriangulo;

typedef struct Circulo{
    float r;
}TCirculo;

typedef struct ListaGen{
    int Tipo;
    void *Info;
    struct ListaGen *Prox;
}TListaGen;

TListaGen *CriaRet(float b, float h){
    TRetangulo *R;
    TListaGen *P;
    //Alocação do Retângulo
    R = (TRetangulo*)malloc(sizeof(TRetangulo));
    R->b = b;
    R->h = h;
    //Alocação do Nó
    P = (TListaGen*)malloc(sizeof(TListaGen));
    P->Tipo = RET;
    P->Info = R;
    P->Prox = NULL;
    return P;
}

TListaGen *CriaTri(float b, float h){
    TTriangulo *T;
    TListaGen *P;
    //Alocação do Triângulo
    T = (TTriangulo*)malloc(sizeof(TTriangulo));
    T->b = b;
    T->h = h;
    //Alocação do Nó
    P = (TListaGen*)malloc(sizeof(TListaGen));
    P->Tipo = TRI;
    P->Info = T;
    P->Prox = NULL;
    return P;
}

TListaGen *CriaCir(float r){
    TCirculo *C;
    TListaGen *P;
    //Alocação do Círculo
    C = (TCirculo*)malloc(sizeof(TCirculo));
    C->r = r;
    //Alocação do Nó
    P = (TListaGen*)malloc(sizeof(TListaGen));
    P->Tipo = CIR;
    P->Info = C;
    P->Prox = NULL;
    return P;

}

typedef TListaGen *PListaGen;

float RetArea(TRetangulo *R){
    return(R->b * R->h);
}

float TriArea(TTriangulo *T){
    return(T->b * T->h);
}

float CirArea(TCirculo *C){
    return(PI * C->r * C->r);
}

float area(TListaGen *P){
    float a;
    switch(P->Tipo){
        case RET:
            a = RetArea(P->Info);
        break;
        case TRI:
            a = TriArea(P->Info);
        break;
        case CIR:
            a = CirArea(P->Info);
        break;
    }
    return a;
}

PListaGen MaxArea(PListaGen L, float *maiorA){
    float AMax = 0.0;
    PListaGen P, Q;
    float a;
    Q = NULL;
    for(P = L; P != NULL; P = P->Prox){
        a = area(P);
        if(a > AMax){
            Q = P;
            AMax = a;
        }
    }
    *maiorA = AMax;
    return Q;
}

void Libera(PListaGen L){
    void *Q;
    PListaGen T;
    while(L != NULL){
        T = L->Prox;
        Q = L->Info;
        free(Q);
        free(L);
        L = T;
    }
}

int main(){
    int Opcao, Tipo;
    float a, b, maiorA;
    PListaGen Lista, P;
    Lista = NULL;
    do{
        printf("Escolha uma opção:\n");
        printf("1) Inserir um elemento na Lista\n");
        printf("2) Calcular a maior área\n");
        printf("3) Sair\n\n");
        printf("Opção: ");
        scanf("%d", &Opcao);
        switch(Opcao){
            case 1:
                do{
                    printf("\nDigite o tipo do objeto (1-Retângulo, 2-Triângulo, 3-Círculo): ");
                    scanf("%d",&Tipo);
                }while(Tipo > 3 || Tipo < 1);
                if(Tipo == 1){
                    printf("\nDigite a base e a altura do retângulo: ");
                    scanf("%f %f", &b, &a);
                    P = CriaRet(b, a);
                }
                else if(Tipo == 2){
                    printf("\nDigite a base e a altura do triângulo: ");
                    scanf("%f %f", &b, &a);
                    P = CriaTri(b, a);
                }
                else{
                    printf("\nDigite o raio do círculo: ");
                    scanf("%f", &b);
                    P = CriaCir(b);
                }
                //Insere o Nó Criado
                P->Prox = Lista;
                Lista = P;
            break;
            case 2:
                P = MaxArea(Lista, &maiorA);
                if(P->Tipo == RET){
                    TRetangulo *Q = P->Info;
                    printf("\nRetângulo de base: %5.2f e altura: %5.2f", Q->b, Q->h);
                }
                else if(P->Tipo == TRI){
                    TTriangulo *Q = P->Info;
                    printf("\nTriângulo de base: %5.2f e altura: %5.2f", Q->b, Q->h);
                }
                else{
                    TCirculo *Q = P->Info;
                    printf("\nCírculo de raio: %5.2f", Q->r);
                }
                printf("\nÁrea: %8.2f", maiorA);
            break;
            default:
                if(Opcao != 3){
                    printf("\nOpção Inválida\n");
                }
            break;
        }
    }while(Opcao != 3);
    Libera(Lista);
    return 0;
}