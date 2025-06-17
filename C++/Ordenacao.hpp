#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include <vector>
#include "QuickSort.hpp"
#include "ListEst.hpp"
#include "ListDin.hpp"
#include "FilaEst.hpp"
#include "FilaDin.hpp"
#include "PilhaEst.hpp"
#include "PilhaDin.hpp"

// Lista Estática
void ordenarListaEst(ListaEstatica& lista) {
    QuickSort::ordenacao(lista.dados);
}

// Lista Dinâmica
void ordenarListaDin(ListaDinamica& lista) {
    std::vector<Rating> aux;
    NoLista* atual = lista.inicio;
    while (atual) {
        aux.push_back(atual->valor);
        atual = atual->prox;
    }

    QuickSort::ordenacao(aux);

    lista.limpar();
    for (const auto& r : aux) {
        lista.inserir(r);
    }
}

// Fila Estática
void ordenarFilaEst(FilaEstatica& fila) {
    std::vector<Rating> aux;
    int idx = fila.frente;
    for (int i = 0; i < fila.tamanhoAtual; ++i) {
        aux.push_back(fila.dados[idx]);
        idx = (idx + 1) % fila.capacidade;
    }

    QuickSort::ordenacao(aux);

    fila.limpar();
    for (const auto& r : aux) {
        fila.enfileirar(r);
    }
}

// Fila Dinâmica
void ordenarFilaDin(FilaDinamica& fila) {
    std::vector<Rating> aux;
    NoFila* atual = fila.frente;
    while (atual) {
        aux.push_back(atual->valor);
        atual = atual->prox;
    }

    QuickSort::ordenacao(aux);

    fila.limpar();
    for (const auto& r : aux) {
        fila.enfileirar(r);
    }
}

void ordenarPilhaEst(PilhaEstatica& pilha) {
    std::vector<Rating> aux;

    for (int i = 0; i < pilha.topo; ++i)
        aux.push_back(pilha.dados[i]);

    QuickSort::ordenacao(aux);

    pilha.limpar();

    // Inserir do maior para o menor para que o menor fique no topo
    for (int i = static_cast<int>(aux.size()) - 1; i >= 0; --i) {
        pilha.push(aux[i]);
    }
}

void ordenarPilhaDin(PilhaDinamica& pilha) {
    std::vector<Rating> aux;

    while (!pilha.vazia()) {
        aux.push_back(pilha.topo->valor);
        pilha.desempilhar();
    }

    QuickSort::ordenacao(aux);

    // Inserir do maior para o menor para que o menor fique no topo
    for (int i = static_cast<int>(aux.size()) - 1; i >= 0; --i) {
        pilha.empilhar(aux[i]);
    }
}

#endif
