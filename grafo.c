#include "grafo.h"

#define MAXV 1000

Grafo{
	int numV;
	int adj[MAXV][MAXV];// todos os elementos da matriz sao inicializados com -1, indicando nenhuma amizade, quando ficarem amigos ficam com o numero de similaridade.
	Usuario rede[MAXV];

};

Usuario{
	int index; // se o index for -1 na rede significa que ele nao está la (excluido e podera ser sobrescrito)
	char nomeUsuario[100];
	int idade;
	int sexo; // 0 - Masculino, 1 - Feminino, 2 - Trans, 3 - Prefiro nao dizer
	char cidade[50];
	char filmePreferido;
	char time[50];
	int interesseEm; // 0 - Masculino, 1 - Feminino, 2 - Trans, 3 - Prefiro nao dizer
	char senha[50];
};


Grafo* criaGrafo(){
	Grafo* G = (Grafo*) malloc(sizeof(Grafo));
	for(int i = 0; i < MAXV; i++){
		rede[i].index = -1;
	}
	Grafo->numV = 0;

	for(int i = 0; i < G->MAXV; i++)
		for(int j = 0; j < G->MAXV; j++)
			adj[i][j] = -1;

}

void liberaGrafo(Grafo* G){
	if(G != NULL)
		free(G);
	return;
}
