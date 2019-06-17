#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXV 1000

typedef struct grafo Grafo;
typedef struct usuario Usuario;

Grafo* criaGrafo();
void liberaGrafo(Grafo* G);
