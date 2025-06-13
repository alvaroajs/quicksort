#include "Leitura.hpp"
#include "QuickSort.hpp"

#include <chrono>

void ordenarLista(ListaDinamica& lista) {
    vector<float> valores;
    NoLista* atual = lista.inicio;
    while (atual) {
        valores.push_back(atual->valor);
        atual = atual->prox;
    }

    QuickSort::ordenacao(valores);

    lista.limpar(); 
    for (float v : valores) {
        lista.inserir(v);
    }
}

// ---------------- ORDENAR FILA DINÂMICA ----------------
void ordenarFila(FilaDinamica& fila) {
    vector<float> valores;
    NoFila* atual = fila.frente;
    while (atual) {
        valores.push_back(atual->valor);
        atual = atual->prox;
    }

    QuickSort::ordenacao(valores);

    fila.limpar();
    for (float v : valores) {
        fila.enfileirar(v);
    }
}

// ---------------- ORDENAR PILHA DINÂMICA ----------------
void ordenarPilha(PilhaDinamica& pilha) {
    vector<float> valores;
    while (!pilha.vazia()) {
        valores.push_back(pilha.topo->valor);
        pilha.desempilhar();
    }

    QuickSort::ordenacao(valores);

    for (int i = valores.size() - 1; i >= 0; i--) {
        pilha.empilhar(valores[i]);
    }
}

// O QuickSort é um algoritmo que funciona para dados armazenados estaticamente, já que ele depende do acesso rápido à posições para ser eficiente, p 

int main(){
    int tam, opcao;

    ListaDinamica Dlista; ListaEstatica Elista;
    FilaDinamica Dfila; FilaEstatica Efila(tam);
    PilhaDinamica Dpilha; PilhaEstatica Epilha(tam);

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration; 

    std::vector<float> arquivo;

    std::cout << "1) DList, 2) EList, 3) DFil, 4) EFil, 5) DPil, 6) EPil" << std::endl;
    std::cin >> opcao;
    std::cout << "Tamanho: ";
    std::cin >> tam;

    switch (opcao){
        case 1: // Lista Dinâmica
            LeituraArquivos(arquivo, tam);
            for (float valor : arquivo) {
                Dlista.inserir(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarLista(Dlista);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;
        
        case 2: // Lista Estática
            LeituraArquivos(arquivo, tam);
            for (float valor : arquivo) {
                Elista.inserir(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            QuickSort::ordenacao(Elista.dados);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start; 
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;

        case 3: // Fila Dinâmica
            LeituraArquivos(arquivo, tam);
            for (float valor : arquivo) {
                Dfila.enfileirar(valor);
            }
            start = std::chrono::high_resolution_clock::now();
            ordenarFila(Dfila);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;

        case 4: // Fila Estática
            LeituraArquivos(arquivo, tam);
            for (float valor : arquivo) {
                Efila.enfileirar(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            QuickSort::ordenacao(Efila.dados);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;
        
        case 5: // Pilha Dinâmica
            LeituraArquivos(arquivo, tam);
            for (float valor : arquivo) {
                Dpilha.empilhar(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarPilha(Dpilha);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;

        case 6: // Pilha Estática
            LeituraArquivos(arquivo, tam);
            for (float valor : arquivo) {
                Epilha.push(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            QuickSort::ordenacao(Epilha.dados);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;
    }

    return 0;
}