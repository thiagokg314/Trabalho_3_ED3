#include "../headers/variaveis.h"

// Inicialização das variáveis globais definidas em 'variaveis.h'
int nroTecnologias = 0;  // Inicializa o número de tecnologias como zero.
int nroParesTecnologias = 0;  // Inicializa o número de pares de tecnologias como zero.

char tecnologiasExistentes[MAX_TECNOLOGIAS][BUFFER_TAM];  // Declara uma matriz para armazenar tecnologias.

// Declara uma matriz de estruturas 'ParTecnologias' para armazenar pares de tecnologias.
struct ParTecnologias paresTecnologiasExistentes[MAX_PARES_TECNOLOGIAS];