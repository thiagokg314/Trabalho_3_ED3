#ifndef FUNCIONALIDADES_H
#define FUNCIONALIDADES_H

#include "../headers/arquivo.h"
#include "../headers/registro.h"
#include "../headers/funcoesFornecidas.h"
#include "../headers/inserir.h"
#include "../headers/kosaraju.h"

// Implementacao da funcionalidade [8]
Grafo* gerarGrafo();

Grafo* gerarTransposta(Grafo* grafo);

void listarTecnologias();

void kosaraju();

#endif