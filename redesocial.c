#include "grafo.h"


int analisaIndex(Grafo* G){
	for(int i = 0; i < G->numV; i++){
		if(G->Rede[i].index == -1){
			return i;
		}
	}
	return G->numV;
}

void imprimeUsuario(Usuario U){
	printf("Nome de Usuario: %s", U.nomeUsuario);
	printf("Idade: %d", U.idade);
}

int classificaIdade(Usuario* U){
	if(U->idade < 10) return 0;
	else if(U->idade >= 10 && U->idade < 19) return 1;
	else if(U->idade >= 20 && U->idade < 29) return 2;
	else if(U->idade >= 30 && U->idade < 39) return 3;
	else if(U->idade >= 40 && U->idade < 49) return 4;
	else if(U->idade >= 50 && U->idade < 59) return 5;
	else if(U->idade >= 60 && U->idade < 69) return 6;
	else if(U->idade >= 70) return 7;
}

Usuario cadastrar(Grafo* G){
	Usuario U;
	U.index = analisaIndex(G);
	G->numV++;

	printf("Informe seu nome de usuario:\n");
	scanf("%[^\n]", U.nomeUsuario);

	printf("Informe sua idade:\n");
	scanf("%d", &(U.idade));

	printf("Informe seu Sexo:\n");
	printf("Digite 0 para 'Masculino'\n");
	printf("Digite 1 para 'Feminino'\n");
	printf("Digite 2  para 'Trans'\n");
	printf("Digite 3  para 'Prefiro não dizer'\n");
	scanf("%d", &(U.sexo));

	printf("Informe sua cidade:\n");
	scanf("%[^\n]", U.cidade);

	printf("Informe seu nome filme preferido:\n");
	scanf("%[^\n]", U.filmePreferido);

	printf("Informe seu nome time do coração (se nao houver digite 'x'):\n");
	scanf("%[^\n]", U.time);

	printf("Informe em que tipo de pessoa voce tem interesse:\n");
	printf("Digite 0 para 'Masculino'\n");
	printf("Digite 1 para 'Feminino'\n");
	printf("Digite 2  para 'Trans'\n");
	printf("Digite 3  para 'Masculino e Feminino'\n");
	printf("Digite 4  para 'Nenhum'\n");
	printf("Digite 5  para 'Prefiro não dizer'\n");
	scanf("%d", &U.interesseEm);

	printf("Digite aqui sua senha:\n");
	scanf("%[^\n]", U.senha);

	return U;
}




int main(){

	Grafo* G;
	G = criaGrafo();
	int instrucao;

	scanf("%d", &instrucao)
	while(instrucao < 8){
		switch (instrucao){
			case 0: // cadastrar
				cadastrar();
				break;
			case 1:// login
				break; 

		}
	}


	liberaGrafo();
}
