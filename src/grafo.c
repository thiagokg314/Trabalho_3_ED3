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

// Função de comparação para o qsort para as arestas
int compararArestas(const void *a, const void *b) {
    return strcmp(((Aresta *)a)->nomeTecnologiaDestino.string, ((Aresta *)b)->nomeTecnologiaDestino.string);
}

// Função de comparação para o qsort para os vértices
int compararVertices(const void *a, const void *b) {
    return strcmp(((Vertice *)a)->nomeTecnologia.string, ((Vertice *)b)->nomeTecnologia.string);
}

// Função para ordenar as arestas de um vértice
void ordenarArestas(Vertice *vertice) {
    if (vertice == NULL || vertice->arestas == NULL || vertice->numArestas <= 0) {
        // Verificação de entrada inválida
        return;
    }

    // Usando a função qsort para ordenar as arestas
    qsort(vertice->arestas, vertice->numArestas, sizeof(Aresta), compararArestas);
}

// Função para ordenar o grafo
void ordenarGrafo(Grafo *grafo) {
    if (grafo == NULL || grafo->vertices == NULL || grafo->numVertices <= 0) {
        // Verificação de entrada inválida
        return;
    }

    // Usando a função qsort para ordenar os vértices
    qsort(grafo->vertices, grafo->numVertices, sizeof(Vertice), compararVertices);

    // Iterar sobre os vértices e ordenar as arestas de cada vértice
    for (int i = 0; i < grafo->numVertices; i++) {
        ordenarArestas(&(grafo->vertices[i]));
    }
}

// Função auxiliar para imprimir informações de um vértice e sua aresta
void imprimirVerticeAresta(Vertice *vertice, Aresta *aresta) {
    imprimeString(vertice->nomeTecnologia);
    printf(" ");
    imprimeNum(vertice->grupo);
    printf(" ");
    imprimeNum(vertice->grauEntrada);
    printf(" ");
    imprimeNum(vertice->grauSaida);
    printf(" ");
    imprimeNum(vertice->grau);
    printf(" ");
    imprimeString(aresta->nomeTecnologiaDestino);
    printf(" ");
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