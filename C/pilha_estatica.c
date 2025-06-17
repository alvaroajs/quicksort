#include <stdlib.h>
#include "pilha_estatica.h"

void inicializarPilhaEstatica(PilhaEstatica* pilha, int capacidade) {
    pilha->dados = (Rating*)malloc(sizeof(Rating) * capacidade);
    pilha->topo = 0;
    pilha->capacidade = capacidade;
}

void push(PilhaEstatica* pilha, Rating valor) {
    if (pilha->topo < pilha->capacidade) {
        pilha->dados[pilha->topo++] = valor;
    }
}

int pop(PilhaEstatica* pilha, Rating* removido) {
    if (pilha->topo == 0) return 0;
    *removido = pilha->dados[--pilha->topo];
    return 1;
}

int pilhaEstaticaVazia(PilhaEstatica* pilha) {
    return pilha->topo == 0;
}

void limparPilhaEstatica(PilhaEstatica* pilha) {
    free(pilha->dados);
    pilha->topo = 0;
    pilha->capacidade = 0;
}
