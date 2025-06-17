#ifndef PILHA_ESTATICA_H
#define PILHA_ESTATICA_H

#include "leitura.h"

typedef struct {
    Rating* dados;
    int topo;
    int capacidade;
} PilhaEstatica;

void inicializarPilhaEstatica(PilhaEstatica* pilha, int capacidade);
void push(PilhaEstatica* pilha, Rating valor);
int pop(PilhaEstatica* pilha, Rating* removido);
int pilhaEstaticaVazia(PilhaEstatica* pilha);
void limparPilhaEstatica(PilhaEstatica* pilha);

#endif
