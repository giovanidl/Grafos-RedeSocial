#include "redesocial.h"

enum SEXO{
	MASCULINO, FEMININO, TRANS, NEUTRO
};

struct usuario{
	int index; // se o index for -1 na rede significa que ele nao está la (excluido e podera ser sobrescrito)
	char nomeUsuario[100];
	int idade;
	int sexo; // 0 - Masculino, 1 - Feminino, 2 - Trans, 3 - Prefiro nao dizer
	char cidade[50];
	char filmePreferido[50];
	char time[50];
	int interesseEm; // 0 - Masculino, 1 - Feminino, 2 - Trans, 3 - Prefiro nao dizer
	char senha[50];
};

struct grafo{
	int numV;
	int adj[MAXV][MAXV];// todos os elementos da matriz sao inicializados com -1, indicando nenhuma amizade, quando ficarem amigos ficam com o numero de similaridade.
	Usuario rede[MAXV];
};

Grafo* criaGrafo(){
	Grafo* G = (Grafo*) malloc(sizeof(Grafo));
	for(int i = 0; i < MAXV; i++){
		G->rede[i].index = -1;
	}
	G->numV = 0;

	for(int i = 0; i < MAXV; i++)
		for(int j = 0; j < MAXV; j++)
			G->adj[i][j] = -1;

}

void liberaGrafo(Grafo* G){
	if(G != NULL)
		free(G);
	return;
}


int classificaIdade(Usuario U){
	if(U.idade < 10) return 0;
	else if(U.idade >= 10 && U.idade < 19) return 1;
	else if(U.idade >= 20 && U.idade < 29) return 2;
	else if(U.idade >= 30 && U.idade < 39) return 3;
	else if(U.idade >= 40 && U.idade < 49) return 4;
	else if(U.idade >= 50 && U.idade < 59) return 5;
	else if(U.idade >= 60 && U.idade < 69) return 6;
	else if(U.idade >= 70) return 7;
}

void menu(){
	printf("0 para cadastrar\n");
	printf("1 para logar\n");
	// ... continua
}


int analisaIndex(Grafo* G){
	for(int i = 0; i < G->numV; i++){
		if(G->rede[i].index == -1){
			G->rede[i].index = i;
			return i;
		}
	}
	return G->numV;
}

void imprimeUsuario(Usuario U){
	printf("Nome de Usuario: %s", U.nomeUsuario);
	printf("Idade: %d", U.idade);
	//... continua
}

int avaliaSimilaridade(Usuario A, Usuario B){
	int similaridade = 0;

	if(classificaIdade(A) == classificaIdade(B))
		similaridade++;
	if(A.sexo == MASCULINO && B.sexo == MASCULINO)
		similaridade++;
	if(!strcmp(A.cidade, B.cidade))
		similaridade++;
	if(!strcmp(A.filmePreferido, B.filmePreferido))
		similaridade++;
	if(!strcmp(A.time, B.time))
		similaridade++;

	return similaridade;
}

int avaliaExistenciaUsuario(Grafo* G, char* str){
	for(int i = 0; i < MAXV; i++){
		if(!strcmp(str, G->rede[i].nomeUsuario))
			return 1;
	}
	return 0;
}

int cadastrar(Grafo* G){
	Usuario U;
	U.index = analisaIndex(G);
	G->numV++;
	getchar();
	printf("Informe seu nome de usuario:\n");
	scanf("%[^\n]", U.nomeUsuario);
	if (avaliaExistenciaUsuario(G, U.nomeUsuario)){
		printf("Nome de Usuario ja existente\n");
		return 1;
	}
	getchar();

	printf("Informe sua idade:\n");
	scanf("%d", &(U.idade));

	printf("Informe seu Sexo:\n");
	printf("Digite 0 para 'Masculino'\n");
	printf("Digite 1 para 'Feminino'\n");
	printf("Digite 2  para 'Trans'\n");
	printf("Digite 3  para 'Prefiro não dizer'\n");
	scanf("%d", &(U.sexo));
	getchar();
	printf("Informe sua cidade:\n");
	scanf("%[^\n]", U.cidade);
	getchar();
	printf("Informe seu nome filme preferido:\n");
	scanf("%[^\n]", U.filmePreferido);
	getchar();
	printf("Informe seu nome time do coracao (se nao houver digite 'x'):\n");
	scanf("%[^\n]", U.time);
	getchar();
	printf("Informe em que tipo de pessoa voce tem interesse:\n");
	printf("Digite 0 para 'Masculino'\n");
	printf("Digite 1 para 'Feminino'\n");
	printf("Digite 2  para 'Trans'\n");
	printf("Digite 3  para 'Masculino e Feminino'\n");
	printf("Digite 4  para 'Nenhum'\n");
	printf("Digite 5  para 'Prefiro não dizer'\n");
	scanf("%d", &U.interesseEm);
	getchar();
	printf("Digite aqui sua senha:\n");
	scanf("%[^\n]", U.senha);
	getchar();
	G->rede[U.index] = U;
	return 0;
}

/*
	Retorna -1 caso tenha havido algum erro na hora de fazer o login, caso contrario, retorna o index achado
*/
int login(Grafo* G){

	char nome[50];
	printf("Nome de Usuario:\n");
	scanf("%[^\n]", nome);
	getchar();
	int flagachou = 0;
	int indexAchado;
	for(int i =0; i < G->numV; i++){
		if(!strcmp(nome, G->rede[i].nomeUsuario)){
			flagachou++;
			indexAchado = i;
		}
	}

	if(flagachou){
		char senha[50];
		printf("Senha:\n");
		scanf("%[^\n]", senha);
		getchar();
		if(!strcmp(senha, G->rede[indexAchado].senha)){
			return indexAchado;
		}
	}
	return -1;	
}

void printaUsuarioSolicitacao(Grafo* G, int indice){
	printf("Nome: %s", G->rede[indice].nomeUsuario);
	printf("")
}

void printaSolicitacao(){
	printf("Quero ser seu amigo:");
}

veSolicitacoesAmizade(Grafo* G, indexLogado){
	printf("Solicitações de amizade:\n")
	for(int i = 0; i < G->MAXV){
		if(G->adj[indexLogado][i] == 10){
			printaSolicitacao();
		}
	}
}

void perfil(Grafo* G, int indexLogado){
	int instrucaoPerfil;
	scanf("%d", &instrucaoPerfil);

	while(instrucaoPerfil < 8){
		switch (instrucaoPerfil){

			case 0: // ver solicitacoes de amizade (informar as chances da amizade ser verdadeira)
				veSolicitacoesAmizade(G, indexLogado);

				break;

			case 1: // enviar solicitacao
				break;

			case 2: // recomendar amigos
				break;

			case 3:	// recomendar namorado
				break;

			case 4:	// detectar falsos amigos
				break;

			case 5:
				break;

			case 6:
				break;

			case 7:	// deslogar
				break;

		}

	}

}

int main(){

	Grafo* G;
	G = criaGrafo();
	int instrucao, indexLogado;
	int logou = 0;
	menu();

	scanf("%d", &instrucao);
	while(instrucao < 2){
		switch (instrucao){
			case 0: // cadastrar
				if(!cadastrar(G))
					printf("Cadastro Realizado com Sucesso\n");
				menu();
				break;
			case 1:// login
				while(indexLogado = login(G),indexLogado == -1);
				logou++;
				perfil(G, indexLogado);
				break;
			case 2:
				printf("Sair;");
		}
		scanf("%d", &instrucao);
	}

	liberaGrafo(G);
}
