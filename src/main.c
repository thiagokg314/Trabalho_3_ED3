#include<stdio.h>

#include "../headers/funcionalidades.h"

int main(int argc, char *argv[])
{
    int num;
    scanf("%d", &num);

    Grafo *grafo;

    // Utiliza uma estrutura de seleção (switch) para executar a função apropriada com base no valor lido.
    switch (num) {
        case 8:
            grafo = gerarGrafo();
            imprimirGrafo(grafo);
            liberarGrafo(grafo);
            break;
        case 9:
            gerarTransposta();
            break;
        case 10:
            listarTecnologias();
            break;
        case 11:
            
            break;
        case 12:
            
            break;
    }

    return 0;
}