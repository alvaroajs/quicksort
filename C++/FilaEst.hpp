#include <iostream>
#include <vector>


class FilaEstatica {
    private:
        int frente;
        int tras;
        int tamanhoAtual;
        int capacidade;
    
    public:
        std::vector<float> dados;       

        FilaEstatica(int tamanho) 
            : dados(tamanho), frente(0), tras(0), tamanhoAtual(0), capacidade(tamanho) {}
    
        void enfileirar(float valor) {
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
    
        void frenteElemento() const {
            if (vazia()) {
                std::cout << "Erro: Fila vazia!\n";
                return;
            }
            std::cout << "Frente: " << dados[frente] << "\n";
        }
    
        void tamanho() const {
            std::cout << "Tamanho: " << tamanhoAtual << "\n";
        }
    
        bool vazia() const {
            return tamanhoAtual == 0;
        }
    
        bool cheia() const {
            return tamanhoAtual == capacidade;
        }
};
