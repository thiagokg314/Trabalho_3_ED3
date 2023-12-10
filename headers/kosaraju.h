#ifndef KOSARAJU_H
#define KOSARAJU_H

#include "../headers/grafo.h"

void DFS(Grafo* grafo, int v, int* visitados, int* pilha, int* index);

void DFSInvertido(Grafo* grafo, int v, int* visitados, int componenteIndex, int** componentes);

#endif