 ## 🚀 COMO EXECUTAR O PROJETO
 
 ### Estrutura de Pastas Obrigatória:
 ```
 projeto-aeds-quicksort/
 ├── julia/
 │   └── main.jl               # Código principal
 └── data/
     └── ratings.csv           # Arquivo de dados (obrigatório)
 ```

 ### Passo a Passo:
 1. Coloque o arquivo `ratings.csv` dentro da pasta `data/`
 2. Abra o terminal na raiz do projeto (`projeto-aeds-quicksort/`)
 3. Execute o comando:
    ```bash
    julia julia/main.jl
    ```
 
 ### No Menu Interativo:
 - Escolha entre 6 estruturas diferentes:
   | Tipo       | Estática (Vector) | Dinâmica (Linked) |
   |------------|-------------------|-------------------|
   | **Lista**  | VectorList        | LinkedList        |
   | **Pilha**  | VectorStack       | LinkedStack       |
   | **Fila**   | VectorQueue       | LinkedQueue       |
   
 - Selecione a quantidade de registros (100 até 1.000.000)
 - Aguarde a execução e verificação da ordenação
 - Resultados serão salvos em CSV automaticamente

 ### ⚠️ IMPORTANTE:
 - Requer Julia 1.6+ instalado
 - O arquivo `ratings.csv` DEVE estar presente em `data/`
 - Formato do CSV: `userId,movieId,rating,timestamp`
 - Dados de exemplo disponíveis em: [MovieLens Dataset](https://grouplens.org/datasets/movielens/)
# Leitura com memoria RAM
```
/usr/bin/time -v julia julia/main.jl
```
