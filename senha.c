#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

#define MAX_LETRAS 5

void encontrarPalavra(char *palavra){
    FILE *palavras;
    palavras = fopen("palavras.txt", "r");

    srand(time(NULL));
    int randNumber = rand() % 1000;
    fseek(palavras, randNumber * (MAX_LETRAS + 2) * sizeof(char), SEEK_SET);

    fread(palavra, sizeof(char), 5, palavras);

    return;
}

int letraNaoChecada(char *checagem, char letra, int *qtd){
    for(int i = 0; i < MAX_LETRAS + 1; i++){
        if(letra == checagem[i]) return 0;
    }
    *qtd += 1;
    return 1;
}

bool exibirAcertos(char *gabarito, char *chute, int i){
    char acertos[5] = {0, 0, 0, 0, 0};
    int qtd = 0;

    for(int i = 0; i < 5; i++){
        if(gabarito[i] == chute[i]){
            printf("%c", gabarito[i]);
            acertos[qtd] = gabarito[i];
            qtd++;
        }
        else printf("*");
    }

    if(qtd == 5){
        printf("\n\n");
        return true;
    }

    printf(" - ");

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(chute[i] == gabarito[j] && letraNaoChecada(acertos, gabarito[j], &qtd)){
                printf("%c ", chute[i]);
                acertos[qtd] = gabarito[j];
            }
        }
    }

    if (i == 5){
        printf("\n\n");
        return false;
    }

    printf("\n%d\n", i + 2);
}

int main(void){
    char palavra[6];
    encontrarPalavra(palavra);
    printf("1\n");
    
    bool ganhou = false;

    for(int i = 0; i < 6 && ganhou == false; i++){
        char entrada[6];
        fgets(entrada, 6, stdin);
        while(getchar() != '\n');
        ganhou = exibirAcertos(palavra, entrada, i);
    }

    if (ganhou == false){
        printf("%s", palavra);
    }
    

    return 0;
}