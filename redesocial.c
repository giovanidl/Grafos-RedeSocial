#include "redesocial.h"

enum SEXO{
	MASCULINO, FEMININO, TRANSSEXUAL, ABSTENCAO
};

enum INTERESSE{
	MASC, FEM, TRANS, MASCFEM, NENHUM, ABS
};

struct usuario{
	int index; // se o index for -1 na rede significa que ele nao está la (excluido e podera ser sobrescrito)
	char nomeUsuario[100];
	int idade;
	int sexo; // 0 - Masculino, 1 - Feminino, 2 - Transsexual, 3 - Prefiro nao dizer
	char cidade[50];
	char filmePreferido[50];
	char time[50];
	int interesseEm; // 0 - Masculino, 1 - Feminino, 2 - Trans, 3- Masculino e Feminino, 4 - Nenhum, 5 - Prefiro nao dizer
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
	printf("<<<<<<<<<< A REDE SOCIAL >>>>>>>>>>\n\n\n");
	printf("---------- MENU PRINCIPAL ---------\n");
	printf("0 para cadastrar\n");
	printf("1 para logar\n");
	// ... continua
}

void menuSecundario(){
	printf("---------- MENU DE PERFIL ---------\n");
	printf("0 para ver solicitacoes\n");
	printf("1 para enviar solicitacao de amizade\n");
	printf("2 para ver solicitacoes em aberto\n");
	printf("3 para recomendar amigos\n");
	printf("4 para detectar falsos amigos\n");
	printf("5 para recomendar namorado\n");
	printf("6 para mostrar todos seus amigos (e tambem seus melhores amigos de acordo com a similaridade)\n");
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
	printf("Digite 2  para 'Transsexual'\n");
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

void recomendarAmigos(Grafo* G, int indexLogado){
	printf("Recomendacao de amizades (possuem grande similaridade a voce):\n");
	int amigosRecomendados = 0;
	for(int i = 0; i < MAXV; i++){
		if(G->rede[i].index != -1 && G->rede[i].index != indexLogado){
			if(avaliaSimilaridade(G->rede[i], G->rede[indexLogado]) >= 3){
				amigosRecomendados++;
				printf("||-----------------------------------------||\n");
				printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
				printf("Similaridade: %d\n", avaliaSimilaridade(G->rede[i], G->rede[indexLogado]));
			}
		}
	}
	if(!amigosRecomendados){
		printf("Nao ha pessoas recomendadas a voce :(\n");
	}
}

void detectaFalsosAmigos(Grafo* G, int indexLogado){
	printf("Falsos amigos (possuem baixa similaridade com voce):\n");
	int numAmigos = 0;
	int numFalsosAmigos = 0;
	for (int i = 0; i < MAXV; i++){
		//Se possui amizade
		if(G->adj[indexLogado][i] != -1 && G->adj[indexLogado][i] != 10){
			numAmigos++;
			if(G->adj[indexLogado][i] < 2){
				numFalsosAmigos++;
				printf("||-----------------------------------------||\n");
				printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
				printf("Similaridade: %d\n", G->adj[indexLogado][i]);
			}
		}
	}
	if(!numAmigos){
		printf("Voce nao tem amigos :(\n");
	}
	else if(!numFalsosAmigos){
		printf("Voce nao tem falsos amigos :)\n");
	}
}

// retorna 1 caso B seja de interesse de A, 0 caso contrario
int avaliaInteresse(Usuario A, Usuario B){
	if(A.interesseEm == NENHUM || A.interesseEm == ABS) return 0;
	if(A.interesseEm == MASCFEM && (B.sexo == MASCULINO || B.sexo == MASCULINO)) return 1;
	if(A.interesseEm == MASC && B.sexo == MASCULINO) return 1;
	if(A.interesseEm == FEM && B.sexo == FEMININO) return 1;
	if(A.interesseEm == TRANS && B.sexo == TRANSSEXUAL) return 1;
	return 0;
}

void recomendarNamorado(Grafo* G, int indexLogado){
	printf("Possiveis bons(as) namorados(as):\n");
	int numNamorados = 0;
	for(int i = 0; i < MAXV; i++){
		if(G->rede[i].index != indexLogado && (G->adj[indexLogado][i] > 4 && G->adj[indexLogado][i] != 10)){
			// se A é de interesse de B e B é de interesse de A.
			if(avaliaInteresse(G->rede[indexLogado], G->rede[i]) && avaliaInteresse(G->rede[i], G->rede[indexLogado])){
				numNamorados++;
				printf("||-----------------------------------------||\n");
				printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
				printf("Similaridade: %d\n", G->adj[indexLogado][i]);
				printf("Voces ja são amigos!!\n");
			}
		}
		else if(G->rede[i].index != indexLogado && (G->adj[indexLogado][i] == -1 || G->adj[indexLogado][i] == 10)){
			if(avaliaSimilaridade(G->rede[indexLogado], G->rede[i]) > 4){
				// se A é de interesse de B e B é de interesse de A.
				if(avaliaInteresse(G->rede[indexLogado], G->rede[i]) && avaliaInteresse(G->rede[i], G->rede[indexLogado])){
					numNamorados++;
					printf("||-----------------------------------------||\n");
					printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
					printf("Similaridade: %d\n", avaliaSimilaridade(G->rede[indexLogado], G->rede[i]));
					printf("Voces ainda nao sao amigos\n");
				}
			}
		}
	}
	if(!numNamorados){
		printf("Nao ha possiveis bons namorados para te recomendar :(\n");
	}
}

void mostrarAmigos(Grafo* G, int indexLogado){
	printf("Seus amigos:\n");
	int numAmigos = 0, maiorSimilaridade = 0;
	for (int i = 0; i < MAXV; i++){
		if(G->adj[indexLogado][i] != -1 && G->adj[indexLogado][i] != 10){
			if(G->adj[indexLogado][i] > 0){
				maiorSimilaridade = G->adj[indexLogado][i];
			}
			numAmigos++;
			printf("||-----------------------------------------||\n");
			printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
			printf("Similaridade: %d\n", G->adj[indexLogado][i]);
		}
	}
	if(!numAmigos){
		printf("Voce ainda nao tem amigos :(\n");
		return;
	}
	printf("Melhor(es) Amigo(s) (de acordo com a similaridade entre voces dois):\n");
	for (int i = 0; i < MAXV; i++){
		if(G->adj[indexLogado][i] == maiorSimilaridade){
			printf("||-----------------------------------------||\n");
			printf("Nome de Usuario: %s\n", G->rede[i].nomeUsuario);
			printf("Similaridade: %d\n", G->adj[indexLogado][i]);
		}
	}

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
				recomendarAmigos(G, indexLogado);
				printf("Para enviar solicitacao a algum deles, selecione a opcao '1' no Menu de Perfil\n");
				menuSecundario();
				break;

			case 4:	// detectar falsos amigos
				detectaFalsosAmigos(G, indexLogado);
				menuSecundario();
				break;

			case 5: // recomendar namorado
				recomendarNamorado(G, indexLogado);
				menuSecundario();
				break;

			case 6: // mostrar todos os amigos
				mostrarAmigos(G, indexLogado);
				menuSecundario();
				break;

			case 7:	// deslogar
				return;
				break;

		}
		scanf("%d", &instrucaoPerfil);
	}

}

