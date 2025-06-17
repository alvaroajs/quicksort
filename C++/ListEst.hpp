#ifndef LISTEST_HPP
#define LISTEST_HPP

#include <iostream>
#include <vector>
#include "Leitura.hpp"

class ListaEstatica {
public:
    std::vector<Rating> dados;

    ListaEstatica() {}

    void inserir(Rating valor) {
        dados.push_back(valor);
    }

    void remover(int pos) {
        dados.erase(dados.begin() + pos);
    }

    void limpar(){
        dados.clear();
    }
}; 

#endif
