#include <stdlib.h>
#include "pilha_dinamica.h"

void inicializarPilhaDinamica(PilhaDinamica* pilha) {
    pilha->topo = NULL;
}

void empilhar(PilhaDinamica* pilha, Rating valor) {
    NoPilha* novo = (NoPilha*)malloc(sizeof(NoPilha));
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

int desempilhar(PilhaDinamica* pilha, Rating* removido) {
    if (!pilha->topo) return 0;
    NoPilha* temp = pilha->topo;
    *removido = temp->valor;
    pilha->topo = temp->prox;
    free(temp);
    return 1;
}

int pilhaDinamicaVazia(PilhaDinamica* pilha) {
    return pilha->topo == NULL;
}

void limparPilhaDinamica(PilhaDinamica* pilha) {
    Rating lixo;
    while (desempilhar(pilha, &lixo));
}
