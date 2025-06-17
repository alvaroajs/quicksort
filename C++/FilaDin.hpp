#ifndef FILADIN_HPP
#define FILADIN_HPP

#include <iostream>
#include "Leitura.hpp"

class NoFila {
public:
    Rating valor;
    NoFila* prox;

    NoFila(Rating v) : valor(v), prox(nullptr) {}
};

class FilaDinamica {
public:
    NoFila* frente;
    NoFila* tras;

    FilaDinamica() : frente(nullptr), tras(nullptr) {}

    void enfileirar(Rating valor) {
        NoFila* novo = new NoFila(valor);
        if (tras) tras->prox = novo;
        else frente = novo;
        tras = novo;
    }

    void limpar() {
        while (frente) {
            NoFila* temp = frente;
            frente = frente->prox;
            delete temp;
        }
        tras = nullptr;
    }

    ~FilaDinamica() {
        limpar();
    }
};

#endif
