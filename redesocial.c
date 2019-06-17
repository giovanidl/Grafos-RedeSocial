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

void menuInicial(){
	printf("0 para cadastrar\n");
	printf("1 para logar\n");
	// ... continua
}

void menuSecundario(){
	printf("0 para ver solicitacoes\n");
	printf("1 para enviar solicitacao de amizade\n");
	printf("2 para ver solicitacoes em aberto\n");
	printf("3 para recomendar amigos\n");
	printf("4 para detectar falsos amigos\n");
	printf("5 para recomendar namorado\n");
	printf("7 para deslogar\n");

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

void printaUsuario(Usuario U){
	printf("||---------------------------------------------------||\n");
	printf("Nome de Usuario: %s\n", U.nomeUsuario);
	printf("Idade: %d\n", U.idade);
	printf("Sexo: %d\n", U.sexo);
	printf("Cidade: %s\n", U.cidade);
	printf("Filme Preferido: %s\n", U.filmePreferido);
	printf("Time: %s\n", U.time);
	//... continua
}

int avaliaSimilaridade(Usuario A, Usuario B){
	int similaridade = 0;

	if(classificaIdade(A) == classificaIdade(B))
		similaridade++;
	if(A.sexo == B.sexo)
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
	getchar();
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
		//getchar();
		if(!strcmp(senha, G->rede[indexAchado].senha)){
			return indexAchado;
		}
	}
	return -1;	
}



void printaSolicitacao(Grafo* G, int indexLogado, int indiceSolicitacao){
	printf("Quero ser seu amigo:\n");
	printf("Nome: %s\n", G->rede[indiceSolicitacao].nomeUsuario);
	printf("Similaridade a voce: ");
	printf("%d\n", avaliaSimilaridade(G->rede[indexLogado], G->rede[indiceSolicitacao]));

}
void aceitarSolicitacao(Grafo* G, char* nome, int indexLogado){
	for(int i = 0; i < MAXV; i ++){
		if(G->adj[indexLogado][i] && !strcmp(G->rede[i].nomeUsuario, nome)){
			G->adj[indexLogado][i] = avaliaSimilaridade(G->rede[indexLogado], G->rede[i]);
			G->adj[i][indexLogado] = avaliaSimilaridade(G->rede[indexLogado], G->rede[i]);		}
	}
	printf("Solicitacao aceita\n");
}

void veSolicitacoesAmizade(Grafo* G, int indexLogado){
	printf("Solicitacoes de amizade:\n");
	int solicitacoes = 0;
	for(int i = 0; i < MAXV; i++){
		if(G->adj[indexLogado][i] == 10){
			solicitacoes++;
			printaSolicitacao(G, indexLogado, i);
		}
	}
	if(!solicitacoes){
		printf("Voce nao tem nenhuma solicitacao\n");
		return;
	}
	printf("Voce deseja aceitar alguma solicitacao?\n");
	printf("Digite 0 se sim ou 1 caso contrario\n");
	getchar();
	char nome[100];
	int escolha;
	scanf("%d",&escolha);
	getchar();
	switch (escolha){
		case 0:
			printf("Digite o nome de usuario da pessoa\n");
			setbuf(stdin, NULL);
			scanf("%[^\n]",nome);
			//scanf("%*s");
			getchar();
			aceitarSolicitacao(G, nome, indexLogado);
			return;
			break;
		case 1:
			return;
			break;
		default:
			printf("Opcao nao valida\n");
			break;
		scanf("%d",&escolha);	
		getchar();
	}

}

void printaRede(Grafo* G, int indexLogado){
	for (int i = 0; i < MAXV; i++){
		if(G->rede[i].index != -1){
			if(G->rede[i].index != indexLogado)
				printaUsuario(G->rede[i]);

			printf("vtnc esse calho: %d\n", indexLogado);
			printf("afdjasasfss: %d\n", G->rede[i].index);
		}
	}
}

int enviaSolicitacao(Grafo* G, int indexLogado){
	printf("Para quem voce deseja enviar uma solicitacao?\n");

	printaRede(G, indexLogado);
	char nome[100];
	printf("Digite o Nome de Usuario da Pessoa:\n");
	getchar();
	scanf("%[^\n]", nome);
	getchar();

	for(int i = 0; i < MAXV; i++){
		if(!strcmp(G->rede[i].nomeUsuario, nome)){
			G->adj[i][indexLogado] = 10; // enviou solicitação
			return 0;
		}
	}
	printf("Nao ha nenhuma pessoa com esse nome\n");
	return 1;

}
void veSolicitacoesEmAberto(Grafo* G, int indexLogado){
	int n = 0;
	for (int i = 0; i < MAXV; i++){
		if(G->adj[i][indexLogado] == 10){
			n++;
			printf("Solicitacoes em Aberto:\n");
			printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
			printf("Indice de Similaridade entre voces: %d\n", avaliaSimilaridade(G->rede[i], G->rede[indexLogado]));
		}
	}
	if(!n)
		printf("Voce nao tem solicitacoes de amizade em aberto\n");
}

void perfil(Grafo* G, int indexLogado){
	int instrucaoPerfil;
	getchar();
	menuSecundario();
	scanf("%d", &instrucaoPerfil);
	while(instrucaoPerfil < 8){
		switch (instrucaoPerfil){

			case 0: // ver solicitacoes de amizade (informar as chances da amizade ser verdadeira)
				veSolicitacoesAmizade(G, indexLogado);
				menuSecundario();
				break;

			case 1: // enviar solicitacao
				if(!enviaSolicitacao(G, indexLogado))
					printf("Solicitacao enviada com sucesso\n");
					printf("\n\n\n");
					menuSecundario();
				break;

			case 2: // ver solicitacoes em aberto
				veSolicitacoesEmAberto(G, indexLogado);
				menuSecundario();
				break;

			case 3:	// recomendar amigos
				//recomendarAmigos();
				break;

			case 4:	// detectar falsos amigos
				break;

			case 5: // recomendar namorado
				break;

			case 6:
				break;

			case 7:	// deslogar
				return;
				break;

		}
		scanf("%d", &instrucaoPerfil);
	}

}
void criaTeste(Grafo* G){
	G->numV = 2;
	G->rede[0].index = 0;
	strcpy(G->rede[0].nomeUsuario, "g");
	G->rede[0].idade = 1;
	G->rede[0].sexo = MASCULINO;
	strcpy(G->rede[0].cidade, "g");
	strcpy(G->rede[0].filmePreferido, "g");
	strcpy(G->rede[0].time, "g");
	G->rede[0].interesseEm = 1;
	strcpy(G->rede[0].senha, "g");


	G->rede[1].index = 1;
	strcpy(G->rede[1].nomeUsuario, "h");
	G->rede[1].idade = 1;
	G->rede[1].sexo = MASCULINO;
	strcpy(G->rede[1].cidade, "h");
	strcpy(G->rede[1].filmePreferido, "h");
	strcpy(G->rede[1].time, "h");
	G->rede[1].interesseEm = 1;
	strcpy(G->rede[1].senha, "h");


}

int main(){

	Grafo* G;
	G = criaGrafo();
	int instrucao, indexLogado;
	int logou = 0;
	menuInicial();

	criaTeste(G);
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
				perfil(G, indexLogado);
				menuInicial();
				break;
			case 2:
				printf("Sair;");
		}
		scanf("%d", &instrucao);
	}

	liberaGrafo(G);
}
