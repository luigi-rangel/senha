#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>

#define NUM_PALAVRAS 2008
#define MAX_LETRAS 5

void encontrarPalavra(char *palavra){
    FILE *palavras;
    palavras = fopen("palavras.txt", "r");

    srand(time(NULL));
    int randNumber = rand() % NUM_PALAVRAS;
    fseek(palavras, randNumber * (MAX_LETRAS + 2) * sizeof(char), SEEK_SET);

    fread(palavra, sizeof(char), 5, palavras);

    return;
}

void printVerde(char string){
    printf("\033[0;32m%c\033[0m", string);
}

void printAmarelo(char string){
    printf("\033[0;33m%c\033[0m", string);
}

bool exibirAcertos(char *gabarito, char *chute, int k){
    int acertos = 0;
    
    for(int i = 0; i < 5; i++){
        bool correto = false;
        char gabaritoCopia[6];
        strcpy(gabaritoCopia, gabarito);
        for(int j = 0; j < 5; j++){
            if(chute[i] == gabaritoCopia[j]){
                correto = true;
                if(chute[i] == gabaritoCopia[i]){
                    gabaritoCopia[i] = '\0';
                    printVerde(chute[i]);
                    acertos++;
                }
                else{
                    printAmarelo(chute[i]);
                }
                break;
            }
        }
        if(!correto){
            printf("%c", chute[i]);
        }
    }

    if(acertos == 5) return true;

    printf("\n\n%d\n", k + 2);
    return false;
}

int main(void){
    char palavra[6];
    encontrarPalavra(palavra);
    printf("1\n");
    
    bool ganhou = false;

    for(int k = 0; k < 6 && ganhou == false; k++){
        char entrada[6];
        fgets(entrada, 6, stdin);
        while(getchar() != '\n');
        ganhou = exibirAcertos(palavra, entrada, k);
    }

    if (ganhou == false){
        printf("%s", palavra);
    }

    return 0;
}