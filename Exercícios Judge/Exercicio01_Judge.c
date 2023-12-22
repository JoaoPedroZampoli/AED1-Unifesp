#include <stdio.h>
#include <locale.h>
#include <string.h>

struct Contagem{
    char Letra;
    int Ocorrencias;
};

void Contador(char[]);

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    char String[256];
    //Comentado pra ficar como deve aparecer no Judge
    //printf("Exercício 01 - Contagem de Letras em Strings\n");
    fgets(String, sizeof(String),stdin);
    //printf("\nA Ocorrência das Letras é de:\n");
    Contador(String);
}

void Contador(char String[]){
    struct Contagem Valores[26];
    int counter = 0;
    for(int i = 0; i < 26; i++){
        Valores[i].Letra = 'A' + i;
        Valores[i].Ocorrencias = 0;
    }
    for(int i = 0; i < strlen(String); i++){
        if(String[i]>='a' && String[i]<='z'){
            String[i] = String[i] - 32;
            Valores[String[i] - 'A'].Ocorrencias++;
        }
        else{
            if(String[i]>='A' && String[i]<='Z'){
                Valores[String[i] - 'A'].Ocorrencias++;
            }
            else{
                if(String[i] == '\0'){
                    break;
                }
            }
        }
    }
    for(int i = 0; i < 26; i++){
        if(Valores[i].Ocorrencias != 0){
            //printf("%c - %i\n", Valores[i].Letra, Valores[i].Ocorrencias);
            printf("%c %i\n", Valores[i].Letra, Valores[i].Ocorrencias);
        }
    }
}