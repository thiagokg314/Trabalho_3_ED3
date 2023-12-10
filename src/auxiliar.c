#include "../headers/auxiliar.h"

// Função para ler um número inteiro de um arquivo CSV.
int retornaNum(FILE *arquivoCSV) {
	char *buffer = retornaString(arquivoCSV);
	int num = atoi(buffer);
	if (num == 0) {
		if (strcmp("0", buffer) != 0) {
			free(buffer);
			return -1;  // Retorna -1 para indicar que o número é nulo.
		}
	}
	free(buffer);
	return num;
}

// Função para ler uma string de um arquivo CSV.
char *retornaString(FILE *arquivoCSV) {
	char *buffer;
	buffer = malloc(50 * sizeof(char));
	int i = 0;
	char c;
	while ((c = fgetc(arquivoCSV)) != EOF) {
		if (c == ',' || c == '\n') {
			buffer[i] = '\0';  // Adiciona o caractere nulo para terminar a string.
			break;
		} else {
			buffer[i++] = (char) c;
		}
	}
	return buffer;
}

// Função para imprimir um número inteiro ou "NULO" se for -1.
void imprimeNum(int inteiro)
{
	printf("%d", inteiro);
}

// Função para imprimir uma string variável ou "NULO" se for vazia.
void imprimeString(StringVariavel string)
{
	if (string.tamanho == 0)
	{
		printf("NULO");
	}
	else
	{
		printf("%s", string.string);
	}
}
