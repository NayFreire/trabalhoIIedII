#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>

typedef struct no{
	char palavra[50];
	int qtd;
	struct no *esq;
	struct no *dir;
}TNo;

struct timeval comeco, final;

void inicializa(TNo **ptr){
	*ptr = NULL;
}

char* letraMinuscula(char *palavra, int tamanho){
	int i, j;
	char *aux = malloc(tamanho);

	if(strchr(palavra, '.') != NULL || 
		strchr(palavra, ',') != NULL || 
		strchr(palavra, '!') != NULL || 
		strchr(palavra, '?') != NULL ||
		strchr(palavra, ':') != NULL ||
		strchr(palavra, ';') != NULL ||
		strchr(palavra, '%') != NULL ||
		strchr(palavra, '&') != NULL ||
		strchr(palavra, '*') != NULL ||
		strchr(palavra, '$') != NULL ||
		strchr(palavra, '#') != NULL ||
		strchr(palavra, '@') != NULL){
		
		for(i=0; i<tamanho-1; i++){
			aux[i] = tolower(palavra[i]);
		}
		
		printf("%s\n", aux);
		return aux;
	}
	else{
		for(i=0;i<tamanho;i++){
			palavra[i] = tolower(palavra[i]);
		}
		return palavra;
	}
}

void insere(TNo **ptr, char palavra[]){
	int inserida = contQtdRepeticao(*ptr, palavra);
	int i, j;
	
	if(inserida == 0){
		if(*ptr == NULL){
			(*ptr) = (TNo *) malloc(sizeof(TNo));
			(*ptr)->esq = NULL;
			(*ptr)->dir = NULL;
			strcpy((*ptr)->palavra, palavra);
			(*ptr)->qtd = 1;
		}
		else{
			if(strcmp(palavra, (*ptr)->palavra) < 0){
				insere(&(*ptr)->esq, palavra);
			}
			else if(strcmp(palavra, (*ptr)->palavra) > 0){
				insere(&(*ptr)->dir, palavra);
			}
			else{
				printf("igual");
			}		
		}
	}
}

int qtdP = 0;
int repeticoes = 0;

void contPalavra(){
	qtdP++;
}

int naoRepetidas = 0;

int i = 0;

void insereVetor(TNo *ptr, char **vetor){
	if(ptr != NULL){
		char *word = malloc(naoRepetidas * sizeof(char));
		strcpy(word, ptr->palavra);
		insereVetor(ptr->esq, vetor);
		*(vetor+i) = word;
		free(word);
		i++;
		insereVetor(ptr->dir, vetor);
	}
}

void inOrdem(TNo *ptr){
	if(ptr != NULL){
		inOrdem(ptr->esq);
		printf("\n***********************\n");
		printf("palavra: %s\n", ptr->palavra);
		printf("qtd: %d\n", ptr->qtd);
		inOrdem(ptr->dir);
	}
	contPalavra();
}

void pesquisaBinaria(char **vetor, char chave){
	int direita = naoRepetidas - 1;
	int esquerda = 0;
	int encontrado = 0;
	int meio;
	printf("D: %d", direita);
	while(esquerda <= direita && !encontrado){
		meio = (esquerda + direita)/2;
		if(strcmp((*vetor+meio), chave) == 0){
			printf("Encontrado");
		}
		else if(chave < (*vetor+meio)){
			direita = meio - 1;
		}
		else{
			esquerda = meio + 1;
		}
	}
}

int contQtdRepeticao(TNo *ptr, char palavra[]){
	if(ptr != NULL){
		if(strcmp(palavra, ptr->palavra) > 0){
			contQtdRepeticao(ptr->dir, palavra);
		}
		else if(strcmp(palavra, ptr->palavra) < 0){
			contQtdRepeticao(ptr->esq, palavra);
		}
		else if(strcmp(palavra, ptr->palavra) == 0){
			repeticoes++;
			ptr->qtd++;
			return 1;
		}
	}
	return 0;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	TNo *ponteiro, *auxPonteiro;
    FILE *arq;
    char word[10];
    
    arq = fopen("exemplo.txt", "r");
    int i=0, j = 0, qtdPalavras=0;
    
    inicializa(&ponteiro);

    if(arq == NULL){
        printf("Can't open file for reading.\n");    	
	}
    else{
        while (fscanf(arq, "%s", word) != EOF)
        {
            qtdPalavras++;
            char *palavraCorrigida = letraMinuscula(word, strlen(word));
            insere(&ponteiro, palavraCorrigida);
        }
        fclose(arq);
    }

    naoRepetidas = qtdPalavras - repeticoes;
    printf("qtd: %d", naoRepetidas);
    auxPonteiro = ponteiro;
	inOrdem(ponteiro); 
    printf("\n\nQTDP: %d", qtdP);
    printf("\n\nRepeticoes: %d\n\n", repeticoes);
    
    char* vetor;
	vetor = calloc(naoRepetidas, sizeof(char));
    
    insereVetor(ponteiro, &vetor);
    
	char *buscada = malloc(10);
	
	printf("Palavra buscada: ");
	gets(buscada);  
	
    gettimeofday(&comeco, NULL);
    pesquisaBinaria(&vetor, buscada);
    gettimeofday(&final, NULL);
    
    printf("Tempo de processamento do vetor: %ld microsegundos\n\n", ((final.tv_sec - comeco.tv_sec)*1000000L+final.tv_usec) - comeco.tv_usec);	
    return 0;
    
}
