#include "../headers/arquivo.h"

// Função para calcular o byte offset com base no RRN (Número de Registro Relativo).
int byte_offset(int proxRRN)
{
	return (proxRRN * TAM_REGISTRO) + TAM_CABECALHO;
}

// Função para abrir um arquivo BIN no caminho especificado e lidar com erros de abertura.
FILE* abrirBIN(char *nome)
{
	char pasta[] = "binarios/";
	char caminhoCompleto[50];
	strcpy(caminhoCompleto, pasta);
	strcat(caminhoCompleto, nome);
	FILE *arquivoBIN = fopen(caminhoCompleto, "rb");
	if (arquivoBIN == NULL)
	{
		printf("Falha no processamento do arquivo.");
		exit(0); // Encerra o programa em caso de falha na abertura do arquivo.
	}
	return arquivoBIN;
}