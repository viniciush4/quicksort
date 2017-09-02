#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void preencherVetorAleatoriamente(int *vetor, int n);
void imprimir(int *vetor, int n);
void permutar(int *vetor, int i, int j);
void quickrandom(int *vetor, int esquerda, int direita);

unsigned long comparacoes = 0;
int semente = 0;

int main (int argc, char *argv[])
{
	// Tamanho do problema
	int n = atoi(argv[1]);
	
	// Acrescimo no tamanho do problema
	int a = atoi(argv[2]);
	
	// Parada do programa (em tamanho do problema)
	int s = atoi(argv[3]);
		
	// Quantidade de repeticoes do mesmo tamanho
	int m = atoi(argv[4]);
	
	// Abre arquivo output
	FILE* arq; 
	arq = fopen("output.csv","w");
	
	// Fazer de n até s
	for(n;n<=s;n+a)
	{
		// Escreve o titulo da linha
		fprintf(arq,"%d, ", n);
	
		// Gera instancia de semente	
		semente = time(NULL) % 428;
	
		// Repete m vezes
		for(int i=0;i<m;i++)
		{	
			// Zera o contador
			comparacoes=0;
		
			// Vetor a ser ordenado
			int vetor[n];
	
			// Preenche vetor com numeros aleatorios
			preencherVetorAleatoriamente(vetor, n);

			// Ordena o vetor
			quickrandom(vetor, 0, n-1);
	
			// Salva a quantidade de comparacoes
			fprintf(arq,"%ld, ", comparacoes);
		}
		
		// Quebra de linha
		fprintf(arq,"/n");
	}
	
	// Fecha arquivo output
	fclose (arq);
	
	// Retorna com sucesso
	return(EXIT_SUCCESS);
}

void preencherVetorAleatoriamente(int *vetor, int n)
{	
	// Atualiza a semente
	semente = semente+43;
	srand(semente);
	
	// Preenche vetor
	for(int i=0;i<n;i++)
		vetor[i] = rand() % n;
}

void imprimir(int *vetor, int n)
{
	// Imprime cada elemento
	for(int i=0;i<n;i++)
		printf("%d\n",vetor[i]);
	printf("\n");
}

void permutar(int *vetor, int i, int j)
{
	// Permuta dois elementos
	int x = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = x;
	
	// Incrementa comparacoes
	comparacoes++;
}

void quickrandom(int *vetor, int esquerda, int direita)
{
	int i, j, pivo;
	semente = semente+37;
	srand(semente);
    
	i = esquerda;
	j = direita;
	pivo = vetor[rand() % (direita - esquerda + 1) + esquerda];
	
	while(i <= j)
	{
		while(vetor[i] < pivo && i < direita)
		{
			i++;
		}
		while(vetor[j] > pivo && j > esquerda)
		{
			j--;
		}
		if(i <= j)
		{
			permutar(vetor, i, j);
			i++;
			j--;
		}
	}
	if(j > esquerda)
	{
		quickrandom(vetor, esquerda, j);
	}
	if(i < direita)
	{
		quickrandom(vetor,  i, direita);
	}
}
