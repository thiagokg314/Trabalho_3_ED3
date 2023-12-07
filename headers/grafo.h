#ifndef GRAFO_H
#define GRAFO_H

#include "../headers/structsGrafo.h"
#include "../headers/auxiliar.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Função auxiliar para encontrar um vértice pelo nome no grafo
int encontrarVertice(Grafo *grafo, char *nomeTecnologia);

// Imprime o grafo de acordo com as especificacoes do trabalho
void imprimirGrafo(Grafo *grafo);

int compararVertices(const void *a, const void *b);

void ordenarGrafo(Grafo *grafo);

// Função auxiliar para imprimir informações de um vértice e sua aresta
void imprimirVerticeAresta(Vertice *vertice, Aresta *aresta);

// Liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo);

#endif