
/*
	Trabalho Prático de Grafos - Rede Social
	Participantes:
		Giovani Decico Lucafo  10288779
		Tamiris Fernandes Tinelli  10346738

*/


#include "redesocial.h"

enum SEXO{
	MASCULINO, FEMININO, TRANSSEXUAL, ABSTENCAO
};

enum INTERESSE{
	MASC, FEM, TRANS, MASCFEM, NENHUM, ABS
};

char TIMES[6][50] = {"Sao Paulo", "Palmeiras", "Corinthians", "Santos", "Flamengo", "Botafogo"};

char FILMES[6][50] = {"Frozen", "Bastardos Inglorios", "Shrek", "Seven", "Avatar", "Titanic"};


char CIDADES[6][50] = {"Piracicaba", "Sao Paulo", "Sao Carlos", "Pirassununga", "Limeira", "Campinas"};




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
	printf("2 para sair\n");
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
	printf("7 para mostrar pessoas que talvez voce conheca\n");
	printf("8 para deslogar\n");

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

void printaUsuarioSimples(Grafo* G,int indexLogado, int index){

	int sim = avaliaSimilaridade(G->rede[index], G->rede[indexLogado]);
	if (sim == 0)
		printf("||---------------------------------------------||\n");
	else if(sim == 1)
		printf("||@@@@@@@@@------------------------------------||\n");
	else if(sim == 2)
		printf("||@@@@@@@@@@@@@@@@@@---------------------------||\n");
	else if(sim == 3)
		printf("||@@@@@@@@@@@@@@@@@@@@@@@@@@@------------------||\n");
	else if(sim == 4)
		printf("||@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@---------||\n");
	else if(sim == 5)
		printf("||@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@||\n");

	printf("Nome de Usuario: %s\n", G->rede[index].nomeUsuario);
	printf("Similaridade: %d\n\n", sim);
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

	for (int i = 0; i < G->numV; i++){
		if(G->rede[i].index != indexLogado)
			if(G->rede[i].index != -1 && G->adj[indexLogado][i])
				printaUsuarioSimples(G, indexLogado, i);
	}

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
				printaUsuarioSimples(G, indexLogado, i);
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
				printaUsuarioSimples(G, indexLogado, i);
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
				printaUsuarioSimples(G, indexLogado, i);
				printf("Voces ja são amigos!!\n");
			}
		}
		else if(G->rede[i].index != indexLogado && (G->adj[indexLogado][i] == -1 || G->adj[indexLogado][i] == 10)){
			if(avaliaSimilaridade(G->rede[indexLogado], G->rede[i]) > 4){
				// se A é de interesse de B e B é de interesse de A.
				if(avaliaInteresse(G->rede[indexLogado], G->rede[i]) && avaliaInteresse(G->rede[i], G->rede[indexLogado])){
					numNamorados++;
					printaUsuarioSimples(G, indexLogado, i);
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
			printaUsuarioSimples(G, indexLogado, i);
		}
	}
	if(!numAmigos){
		printf("Voce ainda nao tem amigos :(\n");
		return;
	}
	printf("Melhor(es) Amigo(s) (de acordo com a similaridade entre voces dois):\n");
	for (int i = 0; i < MAXV; i++){
		if(G->adj[indexLogado][i] == maiorSimilaridade){
			printaUsuarioSimples(G, indexLogado, i);
		}
	}

}

int ehamigo(Grafo* G, int A, int B){
	return (G->adj[A][B] != -1 && G->adj[A][B] != 10);
}
/*
	Esta funcao aplicará uma BFS no Grafo G, encontrando as menores distancias entre pessoas não amigas
	assim recomendando-as para o usuário logado
*/
int* talvezConheca(Grafo* G, Fila* F, int indexLogado){
	int visitados[G->numV];
	int* dist = (int*) malloc(sizeof(int)* G->numV);

	for(int i = 0; i < G->numV; i++){
		visitados[i] = 0;
		dist[i] = -1;
	}
	int j = indexLogado;
	dist[j] = 0;

	entra(F, j);
	visitados[j] = 1;


	while(!estaVazia(F)){
		for(int i = 0; i < G->numV; i++){
			if(ehamigo(G,j, i) && visitados[i] == 0){
				visitados[i] = 1;
				if(dist[i] == -1){
					dist[i] = dist[j] + 1;
					entra(F, i);
				}
			}
		}
		sai(F);
		j = proxFila(F);

	}
	/*
	for(int i = 0; i < G->numV; i++){
		printf("%d ", dist[i]);
	}
	printf("\n");
	*/
	return dist;

}

void recomendaTalvezConheca(Grafo* G, Fila* F, int indexLogado){
	printf("Pessoas que talvez voce conheça\n");
	int* dist = talvezConheca(G, F, indexLogado);
	int achados = 0;
	for (int i = 0; i < G->numV; i++){
		if(dist[i] == 1){
			achados++;
			printaUsuarioSimples(G, indexLogado, i);
		}
	}
	if(!achados){
		printf("Nao ha nenhuma pessoa na rede que talvez voce conheca\n");
	}
	if(dist != NULL)
		free(dist);
}

