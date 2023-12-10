#include "../headers/funcionalidades.h"

void criarCabecalho(FILE *arquivoBIN, Cabecalho *cabecalho)
{
	fseek(arquivoBIN, 0, SEEK_SET);
	fwrite(cabecalho, sizeof(Cabecalho), 1, arquivoBIN);
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

			if (registro->removido == '0') {
				// Verifica se o vértice de origem já existe no grafo
				int indiceOrigem = inserirVertice(grafo, registro->tecnologiaOrigem, registro->grupo);
				
				// Verifica se o vértice de destino já existe no grafo
				int indiceDestino = inserirVertice(grafo, registro->tecnologiaDestino, -2);

				if(registro->peso != -1 && registro->tecnologiaOrigem.tamanho != 0 && registro->tecnologiaDestino.tamanho != 0)
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

Grafo* gerarTransposta(Grafo* grafo) {

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

	return;
}

void kosaraju() {

	Grafo *grafo = gerarGrafo();

    int* visitados = (int*)calloc(grafo->numVertices, sizeof(int));
    int* pilha = (int*)malloc(grafo->numVertices * sizeof(int));
    int index = 0;

    // Primeira passagem: preenche a pilha com a ordem de finalização dos vértices
    for (int i = 0; i < grafo->numVertices; ++i) {
        if (!visitados[i]) {
            DFS(grafo, i, visitados, pilha, &index);
        }
    }

	Grafo *grafoInvertido = gerarTransposta(grafo);

	memset(visitados, 0, grafo->numVertices * sizeof(int));

	// Segunda passagem: identifica os componentes fortemente conexos
    int** componentes = NULL;
    int numComponentes = 0;

    for (int i = grafo->numVertices - 1; i >= 0; --i) {
        int v = pilha[i];
        if (!visitados[v]) {
            componentes = realloc(componentes, (numComponentes + 1) * sizeof(int*));
            componentes[numComponentes] = NULL;
            DFSInvertido(grafoInvertido, v, visitados, numComponentes, componentes);
            numComponentes++;
        }
    }

	// Processa os componentes fortemente conexos conforme necessário
    for (int i = 0; i < numComponentes; ++i) {
        free(componentes[i]);
    }

	if(numComponentes == grafo->numVertices) {
		printf("Sim, o grafo e fortemente conexo e possui %d componentes.\n", numComponentes);
	}
	else {
		printf("Nao, o grafo nao e fortemente conexo e possui %d componentes.\n", numComponentes);
	}

    // Liberar memória
    free(visitados);
    free(pilha);
	free(componentes);

    liberarGrafo(grafoInvertido);
	liberarGrafo(grafo);

	return;
}