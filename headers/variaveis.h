#ifndef VARIAVEIS_H
#define VARIAVEIS_H

// Definição de constantes
#define BUFFER_TAM 50
#define TAM_REGISTRO 76
#define TAM_CABECALHO 13
#define INCONSISTENTE '0'
#define CONSISTENTE '1'
#define MAX_TECNOLOGIAS 500
#define MAX_PARES_TECNOLOGIAS 500

// Variáveis globais
extern int nroTecnologias;  // Número de tecnologias
extern int nroParesTecnologias;  // Número de pares de tecnologias

extern char tecnologiasExistentes[MAX_TECNOLOGIAS][BUFFER_TAM];  // Matriz de tecnologias

// Estrutura para armazenar pares de tecnologias
struct ParTecnologias {
    char tecOrigem[BUFFER_TAM];  // Tecnologia de origem
    char tecDestino[BUFFER_TAM];  // Tecnologia de destino
};

extern struct ParTecnologias paresTecnologiasExistentes[MAX_PARES_TECNOLOGIAS];  // Matriz de pares de tecnologias

#endif
