#include "../headers/inserir.h"

int inserirVertice(Grafo* grafo, StringVariavel string, int grupo) {

	int indice = encontrarVertice(grafo, string.string);

	if(indice == -1) {
		grafo->numVertices++;
		grafo->vertices = realloc(grafo->vertices, grafo->numVertices*sizeof(Vertice));
		Vertice *vertice = &grafo->vertices[grafo->numVertices-1];
		vertice->numArestas = 0;
		vertice->arestas = NULL;

		// Preenche os dados do vértice
		vertice->nomeTecnologia.tamanho = string.tamanho;
		vertice->nomeTecnologia.string = (char*)malloc(vertice->nomeTecnologia.tamanho + 1);
		strcpy(vertice->nomeTecnologia.string, string.string);
		vertice->grupo = grupo;
		vertice->grauEntrada = 0;
		vertice->grauSaida = 0;
		vertice->grau = 0;
		
		indice = grafo->numVertices - 1;
	}

	else if(grafo->vertices[indice].grupo == -2) {
		grafo->vertices[indice].grupo = grupo;
	}

	return indice;
}

void inserirAresta(Grafo* grafo, StringVariavel string, int peso, int indiceOrigem, int indiceDestino) {

	grafo->vertices[indiceOrigem].numArestas++;
	grafo->vertices[indiceOrigem].arestas =realloc(grafo->vertices[indiceOrigem].arestas,
		grafo->vertices[indiceOrigem].numArestas*sizeof(Aresta));
	Aresta *aresta = &grafo->vertices[indiceOrigem].arestas[grafo->vertices[indiceOrigem].numArestas - 1];
	aresta->nomeTecnologiaDestino.tamanho = string.tamanho;
	aresta->nomeTecnologiaDestino.string = (char*)malloc(aresta->nomeTecnologiaDestino.tamanho + 1);
	strcpy(aresta->nomeTecnologiaDestino.string, string.string);
	aresta->peso = peso;

	// Atualiza os graus do vértice de origem
	grafo->vertices[indiceOrigem].grau++;
	grafo->vertices[indiceOrigem].grauSaida++;

	// Atualiza os graus do vértice de destino
	grafo->vertices[indiceDestino].grau++;
	grafo->vertices[indiceDestino].grauEntrada++;
}