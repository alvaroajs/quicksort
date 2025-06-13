#ifndef LISTDIN_HPP
#define LISTDIN_HPP

#include <iostream>

class NoLista {
public:
    float valor;
    NoLista* prox;

    NoLista(float v) : valor(v), prox(nullptr) {}
};

class ListaDinamica {
    public:
        NoLista* inicio;
        ListaDinamica() : inicio(nullptr) {}

        void inserir(float valor) {
            NoLista* novo = new NoLista(valor);
            novo->prox = inicio;
            inicio = novo;
        }

        void remover() {
            if (inicio) {
                NoLista* temp = inicio;
                inicio = inicio->prox;
                delete temp;
            }
        }

        void imprimir() {
            NoLista* atual = inicio;
            while (atual) {
                std::cout << atual->valor << " ";
                atual = atual->prox;
            }
            std::cout << "\n";
        }

        void limpar() {
            NoLista* atual = inicio;
            while (atual) {
                NoLista* temp = atual;
                atual = atual->prox;
                delete temp;
            }
            inicio = nullptr;
        }

        ~ListaDinamica() {
            limpar(); // Liberar memória ao destruir
        }
};

#endif