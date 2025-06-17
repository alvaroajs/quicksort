#ifndef LISTDIN_HPP
#define LISTDIN_HPP

#include <iostream>
#include "Leitura.hpp"

class NoLista {
public:
    Rating valor;
    NoLista* prox;

    NoLista(Rating v) : valor(v), prox(nullptr) {}
};

class ListaDinamica {
public:
    NoLista* inicio;

    ListaDinamica() : inicio(nullptr) {}

    void inserir(Rating valor) {
        NoLista* novo = new NoLista(valor);
        novo->prox = inicio;
        inicio = novo;
    }

    void limpar() {
        while (inicio) {
            NoLista* temp = inicio;
            inicio = inicio->prox;
            delete temp;
        }
    }

    ~ListaDinamica() {
        limpar();
    }
};

#endif
