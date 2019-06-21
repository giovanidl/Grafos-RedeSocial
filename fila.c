#include "fila.h"

void esvazia(Fila* f) {
	f->total = 0;
    f->ini = 0;
    f->fim = 0;
    return;
}

Fila* criaFila() {
	Fila* f = (Fila*) malloc(sizeof(Fila));
    esvazia(f);
    return f;
}

int estaVazia(Fila* f) {
    //return (f.total == 0);
    if (f->total == 0)
        return 1;
    return 0;
}

int estaCheia(Fila* f) {
    //return (f.total == TamFila);
    if (f->total == TamFila)
        return 1;
    return 0;
}

int entra(Fila* f, elem x) {
    if (estaCheia(f))
        return 1;
    f->vet[f->fim] = x;
    f->total++;
    if (f->fim == TamFila - 1)
        f->fim = 0;
    else
        f->fim++;
    return 0;
}

int sai(Fila* f) {
	int x;
    if (estaVazia(f))
        return 1;
    x = f->vet[f->ini];
    f->total--;
    if (f->ini == TamFila -1)
        f->ini = 0;
    else
        f->ini++;
    return x;
}

elem proxFila(Fila* f){
	return f->vet[f->ini];
}

void liberaFila(Fila * f){
	if(f != NULL)
		free(f);
	return;
}
