/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "leitura.h"
#include "quicksort.h"

#include "lista_dinamica.h"
#include "lista_estatica.h"
#include "fila_dinamica.h"
#include "fila_estatica.h"
#include "pilha_dinamica.h"
#include "pilha_estatica.h"

static void ordenar_lista_dinamica(ListaDinamica* lista, int n) {
    Rating* aux = malloc(sizeof(Rating) * n);
    int i = 0;
    for (NoLista* p = lista->inicio; p; p = p->prox) aux[i++] = p->valor;
    quicksort(aux, 0, n - 1);

    limparListaDinamica(lista);
    for (i = 0; i < n; ++i) inserirListaDinamica(lista, aux[i]);
    free(aux);
}

static void ordenar_lista_estatica(ListaEstatica* lista) {
    quicksort(lista->dados, 0, lista->tamanho - 1);
}

static void ordenar_fila_dinamica(FilaDinamica* fila, int n) {
    Rating* aux = malloc(sizeof(Rating) * n);
    int i = 0;
    for (NoFila* p = fila->frente; p; p = p->prox) aux[i++] = p->valor;
    quicksort(aux, 0, n - 1);

    limparFila(fila);
    for (i = 0; i < n; ++i) enfileirar(fila, aux[i]);
    free(aux);
}

static void ordenar_fila_estatica(FilaEstatica* fila) {
    /* Copia para vetor contíguo, ordena e reinsere */
    Rating* aux = malloc(sizeof(Rating) * fila->tamanho);
    int idx = fila->frente;
    for (int i = 0; i < fila->tamanho; ++i) {
        aux[i] = fila->dados[idx];
        idx = (idx + 1) % fila->capacidade;
    }
    quicksort(aux, 0, fila->tamanho - 1);

    limparFilaEstatica(fila);
    for (int i = 0; i < fila->capacidade && i < fila->tamanho; ++i)
        enfileirarEstatica(fila, aux[i]);
    free(aux);
}

static void ordenar_pilha_dinamica(PilhaDinamica* pilha, int n) {
    Rating* aux = malloc(sizeof(Rating) * n);
    Rating tmp;
    int i = 0;
    while (desempilhar(pilha, &tmp)) aux[i++] = tmp;
    quicksort(aux, 0, n - 1);

    /* Reempilha do maior para o menor para que o menor fique no topo */
    for (i = n - 1; i >= 0; --i) empilhar(pilha, aux[i]);
    free(aux);
}

static void ordenar_pilha_estatica(PilhaEstatica* pilha) {
    quicksort(pilha->dados, 0, pilha->topo - 1);

    for (int i = 0; i < pilha->topo / 2; ++i) {
        Rating temp = pilha->dados[i];
        pilha->dados[i] = pilha->dados[pilha->topo - 1 - i];
        pilha->dados[pilha->topo - 1 - i] = temp;
    }
}

int main(void) {
    int tam, opcao, lidos = 0;

    puts("1) Lista Dinamica\n2) Lista Estatica");
    puts("3) Fila Dinamica\n4) Fila Estatica");
    puts("5) Pilha Dinamica\n6) Pilha Estatica");
    printf("Escolha a opcao: ");
    scanf("%d", &opcao);

    printf("Quantidade de registros a ler: ");
    scanf("%d", &tam);

    Rating* dados = ler_ratings("../dataset/ratings.csv", tam, &lidos);
    if (!dados) return 1;

    clock_t inicio, fim;
    double tempo;

    switch (opcao) {
    case 1: { /* Lista Dinâmica */
        ListaDinamica lista;
        inicializarListaDinamica(&lista);
        for (int i = 0; i < lidos; ++i) inserirListaDinamica(&lista, dados[i]);

        inicio = clock();
        ordenar_lista_dinamica(&lista, lidos);
        fim = clock();
        
        limparListaDinamica(&lista);
        break;
    }
    case 2: { /* Lista Estática */
        ListaEstatica lista;
        inicializarListaEstatica(&lista, lidos);
        for (int i = 0; i < lidos; ++i) inserirListaEstatica(&lista, dados[i]);

        inicio = clock();
        ordenar_lista_estatica(&lista);
        fim = clock();

        limparListaEstatica(&lista);
        break;
    }
    case 3: { /* Fila Dinâmica */
        FilaDinamica fila;
        inicializarFilaDinamica(&fila);
        for (int i = 0; i < lidos; ++i) enfileirar(&fila, dados[i]);

        inicio = clock();
        ordenar_fila_dinamica(&fila, lidos);
        fim = clock();

        limparFila(&fila);
        break;
    }
    case 4: { /* Fila Estática */
        FilaEstatica fila;
        inicializarFilaEstatica(&fila, lidos);
        for (int i = 0; i < lidos; ++i) enfileirarEstatica(&fila, dados[i]);

        inicio = clock();
        ordenar_fila_estatica(&fila);
        fim = clock();

        limparFilaEstatica(&fila);
        break;
    }
    case 5: { /* Pilha Dinâmica */
        PilhaDinamica pilha;
        inicializarPilhaDinamica(&pilha);
        for (int i = 0; i < lidos; ++i) empilhar(&pilha, dados[i]);

        inicio = clock();
        ordenar_pilha_dinamica(&pilha, lidos);
        fim = clock();

        limparPilhaDinamica(&pilha);
        break;
    }
    case 6: { /* Pilha Estática */
        PilhaEstatica pilha;
        inicializarPilhaEstatica(&pilha, lidos);
        for (int i = 0; i < lidos; ++i) push(&pilha, dados[i]);

        inicio = clock();
        ordenar_pilha_estatica(&pilha);
        fim = clock();

        limparPilhaEstatica(&pilha);
        break;
    }
    default:
        puts("Opcao invalida!");
        free(dados);
        return 0;
    }

    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.6f s\n", tempo);

    free(dados);
    return 0;
}