void criaTeste(Grafo* G){
	G->numV = 4;
	G->rede[0].index = 0;
	strcpy(G->rede[0].nomeUsuario, "g");
	G->rede[0].idade = 1;
	G->rede[0].sexo = MASCULINO;
	strcpy(G->rede[0].cidade, "g");
	strcpy(G->rede[0].filmePreferido, "g");
	strcpy(G->rede[0].time, "g");
	G->rede[0].interesseEm = 0;
	strcpy(G->rede[0].senha, "g");


	G->rede[1].index = 1;
	strcpy(G->rede[1].nomeUsuario, "h");
	G->rede[1].idade = 70;
	G->rede[1].sexo = FEMININO;
	strcpy(G->rede[1].cidade, "h");
	strcpy(G->rede[1].filmePreferido, "h");
	strcpy(G->rede[1].time, "h");
	G->rede[1].interesseEm = 1;
	strcpy(G->rede[1].senha, "h");

	G->rede[2].index = 2;
	strcpy(G->rede[2].nomeUsuario, "c");
	G->rede[2].idade = 1;
	G->rede[2].sexo = MASCULINO;
	strcpy(G->rede[2].cidade, "g");
	strcpy(G->rede[2].filmePreferido, "g");
	strcpy(G->rede[2].time, "g");
	G->rede[2].interesseEm = 0;
	strcpy(G->rede[2].senha, "c");

	G->rede[3].index = 3;
	strcpy(G->rede[3].nomeUsuario, "d");
	G->rede[3].idade = 1;
	G->rede[3].sexo = MASCULINO;
	strcpy(G->rede[3].cidade, "g");
	strcpy(G->rede[3].filmePreferido, "g");
	strcpy(G->rede[3].time, "g");
	G->rede[3].interesseEm = 0;
	strcpy(G->rede[3].senha, "d");


}

int main(){

	Grafo* G;
	G = criaGrafo();
	int instrucao, indexLogado;
	int logou = 0;
	menuInicial();

	//carregar banco de dados

	//criaTeste(G);
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
