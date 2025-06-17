#ifndef LISTA_DINAMICA_H
#define LISTA_DINAMICA_H

#include "leitura.h"

typedef struct NoLista {
    Rating valor;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* inicio;
} ListaDinamica;

void inicializarListaDinamica(ListaDinamica* lista);
void inserirListaDinamica(ListaDinamica* lista, Rating valor);
void limparListaDinamica(ListaDinamica* lista);

#endif
