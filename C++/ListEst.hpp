#ifndef LISTEST_HPP
#define LISTEST_HPP

#include <iostream>
#include <vector>

class ListaEstatica     {
public:
    std::vector<float> dados;

    ListaEstatica(){}

    void inserir(int valor) {
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