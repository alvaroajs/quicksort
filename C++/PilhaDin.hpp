#ifndef PILHADIN_HPP
#define PILHADIN_HPP

#include <iostream>
#include "Leitura.hpp"

class NoPilha {
public:
    Rating valor;
    NoPilha* prox;

    NoPilha(Rating v) : valor(v), prox(nullptr) {}
};

class PilhaDinamica {
public:
    NoPilha* topo;

    PilhaDinamica() : topo(nullptr) {}

    void empilhar(Rating valor) {
        NoPilha* novo = new NoPilha(valor);
        novo->prox = topo;
        topo = novo;
    }

    void desempilhar() {
        if (topo) {
            NoPilha* temp = topo;
            topo = topo->prox;
            delete temp;
        }
    }

    bool vazia() {
        return topo == nullptr;
    }

    void limpar() {
        while (topo) {
            NoPilha* temp = topo;
            topo = topo->prox;
            delete temp;
        }
    }

    ~PilhaDinamica() {
        limpar();
    }
};

#endif
