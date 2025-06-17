#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include <vector>
#include <algorithm>
#include "Leitura.hpp"

class QuickSort {
public:
    static void ordenacao(std::vector<Rating>& arr) {
        if(arr.empty()) return;
        quickSort(arr, 0, static_cast<int>(arr.size()) - 1);
    }

private:
    static void quickSort(std::vector<Rating>& arr, int inicio, int fim) {
        if (inicio < fim) {
            int pivo = particiona(arr, inicio, fim);
            quickSort(arr, inicio, pivo - 1);
            quickSort(arr, pivo + 1, fim);
        }
    }

    static int particiona(std::vector<Rating>& arr, int inicio, int fim) {
        Rating pivo = arr[fim];
        int i = inicio - 1;
        for (int j = inicio; j < fim; j++) {
            if (arr[j].tempo <= pivo.tempo) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[fim]);
        return i + 1;
    }
};

#endif
