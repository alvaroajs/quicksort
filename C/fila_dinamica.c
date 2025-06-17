// fila_dinamica.c
#include <stdlib.h>
#include "fila_dinamica.h"

void inicializarFilaDinamica(FilaDinamica* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

void enfileirar(FilaDinamica* fila, Rating valor) {
    NoFila* novo = (NoFila*)malloc(sizeof(NoFila));
    novo->valor = valor;
    novo->prox = NULL;

    if (fila->tras)
        fila->tras->prox = novo;
    else
        fila->frente = novo;

    fila->tras = novo;
}

void limparFila(FilaDinamica* fila) {
    NoFila* atual = fila->frente;
    while (atual) {
        NoFila* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    fila->frente = fila->tras = NULL;
}
