#ifndef LEITURA_HPP
#define LEITURA_HPP

#include "QuickSort.hpp"
#include <fstream>
#include <sstream>
#include <string>

// ratings -> timestamp

void LeituraArquivos(vector<float>& vetor, int tam){
    std::ifstream arquivo("dataset/elementos.csv");

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo.\n";
        return;
    }

    int i = 0;
    std::string linha;
    
    do{
        while (std::getline(arquivo, linha)) {
            std::stringstream ss(linha);
            std::string campo;
            std::vector<std::string> campos;

            while (std::getline(ss, campo, ',')) {
                campos.push_back(campo);
                vetor.push_back(stof(campos[3]));
            }
        }
    }while(tam-- != 0);

    arquivo.close();

}
    



#endif