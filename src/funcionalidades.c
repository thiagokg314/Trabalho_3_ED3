#include "../headers/funcionalidades.h"

void criarCabecalho(FILE *arquivoBIN, Cabecalho *cabecalho)
{
	fseek(arquivoBIN, 0, SEEK_SET);
	fwrite(cabecalho, sizeof(Cabecalho), 1, arquivoBIN);
}

void gerarGrafo() {

    char nomeArquivoBIN[50];
	scanf("%s", nomeArquivoBIN);

	FILE *arquivoBIN = abrirBIN(nomeArquivoBIN);

	Cabecalho *cabecalho = (Cabecalho*) malloc(sizeof(Cabecalho));
	fread(cabecalho, sizeof(Cabecalho), 1, arquivoBIN);

	printf("Numero de Tecnologias: %d\n", cabecalho->nroTecnologias);

	if (cabecalho->proxRRN == 0)
	{
		printf("Registro inexistente.\n");
	}
	else
	{
		Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));
		grafo->numVertices = 0;
		grafo->vertices = NULL;

		for (int i = 0; i < cabecalho->proxRRN; i++)
		{
			Registro *registro = (Registro*) malloc(sizeof(Registro));
			lerRegistroBIN(arquivoBIN, registro);

			if (registro->removido == '0')
			{
				//imprimeRegistro(registro);
				// Verifica se o vértice de origem já existe no grafo
				int indiceOrigem = encontrarVertice(grafo, registro->tecnologiaOrigem.string);

				// Se não existe, cria um novo vértice
				if(indiceOrigem == -1) {
					//printf("CRIOU VERTICE\n");
					grafo->numVertices++;
					grafo->vertices = realloc(grafo->vertices, grafo->numVertices*sizeof(Vertice));
					Vertice *vertice = &grafo->vertices[grafo->numVertices-1];
					vertice->numArestas = 0;
					vertice->arestas = NULL;

					// Preenche os dados do vértice
					vertice->nomeTecnologia.tamanho = registro->tecnologiaOrigem.tamanho;
					vertice->nomeTecnologia.string = (char*)malloc(vertice->nomeTecnologia.tamanho);
					strcpy(vertice->nomeTecnologia.string, registro->tecnologiaOrigem.string);
					vertice->grupo = registro->grupo;
					vertice->grauEntrada = 0;
					vertice->grauSaida = 0;
					vertice->grau = 0;
					
					indiceOrigem = grafo->numVertices - 1;
				}
				
				int indiceDestino = encontrarVertice(grafo, registro->tecnologiaDestino.string);

				if(indiceDestino == -1) {
					grafo->numVertices++;
					grafo->vertices = realloc(grafo->vertices, grafo->numVertices*sizeof(Vertice));
					Vertice *vertice = &grafo->vertices[grafo->numVertices-1];
					vertice->numArestas = 0;
					vertice->arestas = NULL;

					// Preenche os dados do vértice
					vertice->nomeTecnologia.tamanho = registro->tecnologiaDestino.tamanho;
					vertice->nomeTecnologia.string = (char*)malloc(vertice->nomeTecnologia.tamanho);
					strcpy(vertice->nomeTecnologia.string, registro->tecnologiaDestino.string);
					vertice->grupo = registro->grupo;
					vertice->grauEntrada = 0;
					vertice->grauSaida = 0;
					vertice->grau = 0;

					indiceDestino = grafo->numVertices - 1;
				}

				grafo->vertices[indiceOrigem].numArestas++;
				grafo->vertices[indiceOrigem].arestas =realloc(grafo->vertices[indiceOrigem].arestas,
					grafo->vertices[indiceOrigem].numArestas*sizeof(Aresta));
				Aresta *aresta = &grafo->vertices[indiceOrigem].arestas[grafo->vertices[indiceOrigem].numArestas - 1];
				aresta->nomeTecnologiaDestino.tamanho = registro->tecnologiaDestino.tamanho;
				aresta->nomeTecnologiaDestino.string = (char*)malloc(aresta->nomeTecnologiaDestino.tamanho);
				strcpy(aresta->nomeTecnologiaDestino.string, registro->tecnologiaDestino.string);
				aresta->peso = registro->peso;

				// Atualiza os graus do vértice de origem
				grafo->vertices[indiceOrigem].grau++;
				grafo->vertices[indiceOrigem].grauSaida++;

				// Atualiza os graus do vértice de destino
				grafo->vertices[indiceDestino].grau++;
				grafo->vertices[indiceDestino].grauEntrada++;
			}

			liberarRegistro(registro);
		}

		printf("Numero de vertices: %d\n", grafo->numVertices);
		imprimirGrafo(grafo);
		liberarGrafo(grafo);
	}

	cabecalho->status = CONSISTENTE;
	criarCabecalho(arquivoBIN, cabecalho);

	free(cabecalho);
	fclose(arquivoBIN);
}