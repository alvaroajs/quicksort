#ifndef FILAEST_HPP
#define FILAEST_HPP

#include <iostream>
#include <vector>
#include "Leitura.hpp"

class FilaEstatica {
public:
    int frente;
    int tras;
    int tamanhoAtual;
    int capacidade;

    std::vector<Rating> dados;

    FilaEstatica(int tamanho)
        : dados(tamanho), frente(0), tras(0), tamanhoAtual(0), capacidade(tamanho) {}

    void enfileirar(Rating valor) {
        if (cheia()) {
            std::cout << "Erro: Fila cheia!\n";
            return;
        }
        dados[tras] = valor;
        tras = (tras + 1) % capacidade;
        tamanhoAtual++;
    }

    void desenfileirar() {
        if (vazia()) {
            std::cout << "Erro: Fila vazia!\n";
            return;
        }
        frente = (frente + 1) % capacidade;
        tamanhoAtual--;
    }

    void limpar() {
        frente = tras = tamanhoAtual = 0;
        dados.clear();
        dados.resize(capacidade);
    }

    bool vazia() const {
        return tamanhoAtual == 0;
    }

    bool cheia() const {
        return tamanhoAtual == capacidade;
    }
};

#endif
