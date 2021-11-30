#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct no{
	char palavra[50];
	int qtd;
	struct no *esq;
	struct no *dir;
}TNo;

void inicializa(TNo **ptr){
	*ptr = NULL;
}

void pegaPalavras(char *palavra, int tamanho){
	printf("%s %d\n", palavra, tamanho);
}

char letraMinuscula(char palavra){
	
}

void insere(TNo **ptr, char palavra[]){
	//printf("%s %d\n", palavra, sizeof(palavra));
	int i, j;
	if(*ptr == NULL){
		(*ptr) = (TNo *) malloc(sizeof(TNo));
		(*ptr)->esq = NULL;
		(*ptr)->dir = NULL;
		strcpy((*ptr)->palavra, tolower(palavra));
		(*ptr)->qtd = 1;
		//printf("primeiro no: %s", (*ptr)->palavra);
	}
	else{
		if(strcmp(palavra, (*ptr)->palavra) < 0){
			//printf("%s - %s", palavra, (*ptr)->palavra);
			insere(&(*ptr)->esq, palavra);
		}
		else if(strcmp(palavra, (*ptr)->palavra) > 0){
			//printf("%s - %s", palavra, (*ptr)->palavra);
			insere(&(*ptr)->dir, palavra);
		}
		else{
			printf("igual");
		}		
	}
}


void inOrdem(TNo *ptr){
	if(ptr != NULL){
		inOrdem(ptr->esq);
		printf("palavra: %s\n", ptr->palavra);
		inOrdem(ptr->dir);
	}
}

/*void contQtdRepeticao(TNo *ptr, char palavra){
	TNo *aux;
	while((ptr != NULL) && (ptr->palavra != palavra)){
		aux = ptr;
		if(strcmp(palavra, (*ptr)->palavra) > 0){
			ptr = ptr->dir;
		}
		else{
			ptr = ptr->esq;
		}
	}
	if(ptr == NULL){
		printf("Não foi encontrada a chave");
	}
	else {
		printf("Achave esta na arvore");
	}
}*/

main(){
	TNo *ponteiro;
    FILE *arq;
    char word[50];
    arq = fopen("texto.txt", "r");
    int i=0, qtdPalavras=0;
    
    inicializa(&ponteiro);

    if(arq == NULL){
        printf("Can't open file for reading.\n");    	
	}
    else{
        while (fscanf(arq, "%s", word) != EOF)
        {
           	//printf("%s\n", word);
            qtdPalavras++;
            insere(&ponteiro, word);
        }
        fclose(arq);
    }
    printf("qtd: %d", qtdPalavras);
    
    inOrdem(ponteiro);
    
    return 0;
}
