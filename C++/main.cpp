#include "Leitura.hpp"
#include "Ordenacao.hpp"

#include <chrono>

// O QuickSort é um algoritmo que funciona para dados armazenados estaticamente, já que ele depende do acesso rápido à posições para ser eficiente, p 

int main(){
    int tam, opcao;
    
    std::cout << "1) DList, 2) EList, 3) DFil, 4) EFil, 5) DPil, 6) EPil" << std::endl;
    std::cin >> opcao;
    std::cout << "Tamanho: ";
    std::cin >> tam;

    ListaDinamica Dlista; ListaEstatica Elista;
    FilaDinamica Dfila; FilaEstatica Efila(tam);
    PilhaDinamica Dpilha; PilhaEstatica Epilha(tam);

    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::duration<double> duration; 

    std::vector<Rating> arquivo;

  

    switch (opcao){
        case 1: // Lista Dinâmica
            arquivo = LeituraArquivos(tam);
            for (const Rating valor :  arquivo) {
                Dlista.inserir(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarListaDin(Dlista);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;
        
        case 2: // Lista Estática
            arquivo = LeituraArquivos(tam);
            for (const Rating valor : arquivo) {
                Elista.inserir(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarListaEst(Elista);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start; 
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;

        case 3: // Fila Dinâmica
            arquivo = LeituraArquivos(tam);
            for (const Rating valor : arquivo) {
                Dfila.enfileirar(valor);
            }
            start = std::chrono::high_resolution_clock::now();
            ordenarFilaDin(Dfila);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;

        case 4: // Fila Estática
            arquivo = LeituraArquivos(tam);
            for (const Rating valor : arquivo) {
                Efila.enfileirar(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarFilaEst(Efila);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;
        
        case 5: // Pilha Dinâmica
            arquivo = LeituraArquivos(tam);
            for (const Rating valor : arquivo) {
                Dpilha.empilhar(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarPilhaDin(Dpilha);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;

        case 6: // Pilha Estática
            arquivo = LeituraArquivos(tam);
            for (const Rating valor : arquivo) {
                Epilha.push(valor);
            }

            start = std::chrono::high_resolution_clock::now();
            ordenarPilhaEst(Epilha);
            end = std::chrono::high_resolution_clock::now();
    
            duration = end - start;
            std::cout << "Tempo de execução: " << duration.count() << " s\n";
            break;
    }

    return 0;
}