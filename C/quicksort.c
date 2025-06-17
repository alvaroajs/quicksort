// quicksort.c
#include "quicksort.h"

void trocar(Rating* a, Rating* b) {
    Rating temp = *a;
    *a = *b;
    *b = temp;
}

int particionar(Rating* arr, int inicio, int fim) {
    float pivo = arr[fim].tempo;
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++) {
        if (arr[j].tempo <= pivo) {
            i++;
            trocar(&arr[i], &arr[j]);
        }
    }
    trocar(&arr[i + 1], &arr[fim]);
    return i + 1;
}

void quicksort(Rating* arr, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionar(arr, inicio, fim);
        quicksort(arr, inicio, pivo - 1);
        quicksort(arr, pivo + 1, fim);
    }
}
