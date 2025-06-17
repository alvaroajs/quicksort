#ifndef FILA_DINAMICA_H
#define FILA_DINAMICA_H

#include "rating.h"

typedef struct NoFila {
    Rating valor;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* frente;
    NoFila* tras;
} FilaDinamica;

void inicializarFilaDinamica(FilaDinamica* fila);
void enfileirar(FilaDinamica* fila, Rating valor);
void limparFila(FilaDinamica* fila);

#endif