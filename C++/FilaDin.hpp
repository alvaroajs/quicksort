#ifndef FILADIN_HPP
#define FILADIN_HPP

#include <iostream>

class NoFila {
    public:
        int valor;
        NoFila* prox;
    
        NoFila(int v) : valor(v), prox(nullptr) {}
};
    
class FilaDinamica {
    public:
        NoFila* frente;
        NoFila* tras;

        FilaDinamica() : frente(nullptr), tras(nullptr) {}

        void enfileirar(int valor) {
            NoFila* novo = new NoFila(valor);
            if (tras) tras->prox = novo;
            else frente = novo;
            tras = novo;
        }

        void desenfileirar() {
            if (frente) {
                NoFila* temp = frente;
                frente = frente->prox;
                if (!frente) tras = nullptr;
                delete temp;
            }
        }

        void imprimir() {
            NoFila* atual = frente;
            while (atual) {
                std::cout << atual->valor << " ";
                atual = atual->prox;
            }
            std::cout << "\n";
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