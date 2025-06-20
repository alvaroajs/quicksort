import time
import sys

# --- IMPORTANTE: Ajustar o limite de recursão ---
# Essencial para lidar com grandes volumes de dados de forma recursiva em Python.
# Ajuste este valor se ainda encontrar o erro 'maximum recursion depth exceeded'.
sys.setrecursionlimit(2_000_000) 

def swap(a, i, j):
    """Auxiliar: troca dois elementos em uma lista pelos índices."""
    a[i], a[j] = a[j], a[i]

def get_numeric_value(item, col_index):
    """Auxiliar: converte o valor de uma coluna para float para comparação."""
    try:
        return float(item[col_index])
    except (ValueError, IndexError):
        # Em caso de erro na conversão (ex: valor não numérico), retorna 0.0 para não quebrar.
        return 0.0

def particao(a, ini, fim, col_index):
    """
    Realiza a partição da sub-lista (a[ini:fim]) usando o esquema Lomuto.
    O pivô é escolhido pela Mediana de Três e posicionado em (fim - 1).
    """
    # A lista 'a' contém linhas do CSV, então acessamos o valor pela col_index.
    # 'fim' é exclusivo, então o último elemento real da sub-lista é 'fim - 1'.
    last_idx = fim - 1

    # --- Mediana de Três para escolha do pivô ---
    # Garante que temos pelo menos 3 elementos para aplicar a Mediana de Três de forma robusta.
    if fim - ini >= 3: 
        mid_idx = (ini + last_idx) // 2

        # Organiza os 3 elementos (ini, mid, last) para que a mediana esteja em 'mid_idx'.
        # Trocas baseadas nos valores numéricos da coluna.
        if get_numeric_value(a[ini], col_index) > get_numeric_value(a[mid_idx], col_index):
            swap(a, ini, mid_idx)
        if get_numeric_value(a[ini], col_index) > get_numeric_value(a[last_idx], col_index):
            swap(a, ini, last_idx)
        if get_numeric_value(a[mid_idx], col_index) > get_numeric_value(a[last_idx], col_index):
            swap(a, mid_idx, last_idx)
        
        # Agora, a mediana está em a[mid_idx]. Movemos ela para a posição do pivô (last_idx).
        swap(a, mid_idx, last_idx)
    # Se a sub-lista tiver menos de 3 elementos, o pivô já é o a[last_idx] (fim-1).
    # Nenhuma troca é necessária para escolher o pivô neste caso simplificado.

    # O pivô para o esquema Lomuto é sempre o último elemento da sub-lista atual.
    # No caso da mediana de 3, já garantimos que a mediana está lá.
    pivo_valor = get_numeric_value(a[last_idx], col_index) 
    
    # 'i' será o índice do último elemento menor ou igual ao pivô.
    # Começa um antes do 'ini' para que 'ini' possa ser o primeiro a ser trocado.
    i = ini - 1 

    # Percorre a sub-lista do 'ini' até o elemento ANTES do pivô ('last_idx').
    for j in range(ini, last_idx):
        if get_numeric_value(a[j], col_index) <= pivo_valor:
            i += 1
            swap(a, i, j) # Move elementos menores/iguais para a seção esquerda
    
    # Coloca o pivô (que está em 'last_idx') em sua posição final correta.
    swap(a, i + 1, last_idx) 
    
    # Retorna o índice onde o pivô foi parar.
    # print(i + 1, "é o índice do pivô após a partição.")
    return i + 1

