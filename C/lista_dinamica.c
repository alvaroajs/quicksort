#include <stdlib.h>
#include "lista_dinamica.h"

void inicializarListaDinamica(ListaDinamica* lista) {
    lista->inicio = NULL;
}

void inserirListaDinamica(ListaDinamica* lista, Rating valor) {
    NoLista* novo = (NoLista*)malloc(sizeof(NoLista));
    novo->valor = valor;
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

void limparListaDinamica(ListaDinamica* lista) {
    NoLista* atual = lista->inicio;
    while (atual) {
        NoLista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
}
