#ifndef PILHAEST_HPP
#define PILHAEST_HPP

#include <iostream>
#include <vector>
#include "Leitura.hpp"

class PilhaEstatica {
public:
    int topo;
    int capacidade;

    std::vector<Rating> dados;

    PilhaEstatica(int tamanho) : dados(tamanho), topo(0), capacidade(tamanho) {}

    void push(Rating valor) {
        if (cheia()) {
            std::cout << "Erro: Pilha cheia!\n";
            return;
        }
        dados[topo++] = valor;
    }

    void pop() {
        if (vazia()) {
            std::cout << "Erro: Pilha vazia!\n";
            return;
        }
        topo--;
    }

    bool vazia() const {
        return topo == 0;
    }

    bool cheia() const {
        return topo == capacidade;
    }

    void limpar() {
        topo = 0;
        dados.clear();
        dados.resize(capacidade);
    }
};

#endif
