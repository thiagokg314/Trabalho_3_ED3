#include "../headers/funcionalidades.h"

void criarCabecalho(FILE *arquivoBIN, Cabecalho *cabecalho)
{
	fseek(arquivoBIN, 0, SEEK_SET);
	fwrite(cabecalho, sizeof(Cabecalho), 1, arquivoBIN);
}

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

Grafo* gerarGrafo() {

    char nomeArquivoBIN[50];
	scanf("%s", nomeArquivoBIN);

	FILE *arquivoBIN = abrirBIN(nomeArquivoBIN);

	Cabecalho *cabecalho = (Cabecalho*) malloc(sizeof(Cabecalho));
	fread(cabecalho, sizeof(Cabecalho), 1, arquivoBIN);

	Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));

	if (cabecalho->proxRRN == 0)
	{
		printf("Registro inexistente.\n");
	}
	else
	{
		grafo->numVertices = 0;
		grafo->vertices = NULL;

		for (int i = 0; i < cabecalho->proxRRN; i++)
		{
			Registro *registro = (Registro*) malloc(sizeof(Registro));
			lerRegistroBIN(arquivoBIN, registro);

			if (registro->removido == '0' && registro->peso != -1 
				&& registro->tecnologiaOrigem.tamanho != 0 && registro->tecnologiaDestino.tamanho != 0) {
				// Verifica se o vértice de origem já existe no grafo
				int indiceOrigem = inserirVertice(grafo, registro->tecnologiaOrigem, registro->grupo);
				
				// Verifica se o vértice de destino já existe no grafo
				int indiceDestino = inserirVertice(grafo, registro->tecnologiaDestino, -2);

				inserirAresta(grafo, registro->tecnologiaDestino, registro->peso, indiceOrigem, indiceDestino);
			}

			liberarRegistro(registro);
		}

		ordenarGrafo(grafo);
	}

	cabecalho->status = CONSISTENTE;
	criarCabecalho(arquivoBIN, cabecalho);

	free(cabecalho);
	fclose(arquivoBIN);

	return grafo;
}

Grafo* gerarTransposta() {

    Grafo *grafo = gerarGrafo();

	Grafo* grafoInvertido = (Grafo*)malloc(sizeof(Grafo));
    grafoInvertido->numVertices = 0;
    grafoInvertido->vertices = NULL;

	for (int i = 0; i < grafo->numVertices; i++) {
		inserirVertice(grafoInvertido, grafo->vertices[i].nomeTecnologia, grafo->vertices[i].grupo);
	}

    // Para cada vértice no grafo
    for (int i = 0; i < grafo->numVertices; i++) {
		for(int j = 0; j < grafo->vertices[i].numArestas; j++) {

			int indiceDestino = encontrarVertice(grafoInvertido, grafo->vertices[i].nomeTecnologia.string);

            int indiceOrigem = encontrarVertice(grafoInvertido, grafo->vertices[i].arestas[j].nomeTecnologiaDestino.string);

            inserirAresta(grafoInvertido, grafo->vertices[i].nomeTecnologia, 
                          grafo->vertices[i].arestas[j].peso, indiceOrigem, indiceDestino);
		}
    }

	liberarGrafo(grafo);

	ordenarGrafo(grafoInvertido);

    return grafoInvertido;
}

void listarTecnologias() {

	Grafo *grafo = gerarGrafo();

	int n;
	scanf("%d", &n);

	char *nomes[n];

	for (int i = 0; i < n; i++) {
		nomes[i] = (char*) malloc(50* sizeof(char));
		scan_quote_string(nomes[i]);
	}

	for(int k = 0; k < n; k++) {
		int encontrouDestino = 0;
		printf("%s:", nomes[k]);
		for(int i = 0; i < grafo->numVertices; i++) {
			for(int j = 0; j < grafo->vertices[i].numArestas; j++) {
				if(strcmp(nomes[k], grafo->vertices[i].arestas[j].nomeTecnologiaDestino.string) == 0) {
					if(encontrouDestino) {
						printf(",");
					}
					encontrouDestino = 1;
					printf(" %s", grafo->vertices[i].nomeTecnologia.string);
				}
			}
		}
		printf("\n\n");
	}

	liberarGrafo(grafo);
}