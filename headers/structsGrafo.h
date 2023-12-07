#ifndef STRUCTSGRAFO_H
#define STRUCTSGRAFO_H

#include "../headers/structs.h"

// Estrutura para representar uma aresta ponderada
typedef struct {
    StringVariavel nomeTecnologiaDestino;
    int peso;
} 

Aresta;

// Estrutura para representar um vértice do grafo
typedef struct {
    StringVariavel nomeTecnologia;
    int grupo;
    int grauEntrada;
    int grauSaida;
    int grau;
    Aresta *arestas; // Lista de adjacências
    int numArestas;  // Número de arestas
}

Vertice;

// Estrutura para representar o grafo
typedef struct {
    Vertice *vertices; // Vetor de vértices
    int numVertices;   // Número de vértices
} 

Grafo;

#endif

