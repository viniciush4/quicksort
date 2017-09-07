#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Assinaturas
void preencherVetorAleatoriamente(int *vetor, int n);
void imprimir(int *vetor, int n);
void permutar(int *vetor, int i, int j);
void quicksort(int *A, int p, int r);
int particionar(int *A, int p, int r);
int particionarUsandoPivoAleatorio(int *A, int p, int r);

// Contadores e semente
unsigned long comparacoes = 0;
unsigned long trocas = 0;
int semente = 0;

// Função principal
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
	
	// Vetor a ser ordenado
	int vetor[n];
	
	// Abre arquivo output
	FILE* arq; 
	arq = fopen("output.txt","w");
	
	// Fazer de n até s, incrementando n em a unidades
	for(n;n<=s;n=n+a)
	{
		// Escreve o titulo da linha (tamanho)
		fprintf(arq,"%d:", n);
	
		// Gera instancia de semente	
		semente = time(NULL) % 428;
	
		// Repete m vezes
		for(int i=0;i<m;i++)
		{	
			// Zera os contadores
			trocas=0;
			comparacoes=0;
		
			// Vetor a ser ordenado
			int vetor[n];
	
			// Preenche vetor com numeros aleatorios
			preencherVetorAleatoriamente(vetor, n);

			// Ordena o vetor
			quicksort(vetor, 0, n-1);
			
			// Salva a quantidade de comparacoes
			fprintf(arq,"%ld,", comparacoes);
		}
		
		// Quebra de linha
		fprintf(arq,"\n");
	}
	
	// Fecha arquivo output
	fclose (arq);
	
	// Retorna com sucesso
	return(EXIT_SUCCESS);
}

// Preenche um vetor dado com numeros int na faixa [0..n]
void preencherVetorAleatoriamente(int *vetor, int n)
{	
	// Atualiza a semente
	semente = semente+43;
	srand(semente);
	
	// Preenche vetor
	for(int i=0;i<n;i++)
		vetor[i] = rand() % n;
}

// Imprime na tela um vetor de tam n
void imprimir(int *vetor, int n)
{
	// Imprime cada elemento
	for(int i=0;i<n;i++)
		printf("%d\n",vetor[i]);
	printf("\n");
}

// Permuta os elementos de indice i e j num vetor dado
void permutar(int *vetor, int i, int j)
{
	// Permuta dois elementos
	int x = vetor[i];
	vetor[i] = vetor[j];
	vetor[j] = x;
	
	// Incrementa trocas
	trocas++;
}

// Ordena um vetor de indice inicial p e final r
void quicksort(int *A, int p, int r)
{
	if(p<=r)
	{
		int q = particionarUsandoPivoAleatorio(A, p, r);
		quicksort(A, p, q-1);
		quicksort(A, q+1, r);
	}
}

// Particiona um vetor considerando o ultimo elemento pivô
int particionar(int *A, int p, int r)
{
	int pivo = A[r];
	int i = p-1;
	
	for(int j=p; j<=r-1; j++)
	{
		if(A[j] <= pivo)
		{
			// Incrementa comparacoes
			comparacoes++;
			
			i=i+1;
			permutar(A, i, j);
		}
	}
	permutar(A, i+1, r);
	return i+1;
}

// escolhe um pivô aleatório para evitar o pior caso do quicksort
int particionarUsandoPivoAleatorio(int *A, int p, int r)
{
	// Atualiza a semente
	semente = semente+43;
	srand(semente);
	
	// seleciona um número entre r (inclusive) e p (inclusive)
	int pivo_indice = (rand() % (r - p + 1)) + p;
	
	// faz a troca para colocar o pivô no r
	permutar(A, pivo_indice, r);
	
	// chama a particionar
	return particionar(A, p, r);
}

