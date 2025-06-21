/* main.c - VERSÃO CORRIGIDA */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// ====== ESTRUTURA RATING CORRIGIDA ======
typedef struct {
    int userId;      // Corrigido de usuarioId
    int movieId;
    float rating;
    int timestamp;   // Corrigido de tempo (float) para timestamp (int)
} Rating;

// ====== QUICKSORT OTIMIZADO ======
static inline void trocar(Rating* a, Rating* b) {
    Rating temp = *a;
    *a = *b;
    *b = temp;
}

// Insertion sort para arrays pequenos (≤20)
static void insertion_sort(Rating* arr, int inicio, int fim) {
    for (int i = inicio + 1; i <= fim; i++) {
        Rating key = arr[i];
        int key_timestamp = key.timestamp;
        int j = i - 1;
        
        while (j >= inicio && arr[j].timestamp > key_timestamp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Partição com mediana de três
static int particionar(Rating* arr, int inicio, int fim) {
    // Mediana de três para escolher pivô
    int meio = (inicio + fim) / 2;
    
    int a = arr[inicio].timestamp;
    int b = arr[meio].timestamp;
    int c = arr[fim].timestamp;
    
    // Ordena os três valores
    if (a > b) {
        trocar(&arr[inicio], &arr[meio]);
        int temp = a; a = b; b = temp;
    }
    if (a > c) {
        trocar(&arr[inicio], &arr[fim]);
        int temp = a; a = c; c = temp;
    }
    if (b > c) {
        trocar(&arr[meio], &arr[fim]);
    }
    
    // Move mediana para o final
    trocar(&arr[meio], &arr[fim]);
    
    // Partição Lomuto
    int pivo = arr[fim].timestamp;
    int i = inicio;
    
    for (int j = inicio; j < fim; j++) {
        if (arr[j].timestamp <= pivo) {
            trocar(&arr[i], &arr[j]);
            i++;
        }
    }
    
    trocar(&arr[i], &arr[fim]);
    return i;
}

// QuickSort com tail recursion optimization
static void quicksort_otimizado(Rating* arr, int inicio, int fim) {
    while (inicio < fim) {
        // Use insertion sort para arrays pequenos
        if (fim - inicio <= 20) {
            insertion_sort(arr, inicio, fim);
            break;
        }
        
        int pivo = particionar(arr, inicio, fim);
        
        // Tail recursion optimization
        if (pivo - inicio < fim - pivo) {
            quicksort_otimizado(arr, inicio, pivo - 1);
            inicio = pivo + 1;
        } else {
            quicksort_otimizado(arr, pivo + 1, fim);
            fim = pivo - 1;
        }
    }
}

// ====== PARSER CSV OTIMIZADO ======
static Rating* ler_ratings_otimizado(const char* caminho, int max_linhas, int* lidos) {
    FILE* f = fopen(caminho, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        return NULL;
    }
    
    // Buffer maior para I/O mais eficiente
    setvbuf(f, NULL, _IOFBF, 65536);
    
    Rating* vetor = malloc(sizeof(Rating) * max_linhas);
    if (!vetor) {
        fclose(f);
        return NULL;
    }
    
    char linha[1024];
    *lidos = 0;
    
    fgets(linha, sizeof(linha), f); // Pula cabeçalho
    
    while (*lidos < max_linhas && fgets(linha, sizeof(linha), f)) {
        // Parser manual mais eficiente que strtok
        char* ptr = linha;
        char* end;
        
        // userId
        vetor[*lidos].userId = (int)strtol(ptr, &end, 10);
        if (*end != ',') continue;
        ptr = end + 1;
        
        // movieId  
        vetor[*lidos].movieId = (int)strtol(ptr, &end, 10);
        if (*end != ',') continue;
        ptr = end + 1;
        
        // rating
        vetor[*lidos].rating = strtof(ptr, &end);
        if (*end != ',') continue;
        ptr = end + 1;
        
        // timestamp
        vetor[*lidos].timestamp = (int)strtol(ptr, &end, 10);
        
        (*lidos)++;
    }
    
    fclose(f);
    printf("📊 Dados carregados: %d registros\n", *lidos);
    return vetor;
}

// ====== ESTRUTURAS DE DADOS ======

// Lista Dinâmica
typedef struct NoLista {
    Rating valor;
    struct NoLista* prox;
} NoLista;

typedef struct {
    NoLista* inicio;
} ListaDinamica;

static void inicializar_lista_dinamica(ListaDinamica* lista) {
    lista->inicio = NULL;
}

static void inserir_lista_dinamica(ListaDinamica* lista, Rating valor) {
    NoLista* novo = malloc(sizeof(NoLista));
    novo->valor = valor;
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

static void limpar_lista_dinamica(ListaDinamica* lista) {
    NoLista* atual = lista->inicio;
    while (atual) {
        NoLista* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    lista->inicio = NULL;
}

// Lista Estática
typedef struct {
    Rating* dados;
    int tamanho;
    int capacidade;
} ListaEstatica;

static void inicializar_lista_estatica(ListaEstatica* lista, int capacidade) {
    lista->dados = malloc(sizeof(Rating) * capacidade);
    lista->tamanho = 0;
    lista->capacidade = capacidade;
}

static void inserir_lista_estatica(ListaEstatica* lista, Rating valor) {
    if (lista->tamanho < lista->capacidade) {
        lista->dados[lista->tamanho++] = valor;
    }
}

static void limpar_lista_estatica(ListaEstatica* lista) {
    free(lista->dados);
    lista->tamanho = 0;
    lista->capacidade = 0;
}

// Fila Dinâmica
typedef struct NoFila {
    Rating valor;
    struct NoFila* prox;
} NoFila;

typedef struct {
    NoFila* frente;
    NoFila* tras;
} FilaDinamica;

static void inicializar_fila_dinamica(FilaDinamica* fila) {
    fila->frente = NULL;
    fila->tras = NULL;
}

static void enfileirar(FilaDinamica* fila, Rating valor) {
    NoFila* novo = malloc(sizeof(NoFila));
    novo->valor = valor;
    novo->prox = NULL;
    
    if (fila->tras)
        fila->tras->prox = novo;
    else
        fila->frente = novo;
        
    fila->tras = novo;
}

static void limpar_fila_dinamica(FilaDinamica* fila) {
    NoFila* atual = fila->frente;
    while (atual) {
        NoFila* temp = atual;
        atual = atual->prox;
        free(temp);
    }
    fila->frente = fila->tras = NULL;
}

// Fila Estática
typedef struct {
    Rating* dados;
    int frente, tras, tamanho, capacidade;
} FilaEstatica;

static void inicializar_fila_estatica(FilaEstatica* fila, int capacidade) {
    fila->dados = malloc(sizeof(Rating) * capacidade);
    fila->frente = 0;
    fila->tras = 0;
    fila->tamanho = 0;
    fila->capacidade = capacidade;
}

static void enfileirar_estatica(FilaEstatica* fila, Rating valor) {
    if (fila->tamanho < fila->capacidade) {
        fila->dados[fila->tras] = valor;
        fila->tras = (fila->tras + 1) % fila->capacidade;
        fila->tamanho++;
    }
}

static void limpar_fila_estatica(FilaEstatica* fila) {
    free(fila->dados);
    fila->frente = fila->tras = fila->tamanho = fila->capacidade = 0;
}

// Pilha Dinâmica
typedef struct NoPilha {
    Rating valor;
    struct NoPilha* prox;
} NoPilha;

typedef struct {
    NoPilha* topo;
} PilhaDinamica;

static void inicializar_pilha_dinamica(PilhaDinamica* pilha) {
    pilha->topo = NULL;
}

static void empilhar(PilhaDinamica* pilha, Rating valor) {
    NoPilha* novo = malloc(sizeof(NoPilha));
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo;
}

static int desempilhar(PilhaDinamica* pilha, Rating* removido) {
    if (!pilha->topo) return 0;
    NoPilha* temp = pilha->topo;
    *removido = temp->valor;
    pilha->topo = temp->prox;
    free(temp);
    return 1;
}

static void limpar_pilha_dinamica(PilhaDinamica* pilha) {
    Rating lixo;
    while (desempilhar(pilha, &lixo));
}

// Pilha Estática
typedef struct {
    Rating* dados;
    int topo;
    int capacidade;
} PilhaEstatica;

static void inicializar_pilha_estatica(PilhaEstatica* pilha, int capacidade) {
    pilha->dados = malloc(sizeof(Rating) * capacidade);
    pilha->topo = 0;
    pilha->capacidade = capacidade;
}

static void push(PilhaEstatica* pilha, Rating valor) {
    if (pilha->topo < pilha->capacidade) {
        pilha->dados[pilha->topo++] = valor;
    }
}

static void limpar_pilha_estatica(PilhaEstatica* pilha) {
    free(pilha->dados);
    pilha->topo = 0;
    pilha->capacidade = 0;
}

// ====== FUNÇÕES DE ORDENAÇÃO CORRIGIDAS ======

static double ordenar_lista_dinamica(ListaDinamica* lista, const Rating* dados, int n) {
    clock_t inicio = clock(); // ✅ INÍCIO: Inclui inserção na estrutura
    
    // Inserir dados na estrutura
    for (int i = 0; i < n; i++) {
        inserir_lista_dinamica(lista, dados[i]);
    }
    
    // Converter para array, ordenar e reconverter
    Rating* aux = malloc(sizeof(Rating) * n);
    int i = 0;
    for (NoLista* p = lista->inicio; p; p = p->prox) {
        aux[i++] = p->valor;
    }
    
    printf("⏱️  Ordenando dados...\n");
    printf("Iniciando ordenação de %d linhas pelo 'timestamp' usando Mediana de Três...\n", n);
    
    quicksort_otimizado(aux, 0, n - 1);
    
    limpar_lista_dinamica(lista);
    for (i = 0; i < n; i++) {
        inserir_lista_dinamica(lista, aux[i]);
    }
    
    clock_t fim = clock(); // ✅ FIM: Processo completo
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenação concluída em %.9f segundos.\n", tempo);
    free(aux);
    return tempo;
}

static double ordenar_lista_estatica(ListaEstatica* lista, const Rating* dados, int n) {
    clock_t inicio = clock();
    
    // Inserir dados
    for (int i = 0; i < n; i++) {
        inserir_lista_estatica(lista, dados[i]);
    }
    
    printf("⏱️  Ordenando dados...\n");
    printf("Iniciando ordenação de %d linhas pelo 'timestamp' usando Mediana de Três...\n", n);
    
    quicksort_otimizado(lista->dados, 0, lista->tamanho - 1);
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenação concluída em %.9f segundos.\n", tempo);
    return tempo;
}

static double ordenar_fila_dinamica(FilaDinamica* fila, const Rating* dados, int n) {
    clock_t inicio = clock();
    
    // Inserir dados
    for (int i = 0; i < n; i++) {
        enfileirar(fila, dados[i]);
    }
    
    // Converter, ordenar e reconverter
    Rating* aux = malloc(sizeof(Rating) * n);
    int i = 0;
    for (NoFila* p = fila->frente; p; p = p->prox) {
        aux[i++] = p->valor;
    }
    
    printf("⏱️  Ordenando dados...\n");
    printf("Iniciando ordenação de %d linhas pelo 'timestamp' usando Mediana de Três...\n", n);
    
    quicksort_otimizado(aux, 0, n - 1);
    
    limpar_fila_dinamica(fila);
    for (i = 0; i < n; i++) {
        enfileirar(fila, aux[i]);
    }
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenação concluída em %.9f segundos.\n", tempo);
    free(aux);
    return tempo;
}

static double ordenar_fila_estatica(FilaEstatica* fila, const Rating* dados, int n) {
    clock_t inicio = clock();
    
    // Inserir dados
    for (int i = 0; i < n; i++) {
        enfileirar_estatica(fila, dados[i]);
    }
    
    // Converter para array contíguo
    Rating* aux = malloc(sizeof(Rating) * n);
    int idx = fila->frente;
    for (int i = 0; i < n; i++) {  // ✅ CORRIGIDO: usa n em vez de fila->capacidade
        aux[i] = fila->dados[idx];
        idx = (idx + 1) % fila->capacidade;
    }
    
    printf("⏱️  Ordenando dados...\n");
    printf("Iniciando ordenação de %d linhas pelo 'timestamp' usando Mediana de Três...\n", n);
    
    quicksort_otimizado(aux, 0, n - 1);
    
    limpar_fila_estatica(fila);
    inicializar_fila_estatica(fila, n);
    for (int i = 0; i < n; i++) {
        enfileirar_estatica(fila, aux[i]);
    }
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenação concluída em %.9f segundos.\n", tempo);
    free(aux);
    return tempo;
}

static double ordenar_pilha_dinamica(PilhaDinamica* pilha, const Rating* dados, int n) {
    clock_t inicio = clock();
    
    // Inserir dados
    for (int i = 0; i < n; i++) {
        empilhar(pilha, dados[i]);
    }
    
    // Converter, ordenar e reconverter
    Rating* aux = malloc(sizeof(Rating) * n);
    Rating tmp;
    int i = 0;
    while (desempilhar(pilha, &tmp)) {
        aux[i++] = tmp;
    }
    
    printf("⏱️  Ordenando dados...\n");
    printf("Iniciando ordenação de %d linhas pelo 'timestamp' usando Mediana de Três...\n", n);
    
    quicksort_otimizado(aux, 0, n - 1);
    
    // Reempilha em ordem reversa para manter ordenação correta
    for (i = n - 1; i >= 0; i--) {
        empilhar(pilha, aux[i]);
    }
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenação concluída em %.9f segundos.\n", tempo);
    free(aux);
    return tempo;
}

static double ordenar_pilha_estatica(PilhaEstatica* pilha, const Rating* dados, int n) {
    clock_t inicio = clock();
    
    // Inserir dados
    for (int i = 0; i < n; i++) {
        push(pilha, dados[i]);
    }
    
    printf("⏱️  Ordenando dados...\n");
    printf("Iniciando ordenação de %d linhas pelo 'timestamp' usando Mediana de Três...\n", n);
    
    quicksort_otimizado(pilha->dados, 0, pilha->topo - 1);
    
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    
    printf("Ordenação concluída em %.9f segundos.\n", tempo);
    return tempo;
}

// ====== FUNÇÃO PRINCIPAL ======
int main(void) {
    printf("\n==================================================\n");
    printf("PROJETO AEDS - ORDENAÇÃO DE DADOS\n");
    printf("==================================================\n");
    
    int tam, opcao = -1, lidos = 0;
    double tempo;
    while(opcao != 0){
        printf("\n📚 Escolha a estrutura de dados:\n");
        printf("1. Lista (Vetor)\n");
        printf("2. Lista Encadeada\n");
        printf("3. Fila (Vetor)\n");
        printf("4. Fila Encadeada\n");
        printf("5. Pilha (Vetor)\n");
        printf("6. Pilha Encadeada\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        
        printf("\n📏 Quantidade de registros a ler: ");
        printf("\n1- 100");
        printf("\n2- 1000");
        printf("\n3- 10000");
        printf("\n4- 100000");
        printf("\n5- 1000000\n");


        scanf("%d", &tam);
        switch (tam) {
            case 1: tam = 100; break;
            case 2: tam = 1000; break;
            case 3: tam = 10000; break;
            case 4: tam = 100000; break;
            case 5: tam = 1000000; break;
            case 0: return 0; // Sair
            default:
                printf("❌ Opção inválida!\n");
                continue; // Volta para o início do loop
        }
        
        printf("\n📂 Carregando dados...\n");
        Rating* dados = ler_ratings_otimizado("../dataset/ratings.csv", tam, &lidos);
        if (!dados) {
            printf("❌ Erro ao carregar dados!\n");
            return 1;
        }
        
        // Criar arquivo de métricas
        FILE* metricas = fopen("metricas.txt", "a");
        if (metricas) {
            const char* nomes[] = {"", "Lista (Vetor)", "Lista Encadeada", "Fila (Vetor)", 
                                "Fila Encadeada", "Pilha (Vetor)", "Pilha Encadeada"};
            fprintf(metricas, "%s %d\n", nomes[opcao], lidos);
        }
        
        printf("\n🚀 Executando 10 medições...\n");
        
        // 10 execuções para métricas
        for (int exec = 0; exec < 10; exec++) {
            printf("\nTentativa %d...\n", exec + 1);
            
            switch (opcao) {
            case 1: { // Lista Estática
                ListaEstatica lista;
                inicializar_lista_estatica(&lista, lidos);
                tempo = ordenar_lista_estatica(&lista, dados, lidos);
                limpar_lista_estatica(&lista);
                break;
            }
            case 2: { // Lista Dinâmica
                ListaDinamica lista;
                inicializar_lista_dinamica(&lista);
                tempo = ordenar_lista_dinamica(&lista, dados, lidos);
                limpar_lista_dinamica(&lista);
                break;
            }
            case 3: { // Fila Estática
                FilaEstatica fila;
                inicializar_fila_estatica(&fila, lidos);
                tempo = ordenar_fila_estatica(&fila, dados, lidos);
                limpar_fila_estatica(&fila);
                break;
            }
            case 4: { // Fila Dinâmica
                FilaDinamica fila;
                inicializar_fila_dinamica(&fila);
                tempo = ordenar_fila_dinamica(&fila, dados, lidos);
                limpar_fila_dinamica(&fila);
                break;
            }
            case 5: { // Pilha Estática
                PilhaEstatica pilha;
                inicializar_pilha_estatica(&pilha, lidos);
                tempo = ordenar_pilha_estatica(&pilha, dados, lidos);
                limpar_pilha_estatica(&pilha);
                break;
            }
            case 6: { // Pilha Dinâmica
                PilhaDinamica pilha;
                inicializar_pilha_dinamica(&pilha);
                tempo = ordenar_pilha_dinamica(&pilha, dados, lidos);
                limpar_pilha_dinamica(&pilha);
                break;
            }
            default:
                printf("❌ Opção inválida!\n");
                free(dados);
                if (metricas) fclose(metricas);
                return 0;
            }
            
            printf("📋 Tempo de execução: %.9f s\n", tempo);
            
            if (metricas) {
                fprintf(metricas, "%.9f\n", tempo);
            }
        }
        
        if (metricas) {
            fprintf(metricas, "\n");
            fclose(metricas);
        }
        
        free(dados);
    }
    return 0;
}