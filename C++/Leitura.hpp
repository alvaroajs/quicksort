// Leitura.hpp
#ifndef LEITURA_HPP
#define LEITURA_HPP

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct Rating {
    int usuarioId;
    int movieId;
    float rating; // ou outro tipo, dependendo do que é
    float tempo;       // 4ª coluna
};

std::vector<Rating> LeituraArquivos(int tam) {

    std::ifstream arquivo("dataset/ratings.csv");
    std::vector<Rating> ratings;

    std::string linha;
    int lidos = 0;

    while (lidos < tam && std::getline(arquivo, linha)) {
        std::stringstream ss(linha);
        std::string campo;
        std::vector<std::string> campos;

        while (std::getline(ss, campo, ',')) {
            campos.push_back(campo);
        }

        if (campos.size() >= 4) {
            Rating r;
            r.usuarioId = std::stoi(campos[0]);
            r.movieId    = std::stoi(campos[1]);
            r.rating     = std::stof(campos[2]); // ou std::stoi/cast se for timestamp
            r.tempo      = std::stof(campos[3]);
            ratings.push_back(r);
            lidos++;
        }
    }

    arquivo.close();
    return ratings;

}

#endif
