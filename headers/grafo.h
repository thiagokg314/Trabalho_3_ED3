#ifndef GRAFO_H
#define GRAFO_H

#include "../headers/structsGrafo.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Função auxiliar para encontrar um vértice pelo nome no grafo
int encontrarVertice(Grafo *grafo, const char *nomeTecnologia);

// Liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo);

#endif