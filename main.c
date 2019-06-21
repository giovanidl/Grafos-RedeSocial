#include "redesocial.h"

int main(){

	Grafo* G;
	Fila* F;

	G = criaGrafo();
	F = criaFila();

	if(F == NULL) return 1;

	int instrucao, indexLogado;
	int logou = 0;
	menuInicial();

	//carregar banco de dados

	criaTeste(G,25);

	//printaUsuario(G->rede[13]);
	scanf("%d", &instrucao);
	while(instrucao < 2){
		switch (instrucao){
			case 0: // cadastrar
				if(!cadastrar(G))
					printf("Cadastro Realizado com Sucesso\n");
				menuInicial();
				break;
			case 1:// login
				//printaRede(G);
				while(indexLogado = login(G),indexLogado == -1){
					printf("Senha incorreta. Tente novamente\n");
				}
				logou++;
				perfil(G, F, indexLogado);
				menuInicial();
				break;
			case 2:// sair
				printf("Volte Sempre!!\n");
				return 0;
				break;
		}
		scanf("%d", &instrucao);
	}

	liberaFila(F);
	liberaGrafo(G);



	return 0;
}