#include <stdlib.h>
#include "fila_estatica.h"

void inicializarFilaEstatica(FilaEstatica* fila, int capacidade) {
    fila->dados = (Rating*)malloc(sizeof(Rating) * capacidade);
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
    fila->capacidade = capacidade;
}

void enfileirarEstatica(FilaEstatica* fila, Rating valor) {
    if (fila->tamanho < fila->capacidade) {
        fila->dados[fila->tras] = valor;
        fila->tras = (fila->tras + 1) % fila->capacidade;
        fila->tamanho++;
    }
}

int desenfileirarEstatica(FilaEstatica* fila, Rating* removido) {
    if (fila->tamanho == 0) return 0;
    *removido = fila->dados[fila->frente];
    fila->frente = (fila->frente + 1) % fila->capacidade;
    fila->tamanho--;
    return 1;
}

void limparFilaEstatica(FilaEstatica* fila) {
    free(fila->dados);
    fila->frente = fila->tras = fila->tamanho = fila->capacidade = 0;
}
