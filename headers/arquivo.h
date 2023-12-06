#ifndef ARQUIVO_H
#define ARQUIVO_H

#include "../headers/variaveis.h"

#include<stdio.h>
#include<stdlib.h>
#include <string.h>

// Função para calcular o byte offset com base no RRN (Número de Registro Relativo).
int byte_offset(int proxRRN);

// Função para abrir um arquivo BIN no caminho especificado.
FILE* abrirBIN(char *nome);

#endif