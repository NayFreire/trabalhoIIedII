#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h> 
#include <locale.h>

typedef struct no{
	char palavra[50];
	int qtd;
	struct no *esq;
	struct no *dir;
}TNo;

typedef struct p{
	char palavra[20];
}Palavra;

void inicializa(TNo **ptr){
	*ptr = NULL;
}

void pegaPalavras(char *palavra, int tamanho){
	printf("%s %d\n", palavra, tamanho);
}

char* letraMinuscula(char *palavra, int tamanho){
	int i, j;
	char *aux = malloc(tamanho-1);

	if(strchr(palavra, '.') != NULL || 
		strchr(palavra, ',') != NULL || 
		strchr(palavra, '!') != NULL || 
		strchr(palavra, '?') != NULL ||
		strchr(palavra, ':') != NULL ||
		strchr(palavra, ';') != NULL
		/*strchr(palavra, '%') != NULL ||
		strchr(palavra, '&') != NULL ||
		strchr(palavra, '*') != NULL ||
		strchr(palavra, '$') != NULL ||
		strchr(palavra, '#') != NULL ||
		strchr(palavra, '@') != NULL*/){
		//printf("%s\n", palavra);
		
		for(i=0; i<tamanho-1; i++){
			aux[i] = tolower(palavra[i]);
			//tamanho--;
			
			//printf("[%d] [%d]= %c\n", i, tamanho-2, aux[i]);
		}
		
		printf("%s\n", aux);
		return aux;
	}
	else{
		for(i=0;i<tamanho;i++){
			palavra[i] = tolower(palavra[i]);
			//printf("[%d] [%d]= %c\n", i, tamanho-1, palavra[i]);
		}
		printf("%s*\n", palavra);
		return palavra;
	}
}

void insere(TNo **ptr, char palavra[]){
	//printf("%s %d\n", palavra, sizeof(palavra));
	int inserida = contQtdRepeticao(*ptr, palavra);
	//printf("%s inserida??? %d\n", palavra, inserida);
	int i, j;
	
	if(inserida == 0){
		if(*ptr == NULL){
			(*ptr) = (TNo *) malloc(sizeof(TNo));
			(*ptr)->esq = NULL;
			(*ptr)->dir = NULL;
			strcpy((*ptr)->palavra, palavra);
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
}

int qtdP = 0;
int repeticoes = 0;

void contPalavra(){
	qtdP++;
}

int naoRepetidas = 0;
//char *vetor = (char*) malloc(1000*sizeof(char));

/*void insereVetor(TNo *ptr, Palavra **vetor){
	Palavra *aux = malloc(sizeof(Palavra));
	aux->palavra = ptr->palavra;
	/*printf("entrou no insere vetor");
	mat = malloc(naoRepetidas * 10 * sizeof(char*));
	int i, j;
	
	percorrePonteiro(ptr, *mat);
	
    for(i=0;i<naoRepetidas;i++){
    	for(j=0;j<10;j++){
    		printf("{%s [%d][%d]}\n", *mat, i, j);
		}
	}
	printf("%s", aux->palavra);
	printf("entrou no percorre ponteiro");
	int i, j;
	if(ptr != NULL){
		insereVetor(ptr->esq, vetor);
			*vetor->palavra = ptr->palavra;
			printf("###### %s\n", vetor->palavra);
		insereVetor(ptr->dir, vetor);
	}
}*/

void percorrePonteiro(TNo *ptr, char *mat){
	printf("entrou no percorre ponteiro");
	int i, j;
	if(ptr != NULL){
		percorrePonteiro(ptr->esq, mat);
		for(i=0;i<naoRepetidas;i++){
			for(j=0;j<10;j++){
				mat = ptr->palavra;
				//printf("###### %s\n", mat);
			}
		}
		percorrePonteiro(ptr->dir, mat);
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

/*TODO: Pesquisa binária e árvores binárias*/
void pesquisaBinaria(char palavra, int tamanho){
	int direita = tamanho - 1;
	int esquerda = 0;
	int encontrado = 0;
	int meio;
	
	while(esquerda <= direita && !encontrado){
		meio = (esquerda + direita)/2;
		//if()
	}
}

void ABPesquisa(){
	
}

void ABPBalanceamento(){
	
}
void contQtdRepeticao(TNo *ptr, char palavra[]){
	if(ptr != NULL){
		if(strcmp(palavra, ptr->palavra) > 0){
			contQtdRepeticao(ptr->dir, palavra);
			//contPalavra();
		}
		else if(strcmp(palavra, ptr->palavra) < 0){
			contQtdRepeticao(ptr->esq, palavra);
			//contPalavra();
		}
		else if(strcmp(palavra, ptr->palavra) == 0){
			repeticoes++;
			ptr->qtd++;
			return 1;
		}
	}
	return 0;
}

main(){
	setlocale(LC_ALL, "Portuguese");
	TNo *ponteiro;
    FILE *arq;
    char word[50];
    //char palavraCorrigida[50];
    arq = fopen("cont.txt", "r");
    int i=0, j = 0, qtdPalavras=0;
    
    inicializa(&ponteiro);

    if(arq == NULL){
        printf("Can't open file for reading.\n");    	
	}
    else{
        while (fscanf(arq, "%s", word) != EOF)
        {
           	//printf("%s\n", word);
            qtdPalavras++;
            char *palavraCorrigida = letraMinuscula(word, strlen(word));
            //printf("%s@", palavraCorrigida);
            insere(&ponteiro, palavraCorrigida);
            //free(palavraCorrigida);
        }
        fclose(arq);
    }
    naoRepetidas = qtdPalavras - repeticoes;
    printf("qtd: %d", naoRepetidas);
    
	inOrdem(ponteiro);
    printf("QTDP: %d", qtdP);
    printf("Repeticoes: %d", repeticoes);
    
	Palavra **vetor;
	vetor = malloc(naoRepetidas*sizeof(Palavra));
    
    //insereVetor(ponteiro, &vetor);
    
    return 0;
}
