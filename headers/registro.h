#ifndef REGISTRO_H
#define REGISTRO_H

#include "../headers/auxiliar.h"

// Função para ler um registro de um arquivo BIN e preencher uma estrutura de Registro.
void lerRegistroBIN(FILE *arquivoBIN, Registro *registro);

// Função para imprimir um registro, formatando a saída.
void imprimeRegistro(Registro *registro);

// Função para liberar a memória alocada para uma estrutura de Registro.
void liberarRegistro(Registro *registro);

#endif