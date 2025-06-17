#ifndef FILA_ESTATICA_H
#define FILA_ESTATICA_H

#include "leitura.h"

typedef struct {
    Rating* dados;
    int frente, tras, tamanho, capacidade;
} FilaEstatica;

void inicializarFilaEstatica(FilaEstatica* fila, int capacidade);
void enfileirarEstatica(FilaEstatica* fila, Rating valor);
int desenfileirarEstatica(FilaEstatica* fila, Rating* removido);
void limparFilaEstatica(FilaEstatica* fila);

#endif
