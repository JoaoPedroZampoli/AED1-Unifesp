#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lista{
    char Dado;
    int Contador;
    struct Lista* Anterior;
    struct Lista* Proximo;
} TLista;

typedef TLista* PLista;

PLista Novo(char Dado){
    PLista Novo =(PLista)malloc(sizeof(TLista));
    Novo->Dado = Dado;
    Novo->Contador = 1;
    Novo->Proximo = NULL;
    Novo->Anterior = NULL;
    return Novo;
}

PLista InserirNoFinal(PLista* L, char Dado){
    PLista Nova = Novo(Dado);
    if(*L == NULL){
        *L = Nova;
    }
    else{
        PLista Ultimo = *L;
        while(Ultimo->Proximo != NULL){
            Ultimo = Ultimo->Proximo;
        }
        Ultimo->Proximo = Nova;
        Nova->Anterior = Ultimo;
    }
    return Nova;
}

void RemoverRuido(PLista *L){
    PLista Temporario = *L;
    while(Temporario != NULL){
        if(Temporario->Contador == 1){
            PLista ProximoTemporario = Temporario->Proximo;
            PLista AnteriorTemporario = Temporario->Anterior;

            if(AnteriorTemporario && ProximoTemporario && AnteriorTemporario->Contador >= 2 && ProximoTemporario->Contador >= 2){
                if(AnteriorTemporario->Contador >= ProximoTemporario->Contador){
                    AnteriorTemporario->Contador += 1;
                } else{
                    ProximoTemporario->Contador += 1;
                }
                if(AnteriorTemporario){
                    AnteriorTemporario->Proximo = ProximoTemporario;
                }
                if(ProximoTemporario){
                    ProximoTemporario->Anterior = AnteriorTemporario;
                }
            } else if(AnteriorTemporario && AnteriorTemporario->Contador >= 2){
                AnteriorTemporario->Contador += 1;
                AnteriorTemporario->Proximo = NULL;
            } else if(ProximoTemporario && ProximoTemporario->Contador >= 2){
                ProximoTemporario->Contador += 1;
                ProximoTemporario->Anterior = NULL;
                *L = ProximoTemporario;
            } else{
                Temporario = Temporario->Proximo;
                continue;
            }

            free(Temporario);
            Temporario = ProximoTemporario;
        }else{
            Temporario = Temporario->Proximo;
        }
    }
}

void LiberarMemoria(PLista *L){
    PLista Temporario;

    while(*L != NULL){
        Temporario = (*L)->Proximo; 
        free(*L); 
        *L = Temporario; 
    }
}

int ContarCaracteres(PLista L){
    int Total = 0;
    while(L != NULL){
        Total++;
        int contador = L->Contador;
        while(contador != 0){
            contador /= 10;
            Total++;
        }
        L = L->Proximo;
    }
    return Total;
}

void Imprimir(PLista L){
    while(L != NULL){
        printf("%d%c", L->Contador, L->Dado);
        L = L->Proximo;
    }
    printf("\n");
}

int main(){
    char String[1024];
    fgets(String, sizeof(String), stdin);

    String[strcspn(String, "\n")] = '\0';

    PLista Lista = Novo(String[0]);
    PLista Ultimo = Lista;

    for(int i = 1; i < strlen(String); i++){
        if(String[i] == String[i - 1]){
            Ultimo->Contador++;
        } else{
            Ultimo = InserirNoFinal(&Lista, String[i]);
        }
    }
    
    printf("%d\n", ContarCaracteres(Lista));
    
    Imprimir(Lista);
    
    RemoverRuido(&Lista);
    
    printf("%d\n", ContarCaracteres(Lista));
    
    Imprimir(Lista);

	LiberarMemoria(&Lista);

	return 0; 
}