def quick_sort(a, ini=0, fim=None, col_index=0):
    """
    Função principal do Quick Sort recursivo.
    Ordena a lista 'a' in-place (diretamente).
    """
    fim = fim if fim is not None else len(a)
    
    # Condição de parada da recursão: se a sub-lista tiver 0 ou 1 elemento, ou se ini >= fim.
    if ini < fim: 
        # Particiona a lista e obtém o índice final do pivô.
        pp = particao(a, ini, fim, col_index)
        
        # Chamadas recursivas para as sub-listas:
        # A sub-lista da esquerda vai de 'ini' até 'pp' (excluindo o pivô).
        # A sub-lista da direita vai de 'pp + 1' até 'fim'.
        quick_sort(a, ini, pp, col_index)       
        quick_sort(a, pp + 1, fim, col_index)   
    
    return a # Retorna a lista 'a' que foi modificada in-place


# --- Funções de Leitura de CSV (mantidas do seu código anterior) ---
def read_csv_lines_manually(file_path, num_lines_to_read=None):
    data_lines = []
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            next(file, None) # Pula a primeira linha (cabeçalho)
            line_count = 0
            for line in file:
                cleaned_line = line.strip()
                columns = cleaned_line.split(',')
                data_lines.append(columns)
                line_count += 1
                if num_lines_to_read is not None and line_count == num_lines_to_read:
                    break
    except FileNotFoundError:
        raise
    except Exception as e:
        raise
    return data_lines

# --- Bloco Principal de Execução ---
if __name__ == "__main__":
    csv_file_path = '../dataset/ratings.csv'
    lines_limit = 100
    column_to_sort_by_index = 3

    print(f"Tentando ler as primeiras {lines_limit if lines_limit is not None else 'todas as'} linhas de DADOS de '{csv_file_path}' (ignorando a primeira linha):\n")

    try:
        # Lê os dados do CSV diretamente para 'movie_data'
        movie_data = read_csv_lines_manually(csv_file_path, num_lines_to_read=lines_limit)
        
        if movie_data:
            print(f"Número de linhas de dados lidas: {len(movie_data)}\n")
            print("Primeiras 5 linhas de dados lidas (não ordenado):")
            for i, row in enumerate(movie_data):
                if i < 5:
                    print(row)
                else:
                    break

            # Coluna para ordenar: 'rating' é a TERCEIRA coluna (índice 2)

            print(f"\nIniciando ordenação de {len(movie_data)} linhas pelo 'rating' (coluna índice {column_to_sort_by_index}) usando Mediana de Três (Recursiva e 'Low-Level')...")
            
            start_time = time.time()
            # Chama o Quick Sort para ordenar 'movie_data' in-place.
            # Não é necessário criar uma cópia aqui, pois quick_sort opera in-place.
            quick_sort(movie_data, ini=0, fim=len(movie_data), col_index=column_to_sort_by_index)
            end_time = time.time()
            
            duration = end_time - start_time
            print(f"Ordenação concluída em {duration:.4f} segundos.")

            print("\nPrimeiras 10 linhas de dados ORDENADAS por 'rating':")
            for i, row in enumerate(movie_data): # Imprime 'movie_data' diretamente, pois foi ordenada
                if i < 5:
                    print(row)
                else:
                    break
            
            if len(movie_data) > 1:
                print(f"\nÚltimas 2 linhas do dataset ordenado: {movie_data[-2:]}")
                # Verificação se a ordenação está correta no final da lista
                if get_numeric_value(movie_data[-2], column_to_sort_by_index) <= \
                   get_numeric_value(movie_data[-1], column_to_sort_by_index):
                    print("Verificação básica do final da lista: OK.")
                else:
                    print("Verificação básica do final da lista: ERRO!")

        else:
            print("Nenhuma linha de dados foi lida ou o arquivo pode estar vazio após o cabeçalho.")

    except FileNotFoundError:
        print(f"Erro: O arquivo '{csv_file_path}' não foi encontrado.")
        print("Certifique-se de que o arquivo 'ratings.csv' está na pasta 'dataset'.")
        print("Caso contrário, baixe o arquivo em: https://www.kaggle.com/datasets/garymk/movielens-25m-dataset.")
    except Exception as e:
        print(f"Ocorreu um erro inesperado ao ler ou ordenar o arquivo: {e}")