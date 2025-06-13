#ifndef QUICKSORT_HPP
#define QUICKSORT_HPP

#include "ListDin.hpp"
#include "ListEst.hpp"

#include "FilaDin.hpp"
#include "FilaEst.hpp"

#include "PilhaDin.hpp"
#include "PilhaEst.hpp"

#include <vector>
#include <algorithm>

using namespace std;


class QuickSort {
public:
    // Ordena um std::vector<float>
    static void ordenacao(std::vector<float>& arr) {
        quickSortVector(arr, 0, arr.size() - 1);
    }


private:
    // QuickSort para vector
    static void quickSortVector(std::vector<float>& arr, float inicio, float fim) {
        if (inicio < fim) {
            float pivo = particionaVector(arr, inicio, fim);
            quickSortVector(arr, inicio, pivo - 1);
            quickSortVector(arr, pivo + 1, fim);
        }
    }

    // Partição para vector
    static float particionaVector(std::vector<float>& arr, float inicio, float fim) {
        float pivo = arr[fim];
        float i = inicio - 1;
        for (float j = inicio; j < fim; j++) {
            if (arr[j] <= pivo) {
                i++;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[fim]);
        return i + 1;
    }

};

#endif