#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_LETRAS 5

void encontrarPalavra(char *palavra){
    FILE *palavras;
    palavras = fopen("palavras.txt", "r");

    srand(time(NULL));
    int randNumber = rand() % 1000;
    fseek(palavras, randNumber * 7 * sizeof(char), SEEK_SET);

    fread(palavra, sizeof(char) * 5, 1, palavras);

    return;
}

int letraNaoChecada(char *checagem, char letra, int *qtd){
    for(int i = 0; i < MAX_LETRAS + 1; i++){
        if(letra == checagem[i]) return 0;
    }
    *qtd += 1;
    return 1;
}

void exibirAcertos(char *gabarito, char *chute){
    for(int i = 0; i < 5; i++){
        if(gabarito[i] == chute[i]){
            printf("%c", gabarito[i]);
        }
        else printf("*");
    }

    printf(" - ");

    char acertos[5] = {0, 0, 0, 0, 0};
    int qtd = 0;

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(chute[j] == gabarito[i] && letraNaoChecada(acertos, gabarito[i], &qtd)){
                printf("%c ", gabarito[i]);
                acertos[qtd] = gabarito[i];
            }
        }
    }

    printf("\n");
}

int main(void){
    char palavra[6];
    encontrarPalavra(palavra);

    for(int i = 0; i < 6; i++){
        char entrada[6];
        fgets(entrada, 6, stdin);
        while(getchar() != '\n');
        exibirAcertos(palavra, entrada);
    }

    printf("%s", palavra);

    return 0;
}