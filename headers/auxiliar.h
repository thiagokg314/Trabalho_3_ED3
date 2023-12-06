#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "structs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Função para ler uma string de um arquivo CSV.
char *retornaString(FILE *arquivoCSV);

// Função para ler um número inteiro de um arquivo CSV.
int retornaNum(FILE *arquivoCSV);

// Função para imprimir um número inteiro ou "NULO" se for -1.
void imprimeNum(int inteiro);

// Função para imprimir uma string variável ou "NULO" se for vazia.
void imprimeString(StringVariavel string);

#endif