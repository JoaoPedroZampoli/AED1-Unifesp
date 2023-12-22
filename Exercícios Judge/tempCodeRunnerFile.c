//João Pedro da Silva Zampoli - RA: 168.880 - AED 1 I
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
 
typedef struct Arvore{
    float Info;
    char Tipo;
    struct Arvore *Esquerda;
    struct Arvore *Direita;
}TArv;
typedef TArv *PArv;
 
PArv Inserir(PArv Arvore, float Area, char Tipo){
    PArv Novo;
    if(Arvore == NULL){
        Novo = (PArv)malloc(sizeof(TArv));
        Novo->Tipo = Tipo;
        Novo->Info = Area;
        Novo->Esquerda = NULL;
        Novo->Direita = NULL;
        return Novo;
    }
    else{
        if(Area < Arvore->Info){
            Arvore->Esquerda = Inserir(Arvore->Esquerda, Area, Tipo);
        }
        else{
            if(Area > Arvore->Info){
                Arvore->Direita = Inserir(Arvore->Direita, Area, Tipo);
            }
        }
    }
    return Arvore;
}
 
int Pesquisar(PArv Arvore, float Area){
    int Info = Arvore->Info+0.5;
    int AreaConvertida = Area+0.5;
    if (Arvore == NULL) {
        return 0;
    }
    if (AreaConvertida < Info) {
        return Pesquisar(Arvore->Esquerda, Area);
    } else if (AreaConvertida > Info) {
        return Pesquisar(Arvore->Direita, Area);
    } else {
        return 1;
    }
}
 
int BuscarTipo(PArv Arvore, char TipoObjeto){
    if(Arvore == NULL){
        return 0;
    }
    if (Arvore->Tipo == TipoObjeto || toupper(Arvore->Tipo) == toupper(TipoObjeto)){
        return 1;
    }
    return BuscarTipo(Arvore->Esquerda, TipoObjeto) || BuscarTipo(Arvore->Direita, TipoObjeto);
}
 
 
 
void ImprimirCirculos(PArv Arvore) {
    if(Arvore != NULL){
        ImprimirCirculos(Arvore->Esquerda);
        if(Arvore->Tipo == 'C'){
            printf("%.1f ", Arvore->Info);
        }
        ImprimirCirculos(Arvore->Direita);
    }
}
 
void ImprimirRetangulos(PArv Arvore){
    if(Arvore != NULL){
        ImprimirRetangulos(Arvore->Esquerda);
        if(Arvore->Tipo == 'R'){
            printf("%.1f ", Arvore->Info);
        }
        ImprimirRetangulos(Arvore->Direita);
    }
}
 
void ImprimirTriangulos(PArv Arvore){
    if(Arvore != NULL){
        ImprimirTriangulos(Arvore->Esquerda);
        if(Arvore->Tipo == 'T'){
            printf("%.1f ", Arvore->Info);
        }
        ImprimirTriangulos(Arvore->Direita);
    }
}
 
PArv ValorMinimo(PArv Arvore){
    PArv Atual = Arvore;
    while(Atual && Atual->Esquerda != NULL){
        Atual = Atual->Esquerda;
    }
    return Atual;
}
 
void ImprimirObjetos(PArv Arvore){
    if(BuscarTipo(Arvore, 'C') == 1){
        printf("\ncirculo\n");
        ImprimirCirculos(Arvore);
    }
    if(BuscarTipo(Arvore, 'R') == 1){
        printf("\nretangulo\n");
        ImprimirRetangulos(Arvore);
    }
    if(BuscarTipo(Arvore, 'T') == 1){
        printf("\ntriangulo\n");
        ImprimirTriangulos(Arvore);
    }
}

PArv RemoverObjetos(PArv Arvore, float LimiteArea, char TipoObjeto){
    if(Arvore == NULL){
        return NULL;
    }

    Arvore->Esquerda = RemoverObjetos(Arvore->Esquerda, LimiteArea, TipoObjeto);
    Arvore->Direita = RemoverObjetos(Arvore->Direita, LimiteArea, TipoObjeto);

    if((toupper(Arvore->Tipo) == toupper(TipoObjeto)) && (Arvore->Info < LimiteArea)){
        if(Arvore->Esquerda == NULL){
            PArv Temporaria = Arvore->Direita;
            free(Arvore);
            return Temporaria;
        }else if (Arvore->Direita == NULL){
            PArv Temporaria = Arvore->Esquerda;
            free(Arvore);
            return Temporaria;
        }else{
            PArv Temporaria = ValorMinimo(Arvore->Direita);
            Arvore->Info = Temporaria->Info;
            Arvore->Tipo = Temporaria->Tipo;
            Arvore->Direita = RemoverObjetos(Arvore->Direita, LimiteArea, TipoObjeto);
        }
    }

    return Arvore;
}
 
int main(){
    //setlocale(LC_ALL, "Portuguese_Brazil");
    char Opcao, TipoObjeto;
    float Base, Altura, Raio, Area;
    PArv Objetos = NULL;
 
    do{
        //printf("Tipo de Objeto: ");
        scanf(" %c", &Opcao);
        Opcao = toupper(Opcao);
        switch(Opcao){
            case 'R':
                scanf("%f %f", &Base, &Altura);
                Area = Base*Altura;
                if(Pesquisar(Objetos, Area) == 0){
                    Objetos = Inserir(Objetos, Area, Opcao);
                }
            break;
            case 'T':
                scanf("%f %f", &Base, &Altura);
                Area = (Base*Altura)/2;
                if(Pesquisar(Objetos, Area) == 0){
                    Objetos = Inserir(Objetos, Area, Opcao);
                }
            break;
            case 'C':
                scanf("%f", &Raio);
                Area = (Raio*Raio)*M_PI;
                if(Pesquisar(Objetos, Area) == 0){
                    Objetos = Inserir(Objetos, Area, Opcao);
                }
            break;
            case 'I':   
                ImprimirObjetos(Objetos);
            break;
            case 'E':
                scanf(" %c %f", &TipoObjeto, &Area);
                Objetos = RemoverObjetos(Objetos, Area, TipoObjeto);
            break;
        }
    }while(Opcao != 'F');
}