import time
import sys

# --- IMPORTANTE: Ajustar o limite de recursão ---
sys.setrecursionlimit(2_000_000) 

# --- IMPLEMENTAÇÃO DA PILHA DINÂMICA ---

class No:
    """Classe que representa um nó da pilha dinâmica."""
    def __init__(self, dado):
        self.dado = dado
        self.proximo = None

class PilhaDinamica:
    """Implementação de pilha dinâmica usando lista ligada."""
    
    def __init__(self):
        self.topo = None
        self._tamanho = 0
    
    def esta_vazia(self):
        """Verifica se a pilha está vazia."""
        return self.topo is None
    
    def empilhar(self, item):
        """Adiciona um item no topo da pilha."""
        novo_no = No(item)
        novo_no.proximo = self.topo
        self.topo = novo_no
        self._tamanho += 1
    
    def desempilhar(self):
        """Remove e retorna o item do topo da pilha."""
        if self.esta_vazia():
            raise IndexError("Pilha vazia! Não é possível desempilhar.")
        
        item = self.topo.dado
        self.topo = self.topo.proximo
        self._tamanho -= 1
        return item
    
    def tamanho(self):
        """Retorna o número de elementos na pilha."""
        return self._tamanho
    
    def ver_topo(self):
        """Retorna o item do topo sem removê-lo."""
        if self.esta_vazia():
            raise IndexError("Pilha vazia!")
        return self.topo.dado

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
    column_to_sort_by_index = 3  # Coluna do rating (3ª coluna, índice 2)

    print(f"Tentando ler as primeiras {lines_limit} linhas de DADOS de '{csv_file_path}' (ignorando a primeira linha):")
    print("Usando PILHA DINÂMICA (lista ligada) em vez de pilha estática\n")

    try:
        # ETAPA 1: Lê dados do CSV e empilha em pilha dinâmica
        movie_data = read_csv_lines_manually(csv_file_path, num_lines_to_read=lines_limit)
        
        if movie_data:
            print(f"Número de linhas de dados lidas: {len(movie_data)}")
            print("Primeiras 5 linhas de dados lidas (não ordenado):")
            for i, row in enumerate(movie_data):
                if i < 5:
                    print(row)
                else:
                    break
            
            # Cria pilha dinâmica e empilha os dados
            print("\nEmpilhando dados na pilha dinâmica...")
            pilha_inicial = PilhaDinamica()
            for linha in movie_data:
                pilha_inicial.empilhar(linha)
            print(f"Tamanho da pilha dinâmica: {pilha_inicial.tamanho()}")
            
            # ETAPA 2: Desempilha para vetor e ordena
            print("\nDesempilhando para vetor...")
            vetor_para_ordenar = []
            while not pilha_inicial.esta_vazia():
                vetor_para_ordenar.append(pilha_inicial.desempilhar())
            
            print(f"\nIniciando ordenação de {len(vetor_para_ordenar)} linhas pelo 'rating' (coluna índice {column_to_sort_by_index}) usando Mediana de Três (Recursiva)...")
            
            start_time = time.time()
            quick_sort(vetor_para_ordenar, col_index=column_to_sort_by_index)
            end_time = time.time()
            
            duration = end_time - start_time
            print(f"Ordenação concluída em {duration:.4f} segundos.")

            # ETAPA 3: Empilha resultado ordenado em pilha auxiliar
            print("\nEmpilhando resultado ordenado em pilha auxiliar...")
            pilha_auxiliar = PilhaDinamica()
            for linha in vetor_para_ordenar:
                pilha_auxiliar.empilhar(linha)
            
            # ETAPA 4: Desempilha da auxiliar para pilha final (inverte a ordem)
            print("Transferindo para pilha final (invertendo ordem)...")
            pilha_final = PilhaDinamica()
            while not pilha_auxiliar.esta_vazia():
                pilha_final.empilhar(pilha_auxiliar.desempilhar())
            
            # Mostra resultado final desempilhando da pilha final
            print("\nDesempilhando resultado final...")
            resultado_final = []
            while not pilha_final.esta_vazia():
                resultado_final.append(pilha_final.desempilhar())
            
            print("\nPrimeiras 5 linhas de dados ORDENADAS por 'rating' (ordem crescente):")
            for i, row in enumerate(resultado_final):
                if i < 5:
                    print(f"  Rating: {row[2]}, UserID: {row[0]}, MovieID: {row[1]}, Timestamp: {row[3]}")
                else:
                    break
            
            if len(resultado_final) > 5:
                print("\nÚltimas 5 linhas de dados ORDENADAS por 'rating' (ordem crescente):")
                for i in range(max(0, len(resultado_final) - 5), len(resultado_final)):
                    row = resultado_final[i]
                    print(f"  Rating: {row[2]}, UserID: {row[0]}, MovieID: {row[1]}, Timestamp: {row[3]}")
            
            # Verificação da ordenação
            print("\nVerificando integridade da ordenação...")
            ordenado_corretamente = True
            for i in range(1, len(resultado_final)):
                if get_numeric_value(resultado_final[i-1], column_to_sort_by_index) > \
                   get_numeric_value(resultado_final[i], column_to_sort_by_index):
                    ordenado_corretamente = False
                    break
            
            if ordenado_corretamente:
                print("✓ Verificação completa: Dados estão corretamente ordenados em ordem CRESCENTE!")
            else:
                print("✗ Erro: Dados não estão corretamente ordenados!")
            
            # Estatísticas finais
            print(f"\nEstatísticas finais:")
            print(f"  - Total de linhas processadas: {len(resultado_final)}")
            print(f"  - Menor rating: {resultado_final[0][2]}")
            print(f"  - Maior rating: {resultado_final[-1][2]}")

        else:
            print("Nenhuma linha de dados foi lida ou o arquivo pode estar vazio após o cabeçalho.")

    except FileNotFoundError:
        print(f"Erro: O arquivo '{csv_file_path}' não foi encontrado.")
        print("Certifique-se de que o arquivo 'ratings.csv' está na pasta 'dataset'.")
        print("Caso contrário, baixe o arquivo em: https://www.kaggle.com/datasets/garymk/movielens-25m-dataset.")
    except Exception as e:
        print(f"Ocorreu um erro inesperado ao ler ou ordenar o arquivo: {e}")