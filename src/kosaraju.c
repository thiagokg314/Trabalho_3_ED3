#include "../headers/grafo.h"

void DFS(Grafo* grafo, int v, int* visitados, int* pilha, int* index) {

    visitados[v] = 1;

    for (int i = 0; i < grafo->vertices[v].numArestas; ++i) {
        int destino = encontrarVertice(grafo, grafo->vertices[v].arestas[i].nomeTecnologiaDestino.string);
        if (!visitados[destino]) {
            DFS(grafo, destino, visitados, pilha, index);
        }
    }

    pilha[*index] = v;
    (*index)++;
}

// Função DFS para encontrar os componentes fortemente conexos
void DFSInvertido(Grafo* grafo, int v, int* visitados, int componenteIndex, int** componentes) {

    visitados[v] = 1;
    componentes[componenteIndex] = realloc(componentes[componenteIndex], (grafo->numVertices) * sizeof(int));
    componentes[componenteIndex][v] = 1;

    for (int i = 0; i < grafo->vertices[v].numArestas; ++i) {
        int destino = encontrarVertice(grafo, grafo->vertices[v].arestas[i].nomeTecnologiaDestino.string);
        if (!visitados[destino]) {
            DFSInvertido(grafo, destino, visitados, componenteIndex, componentes);
        }
    }
}