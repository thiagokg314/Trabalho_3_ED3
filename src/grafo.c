#include "../headers/grafo.h"

// Função auxiliar para encontrar um vértice pelo nome no grafo
int encontrarVertice(Grafo *grafo, const char *nomeTecnologia) {
    for (int i = 0; i < grafo->numVertices; i++) {
        if (strcmp(grafo->vertices[i].nomeTecnologia.string, nomeTecnologia) == 0) {
            return i; // Retorna o índice do vértice encontrado
        }
    }
    return -1; // Retorna -1 se o vértice não for encontrado
}

// Liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->vertices[i].numArestas; j++) {
            free(grafo->vertices[i].arestas->nomeTecnologiaDestino.string);
            free(grafo->vertices[i].arestas->nomeTecnologiaDestino.tamanho);
            free(grafo->vertices[i].arestas);
        }
        free(grafo->vertices[i].nomeTecnologia.string);
        free(grafo->vertices[i].nomeTecnologia.tamanho);
    }
    free(grafo->vertices);
    free(grafo);
}