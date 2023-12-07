#include "../headers/registro.h"

// Função para ler um registro de um arquivo BIN e preencher uma estrutura de Registro.
void lerRegistroBIN(FILE *arquivoBIN, Registro *registro)
{
	// Lê os campos do registro do arquivo BIN.
	fread(&registro->removido, sizeof(char), 1, arquivoBIN);
	fread(&registro->grupo, sizeof(int), 1, arquivoBIN);
	fread(&registro->popularidade, sizeof(int), 1, arquivoBIN);
	fread(&registro->peso, sizeof(int), 1, arquivoBIN);

	// Lê os campos de strings variáveis e aloca memória dinamicamente.
	fread(&registro->tecnologiaOrigem.tamanho, sizeof(int), 1, arquivoBIN);
	registro->tecnologiaOrigem.string = malloc(registro->tecnologiaOrigem.tamanho * sizeof(char) + 1);
	fread(registro->tecnologiaOrigem.string, sizeof(char), registro->tecnologiaOrigem.tamanho, arquivoBIN);
	registro->tecnologiaOrigem.string[registro->tecnologiaOrigem.tamanho] = '\0'; // Adiciona um caractere nulo ao final.

	fread(&registro->tecnologiaDestino.tamanho, sizeof(int), 1, arquivoBIN);
	registro->tecnologiaDestino.string = malloc(registro->tecnologiaDestino.tamanho * sizeof(char) + 1);
	fread(registro->tecnologiaDestino.string, sizeof(char), registro->tecnologiaDestino.tamanho, arquivoBIN);
	registro->tecnologiaDestino.string[registro->tecnologiaDestino.tamanho] = '\0'; // Adiciona um caractere nulo ao final.

	size_t bytesNaoUtilizados = TAM_REGISTRO - (5* sizeof(int) + registro->tecnologiaOrigem.tamanho +
		registro->tecnologiaDestino.tamanho + sizeof(char));
	char *lixo = malloc(bytesNaoUtilizados);
	fread(lixo, bytesNaoUtilizados, 1, arquivoBIN);
	free(lixo);
}

// Função para imprimir um registro, formatando a saída.
void imprimeRegistro(Registro *registro)
{
	imprimeString(registro->tecnologiaOrigem);
	printf(", ");
	imprimeNum(registro->grupo);
	printf(", ");
	imprimeNum(registro->popularidade);
	printf(", ");
	imprimeString(registro->tecnologiaDestino);
	printf(", ");
	imprimeNum(registro->peso);
	printf("\n");
}

// Função para liberar a memória alocada para uma estrutura de Registro.
void liberarRegistro(Registro *registro) {
	free(registro->tecnologiaOrigem.string);
	free(registro->tecnologiaDestino.string);
	free(registro);
}