void perfil(Grafo* G, Fila* F, int indexLogado){
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

			case 7:	// mostrar pessoas que talvez o usuario logado conheca
				recomendaTalvezConheca(G, F, indexLogado);
				menuSecundario();
				break;

			case 8:	// deslogar
				return;
				break;

		}
		scanf("%d", &instrucaoPerfil);
	}
}

int randomizar(int n){
	return rand() % n;
}

void criaTesteRand(Grafo* G, int n){
	int i;
	for (i = 0; i < n; i++){
		G->rede[i].index = i;
		G->rede[i].idade = randomizar(99);
		G->rede[i].sexo = randomizar(4);
		strcpy(G->rede[i].cidade, CIDADES[randomizar(6)]);
		strcpy(G->rede[i].filmePreferido, FILMES[randomizar(6)]);
		strcpy(G->rede[i].time, TIMES[randomizar(6)]);
		G->rede[0].interesseEm = randomizar(6);

	}
	G->numV = i+1;

	for(int i = 0 ; i < G->numV; i++){
		for(int j = 0; j < G->numV; j++){
			int n = (rand() % 100) - 1;
			if(n < 11 && n >= -1)
				G->adj[i][j] = n;
			else
				G->adj[i][j] = -1;
		}
	}
}

void criaTeste(Grafo* G, int n){
	criaTesteRand(G, n);

	strcpy(G->rede[0].nomeUsuario, "Adelio");
	strcpy(G->rede[0].senha, "adelio123");

	strcpy(G->rede[1].nomeUsuario, "Bruno");
	strcpy(G->rede[1].senha, "bruno123");

	strcpy(G->rede[2].nomeUsuario, "Carlos");
	strcpy(G->rede[2].senha, "carlos123");

	strcpy(G->rede[3].nomeUsuario, "Drauzio");
	strcpy(G->rede[3].senha, "drauzio123");

	strcpy(G->rede[4].nomeUsuario, "Enrico");
	strcpy(G->rede[4].senha, "enrico123");

	strcpy(G->rede[5].nomeUsuario, "Fabiana");
	strcpy(G->rede[5].senha, "fabiana123");

	strcpy(G->rede[6].nomeUsuario, "Giovani");
	strcpy(G->rede[6].senha, "giovani123");

	strcpy(G->rede[7].nomeUsuario, "Henrique");
	strcpy(G->rede[7].senha, "henrique123");

	strcpy(G->rede[8].nomeUsuario, "Iris");
	strcpy(G->rede[8].senha, "iris123");

	strcpy(G->rede[9].nomeUsuario, "Joana");
	strcpy(G->rede[9].senha, "joana123");

	strcpy(G->rede[10].nomeUsuario, "Karla");
	strcpy(G->rede[10].senha, "karla123");

	strcpy(G->rede[11].nomeUsuario, "Luis");
	strcpy(G->rede[11].senha, "luis123");

	strcpy(G->rede[12].nomeUsuario, "Mario");
	strcpy(G->rede[12].senha, "mario123");

	strcpy(G->rede[13].nomeUsuario, "Natasha");
	strcpy(G->rede[13].senha, "natasha123");

	strcpy(G->rede[14].nomeUsuario, "Olga");
	strcpy(G->rede[14].senha, "olga123");

	strcpy(G->rede[15].nomeUsuario, "Pedro");
	strcpy(G->rede[15].senha, "pedro123");

	strcpy(G->rede[16].nomeUsuario, "Quincas");
	strcpy(G->rede[16].senha, "quincas123");

	strcpy(G->rede[17].nomeUsuario, "Ricardo");
	strcpy(G->rede[17].senha, "ricardo123");

	strcpy(G->rede[18].nomeUsuario, "Samanta");
	strcpy(G->rede[18].senha, "samanta123");

	strcpy(G->rede[19].nomeUsuario, "Tulio");
	strcpy(G->rede[19].senha, "tulio123");

	strcpy(G->rede[20].nomeUsuario, "Ursula");
	strcpy(G->rede[20].senha, "ursula123");

	strcpy(G->rede[21].nomeUsuario, "Victor");
	strcpy(G->rede[21].senha, "victor123");

	strcpy(G->rede[22].nomeUsuario, "Wesley");
	strcpy(G->rede[22].senha, "wesley123");

	strcpy(G->rede[23].nomeUsuario, "Xuxa");
	strcpy(G->rede[23].senha, "xuxa123");

	strcpy(G->rede[24].nomeUsuario, "Yolanda");
	strcpy(G->rede[24].senha, "yolanda123");

	strcpy(G->rede[25].nomeUsuario, "Zelia");
	strcpy(G->rede[25].senha, "zelia123");
}

