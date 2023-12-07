#include "../headers/grafo.h"

// Função auxiliar para encontrar um vértice pelo nome no grafo
int encontrarVertice(Grafo *grafo, char *nomeTecnologia) {
    for (int i = 0; i < grafo->numVertices; i++) {
        if (strcmp(grafo->vertices[i].nomeTecnologia.string, nomeTecnologia) == 0) {
            return i; // Retorna o índice do vértice encontrado
        }
    }
    return -1; // Retorna -1 se o vértice não for encontrado
}

// Imprime o grafo de acordo com as especificacoes do trabalho
void imprimirGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->vertices[i].numArestas; j++) {
            imprimirVerticeAresta(&grafo->vertices[i], &grafo->vertices[i].arestas[j]);
            printf("\n");
        }
    }
}

void ordenarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        
    }
}

// Função auxiliar para imprimir informações de um vértice e sua aresta
void imprimirVerticeAresta(Vertice *vertice, Aresta *aresta) {
    imprimeString(vertice->nomeTecnologia);
    printf(", ");
    imprimeNum(vertice->grupo);
    printf(", ");
    imprimeNum(vertice->grauEntrada);
    printf(", ");
    imprimeNum(vertice->grauSaida);
    printf(", ");
    imprimeNum(vertice->grau);
    printf(", ");
    imprimeString(aresta->nomeTecnologiaDestino);
    printf(", ");
    imprimeNum(aresta->peso);
}

// Liberar a memória alocada para o grafo
void liberarGrafo(Grafo *grafo) {
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->vertices[i].numArestas; j++) {
            free(grafo->vertices[i].arestas[j].nomeTecnologiaDestino.string);
        }
        free(grafo->vertices[i].nomeTecnologia.string);
        free(grafo->vertices[i].arestas);
    }
    free(grafo->vertices);
}