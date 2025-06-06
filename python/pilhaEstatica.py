import time
import sys

# --- IMPORTANTE: Ajustar o limite de recursão ---
sys.setrecursionlimit(2_000_000) 

# --- IMPLEMENTAÇÃO DAS PILHAS ESTÁTICAS ---

class PilhaEstatica:
    """Implementação de pilha estática usando lista Python com append/pop."""
    
    def __init__(self, tamanho_maximo):
        self.tamanho_maximo = tamanho_maximo
        self.pilha = []  # Lista que funcionará como pilha
    
    def esta_vazia(self):
        """Verifica se a pilha está vazia."""
        return len(self.pilha) == 0
    
    def esta_cheia(self):
        """Verifica se a pilha está cheia."""
        return len(self.pilha) >= self.tamanho_maximo
    
    def empilhar(self, item):
        """Adiciona um item no topo da pilha usando append()."""
        if self.esta_cheia():
            raise OverflowError("Pilha cheia! Não é possível empilhar mais elementos.")
        self.pilha.append(item)
    
    def desempilhar(self):
        """Remove e retorna o item do topo da pilha usando pop()."""
        if self.esta_vazia():
            raise IndexError("Pilha vazia! Não é possível desempilhar.")
        return self.pilha.pop()
    
    def tamanho(self):
        """Retorna o número de elementos na pilha."""
        return len(self.pilha)

# --- FUNÇÕES DE ORDENAÇÃO (mantidas do código original) ---

def swap(a, i, j):
    """Auxiliar: troca dois elementos em uma lista pelos índices."""
    a[i], a[j] = a[j], a[i]

def get_numeric_value(item, col_index):
    """Auxiliar: converte o valor de uma coluna para float para comparação."""
    try:
        return float(item[col_index])
    except (ValueError, IndexError):
        return 0.0

def particao(a, ini, fim, col_index):
    """Realiza a partição da sub-lista usando o esquema Lomuto com Mediana de Três."""
    last_idx = fim - 1

    # Mediana de Três para escolha do pivô
    if fim - ini >= 3: 
        mid_idx = (ini + last_idx) // 2

        if get_numeric_value(a[ini], col_index) > get_numeric_value(a[mid_idx], col_index):
            swap(a, ini, mid_idx)
        if get_numeric_value(a[ini], col_index) > get_numeric_value(a[last_idx], col_index):
            swap(a, ini, last_idx)
        if get_numeric_value(a[mid_idx], col_index) > get_numeric_value(a[last_idx], col_index):
            swap(a, mid_idx, last_idx)
        
        swap(a, mid_idx, last_idx)

    pivo_valor = get_numeric_value(a[last_idx], col_index) 
    i = ini - 1 

    for j in range(ini, last_idx):
        if get_numeric_value(a[j], col_index) <= pivo_valor:
            i += 1
            swap(a, i, j)
    
    swap(a, i + 1, last_idx) 
    return i + 1

def quick_sort(a, ini=0, fim=None, col_index=0):
    """Função principal do Quick Sort recursivo."""
    fim = fim if fim is not None else len(a)
    
    if ini < fim: 
        pp = particao(a, ini, fim, col_index)
        quick_sort(a, ini, pp, col_index)       
        quick_sort(a, pp + 1, fim, col_index)   
    
    return a

# --- FUNÇÃO DE LEITURA DE CSV ---

def read_csv_lines_manually(file_path, num_lines_to_read=None):
    """Lê linhas do CSV e retorna uma lista de listas."""
    data_lines = []
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            next(file, None)  # Pula a primeira linha (cabeçalho)
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

# --- BLOCO PRINCIPAL DE EXECUÇÃO ---

if __name__ == "__main__":
    csv_file_path = '../dataset/ratings.csv'
    lines_limit = 100000
    column_to_sort_by_index = 2  # Coluna do timestamp (4ª coluna)

    print(f"Tentando ler as primeiras {lines_limit} linhas de DADOS de '{csv_file_path}' (ignorando a primeira linha):")

    try:
        # ETAPA 1: Lê dados do CSV e empilha em pilha estática
        movie_data = read_csv_lines_manually(csv_file_path, num_lines_to_read=lines_limit)
        
        if movie_data:
            print(f"Número de linhas de dados lidas: {len(movie_data)}")
            print("Primeiras 5 linhas de dados lidas (não ordenado):")
            for i, row in enumerate(movie_data):
                if i < 5:
                    print(row)
                else:
                    break
            
            # Cria pilha estática e empilha os dados
            pilha_inicial = PilhaEstatica(len(movie_data))
            for linha in movie_data:
                pilha_inicial.empilhar(linha)
            
            # ETAPA 2: Desempilha para vetor estático e ordena
            vetor_estatico = []
            while not pilha_inicial.esta_vazia():
                vetor_estatico.append(pilha_inicial.desempilhar())
            
            print(f"Iniciando ordenação de {len(vetor_estatico)} linhas pelo 'rating' (coluna índice {column_to_sort_by_index}) usando Mediana de Três (Recursiva e 'Low-Level')...")
            
            start_time = time.time()
            quick_sort(vetor_estatico, col_index=column_to_sort_by_index)
            end_time = time.time()
            
            duration = end_time - start_time
            print(f"Ordenação concluída em {duration:.4f} segundos.")

            # ETAPA 3: Empilha resultado em pilha auxiliar
            pilha_auxiliar = PilhaEstatica(len(vetor_estatico))
            for linha in vetor_estatico:
                pilha_auxiliar.empilhar(linha)
            
            # ETAPA 4: Desempilha da auxiliar para pilha final (ordem crescente)
            pilha_final = PilhaEstatica(len(vetor_estatico))
            while not pilha_auxiliar.esta_vazia():
                pilha_final.empilhar(pilha_auxiliar.desempilhar())
            
            # Mostra resultado final desempilhando da pilha final
            resultado_final = []
            while not pilha_final.esta_vazia():
                resultado_final.append(pilha_final.desempilhar())
            
            print("Primeiras 5 linhas de dados ORDENADAS por 'rating':")
            for i, row in enumerate(resultado_final):
                if i < 5:
                    print(row)
                else:
                    break
            
            if len(resultado_final) > 1:
                print(f"Últimas 2 linhas do dataset ordenado: {resultado_final[-2:]}")
                # Verificação se a ordenação está correta no final da lista
                if get_numeric_value(resultado_final[-2], column_to_sort_by_index) <= \
                   get_numeric_value(resultado_final[-1], column_to_sort_by_index):
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