#ifndef PILHADIN_HPP
#define PILHADIN_HPP

// Pilha Dinâmica (não há valor máximo, utiliza ponteiro)

#include <iostream>

class NoPilha {
public:
    float valor;
    NoPilha* prox;

    NoPilha(float v) : valor(v), prox(nullptr) {}
};

class PilhaDinamica {
public:
    NoPilha* topo;

    PilhaDinamica() : topo(nullptr) {}

    void empilhar(float valor) {
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

    void imprimir() {
        NoPilha* atual = topo;
        while (atual) {
            std::cout << atual->valor << " ";
            atual = atual->prox;
        }
        std::cout << "\n";
    }

    void limpar() {
        while (topo) {
            NoPilha* temp = topo;
            topo = topo->prox;
            delete temp;
        }
    }

    bool vazia(){
        return topo == nullptr;
    }

    ~PilhaDinamica() {
        limpar();
    }

};

#endif
