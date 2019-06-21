#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "fila.h"
//#include <conio.h>

#define MAXV 1000

typedef struct grafo Grafo;
typedef struct usuario Usuario;
typedef struct fila Fila;



Grafo* criaGrafo();
void liberaGrafo(Grafo* G);

int classificaIdade(Usuario U);

void menuInicial();

void menuSecundario();

int analisaIndex(Grafo* G);

void printaUsuario(Usuario U);

int avaliaSimilaridade(Usuario A, Usuario B);

void printaUsuarioSimples(Grafo* G,int indexLogado, int index);

int avaliaExistenciaUsuario(Grafo* G, char* str);

int cadastrar(Grafo* G);

int login(Grafo* G);

void printaSolicitacao(Grafo* G, int indexLogado, int indiceSolicitacao);

void aceitarSolicitacao(Grafo* G, char* nome, int indexLogado);

void veSolicitacoesAmizade(Grafo* G, int indexLogado);

void printaRede(Grafo* G, int indexLogado);

int enviaSolicitacao(Grafo* G, int indexLogado);

void veSolicitacoesEmAberto(Grafo* G, int indexLogado);

void recomendarAmigos(Grafo* G, int indexLogado);

void detectaFalsosAmigos(Grafo* G, int indexLogado);

int avaliaInteresse(Usuario A, Usuario B);

void recomendarNamorado(Grafo* G, int indexLogado);

void mostrarAmigos(Grafo* G, int indexLogado);

int ehamigo(Grafo* G, int A, int B);

int* talvezConheca(Grafo* G, Fila* F, int indexLogado);

void recomendaTalvezConheca(Grafo* G, Fila* F, int indexLogado);

void perfil(Grafo* G, Fila* F, int indexLogado);

int randomizar(int n);

void criaTesteRand(Grafo* G, int n);

void criaTeste(Grafo* G, int n);