all:
	gcc -o programaTrab ./src/arquivo.c ./src/auxiliar.c ./src/funcionalidades.c ./src/funcoesFornecidas.c ./src/grafo.c ./src/main.c ./src/registro.c ./src/variaveis.c

run: programaTrab
	./programaTrab