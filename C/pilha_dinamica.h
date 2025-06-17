#ifndef PILHA_DINAMICA_H
#define PILHA_DINAMICA_H

#include "leitura.h"

typedef struct NoPilha {
    Rating valor;
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
} PilhaDinamica;

void inicializarPilhaDinamica(PilhaDinamica* pilha);
void empilhar(PilhaDinamica* pilha, Rating valor);
int desempilhar(PilhaDinamica* pilha, Rating* removido);
int pilhaDinamicaVazia(PilhaDinamica* pilha);
void limparPilhaDinamica(PilhaDinamica* pilha);

#endif
