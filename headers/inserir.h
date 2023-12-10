#ifndef INSERIR_H
#define INSERIR_H

#include "../headers/grafo.h"

int inserirVertice(Grafo* grafo, StringVariavel string, int grupo);

void inserirAresta(Grafo* grafo, StringVariavel string, int peso, int indiceOrigem, int indiceDestino);

#endif