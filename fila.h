#include<stdlib.h>

#define TamFila 1000

typedef int elem;

typedef struct fila {
    elem vet[TamFila];
    int ini, fim, total;
} Fila;

Fila* criaFila();
void esvazia(Fila* f);
int estaVazia(Fila* f);
int estaCheia(Fila* f);
int entra(Fila* f, elem x);
elem proxFila(Fila* f);
int sai(Fila* f);
void liberaFila(Fila* f);
