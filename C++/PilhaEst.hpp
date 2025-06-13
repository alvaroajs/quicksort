#ifndef PILHAEST_HPP
#define PILHAEST_HPP

#include <iostream>

// Pilha Estática (precisa de um valor máximo para ser armazenado)

#define MAX 100

#include <iostream>
#include <vector>

class PilhaEstatica {
private:
    int topo;
    int capacidade;

public:
    std::vector<float> dados;
    PilhaEstatica(int tamanho) : dados(tamanho), topo(0), capacidade(tamanho) {}
    
    void push(float valor) {
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

    void topoElemento() const {
        if (vazia()) {
            std::cout << "Erro: Pilha vazia!\n";
            return;
        }
        std::cout << "Topo: " << dados[topo - 1] << "\n";
    }

    void tamanho() const {
        std::cout << "Tamanho: " << topo << "\n";
    }

    bool vazia() const {
        return topo == 0;
    }

    bool cheia() const {
        return topo == capacidade;
    }
};
#endif