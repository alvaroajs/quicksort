// leitura.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leitura.h"

#define LINHA_MAX 1024

Rating* ler_ratings(const char* caminho, int max_linhas, int* lidos) {
    FILE* f = fopen(caminho, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }

    Rating* vetor = malloc(sizeof(Rating) * max_linhas);
    if (!vetor) {
        fclose(f);
        return NULL;
    }

    char linha[LINHA_MAX];
    *lidos = 0;

    fgets(linha, LINHA_MAX, f); // Pula o cabeçalho

    while (*lidos < max_linhas && fgets(linha, LINHA_MAX, f)) {
        char* token = strtok(linha, ",");
        if (!token) continue;
        vetor[*lidos].usuarioId = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        vetor[*lidos].movieId = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        vetor[*lidos].rating = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        vetor[*lidos].tempo = atol(token);

        (*lidos)++;
    }

    fclose(f);
    return vetor;
}
