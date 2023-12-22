#include <stdio.h>
#include <locale.h>

struct Data{
    int Dia, Mes, Ano;
};

struct Banda{
    char Nome[50];
    struct Data Data_Lancamento;
    struct Data Data_Contratacao;
    float Valor;
    int Membros;
    char Produtora[30];
};

int main(){
    setlocale(LC_ALL, "Portuguese_Brazil");
    printf("Exemplo - AED1, Slide 2\n");
    int i;
    struct Banda Bandas[10];
    for(i = 0; i < 10; i++){
        printf("\nMembros (Quantidade): ");
        scanf("%d", &Bandas[i].Membros);
        printf("\nValor: ");
        scanf("%f", &Bandas[i].Valor);
        printf("\nNome: ");
        scanf("%s", &Bandas[i].Nome);
        printf("\nProdutora: ");
        scanf("%s", &Bandas[i].Produtora);
        printf("\nDia de Lançamento: ");
        scanf("%d", &Bandas[i].Data_Lancamento.Dia);
        printf("\nMês de Lançamento: ");
        scanf("%d", &Bandas[i].Data_Lancamento.Mes);
        printf("\nAno de Lançamento: ");
        scanf("%d", &Bandas[i].Data_Lancamento.Ano);
        printf("\nDia de Contratação: ");
        scanf("%d", &Bandas[i].Data_Contratacao.Dia);
        printf("\nMês de Contratação: ");
        scanf("%d", &Bandas[i].Data_Contratacao.Mes);
        printf("\nAno de Contratação: ");
        scanf("%d", &Bandas[i].Data_Contratacao.Ano);
    }
}