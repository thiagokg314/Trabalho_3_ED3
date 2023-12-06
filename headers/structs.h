#ifndef STRUCTS_H
#define STRUCTS_H

// Estrutura para o registro de cabecalho
#pragma pack(push, 1)
typedef struct
{
	char status;
	int proxRRN;
	int nroTecnologias;
	int nroParesTecnologias;
}

Cabecalho;
#pragma pack(pop)

// Estrutura para armazenar as strings e seus tamanhos
typedef struct
{
	int tamanho;
	char *string;
}

StringVariavel;

// Estrutura para o registro de elem
typedef struct
{
	char removido;
	int grupo;
	int popularidade;
	int peso;
	StringVariavel tecnologiaOrigem;
	StringVariavel tecnologiaDestino;
}

Registro;

#endif