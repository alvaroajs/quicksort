#include <stdlib.h>
#include "lista_estatica.h"

void inicializarListaEstatica(ListaEstatica* lista, int capacidade) {
    lista->dados = (Rating*)malloc(sizeof(Rating) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = capacidade;
}

void inserirListaEstatica(ListaEstatica* lista, Rating valor) {
    if (lista->tamanho < lista->capacidade) {
        lista->dados[lista->tamanho++] = valor;
    }
}

void limparListaEstatica(ListaEstatica* lista) {
    free(lista->dados);
    lista->tamanho = 0;
    lista->capacidade = 0;
}
