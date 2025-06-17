#ifndef LISTA_ESTATICA_H
#define LISTA_ESTATICA_H

#include "leitura.h"

typedef struct {
    Rating* dados;
    int tamanho;
    int capacidade;
} ListaEstatica;

void inicializarListaEstatica(ListaEstatica* lista, int capacidade);
void inserirListaEstatica(ListaEstatica* lista, Rating valor);
void limparListaEstatica(ListaEstatica* lista);

#endif
