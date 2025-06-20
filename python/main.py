import time
import sys
import os

sys.setrecursionlimit(2_000_000)

class No:
    """Classe que representa um nó para estruturas dinâmicas."""
    def __init__(self, dado):
        self.dado = dado
        self.proximo = None

class VetorEstatico:
    """Implementação de vetor estático (lista Python)."""
    def __init__(self):
        self.data = []
    
    def adicionar(self, item):
        self.data.append(item)
    
    def tamanho(self):
        return len(self.data)
    
    def para_lista(self):
        return self.data.copy()
    
    def de_lista(self, lista):
        self.data = lista.copy()

class VetorDinamico:
    """Implementação de vetor dinâmico usando lista ligada."""
    def __init__(self):
        self.cabeca = None
        self.cauda = None
        self.tamanho = 0
    
    def adicionar(self, dados):
        novo_no = No(dados)
        if not self.cabeca:
            self.cabeca = self.cauda = novo_no
        else:
            self.cauda.proximo = novo_no
            self.cauda = novo_no
        self.tamanho += 1
    
    def para_lista(self):
        resultado = []
        atual = self.cabeca
        while atual:
            resultado.append(atual.dado)
            atual = atual.proximo
        return resultado
    
    def de_lista(self, lista):
        self.cabeca = None
        self.cauda = None
        self.tamanho = 0
        for item in lista:
            self.adicionar(item)

class PilhaEstatica:
    """Implementação de pilha estática usando lista Python."""
    def __init__(self):
        self.pilha = []
    
    def empilhar(self, item):
        self.pilha.append(item)
    
    def desempilhar(self):
        if not self.esta_vazia():
            return self.pilha.pop()
        return None
    
    def esta_vazia(self):
        return len(self.pilha) == 0
    
    def tamanho(self):
        return len(self.pilha)

class PilhaDinamica:
    """Implementação de pilha dinâmica usando lista ligada."""
    def __init__(self):
        self.topo = None
        self._tamanho = 0
    
    def empilhar(self, item):
        novo_no = No(item)
        novo_no.proximo = self.topo
        self.topo = novo_no
        self._tamanho += 1
    
    def desempilhar(self):
        if not self.esta_vazia():
            item = self.topo.dado
            self.topo = self.topo.proximo
            self._tamanho -= 1
            return item
        return None
    
    def esta_vazia(self):
        return self.topo is None
    
    def tamanho(self):
        return self._tamanho

class FilaEstatica:
    """Implementação de fila estática usando lista Python."""
    def __init__(self):
        self.fila = []
    
    def enfileirar(self, item):
        self.fila.append(item)
    
    def desenfileirar(self):
        if not self.esta_vazia():
            return self.fila.pop(0)
        return None
    
    def esta_vazia(self):
        return len(self.fila) == 0
    
    def tamanho(self):
        return len(self.fila)

class FilaDinamica:
    """Implementação de fila dinâmica usando lista ligada."""
    def __init__(self):
        self.inicio = None
        self.fim = None
        self._tamanho = 0
    
    def enfileirar(self, item):
        novo_no = No(item)
        if self.esta_vazia():
            self.inicio = self.fim = novo_no
        else:
            self.fim.proximo = novo_no
            self.fim = novo_no
        self._tamanho += 1
    
    def desenfileirar(self):
        if not self.esta_vazia():
            item = self.inicio.dado
            self.inicio = self.inicio.proximo
            if self.inicio is None:
                self.fim = None
            self._tamanho -= 1
            return item
        return None
    
    def esta_vazia(self):
        return self.inicio is None
    
    def tamanho(self):
        return self._tamanho


def estrutura_para_vetor(estrutura):
    """Converte qualquer estrutura para vetor (lista Python)."""
    vetor = []
    
    if isinstance(estrutura, (VetorEstatico, VetorDinamico)):
        return estrutura.para_lista()
    
    elif isinstance(estrutura, (PilhaEstatica, PilhaDinamica)):
        # Desempilha todos os elementos
        temp = []
        while not estrutura.esta_vazia():
            temp.append(estrutura.desempilhar())
        # Como pilha inverte a ordem, precisamos reverter
        vetor = temp[::-1]
        # Reempilha para manter a estrutura intacta
        for item in vetor:
            estrutura.empilhar(item)
            
    elif isinstance(estrutura, (FilaEstatica, FilaDinamica)):
        # Desenfileira todos os elementos
        while not estrutura.esta_vazia():
            vetor.append(estrutura.desenfileirar())
        # Reenfileira para manter a estrutura intacta
        for item in vetor:
            estrutura.enfileirar(item)
    
    return vetor

def vetor_para_estrutura(vetor, estrutura):
    """Converte vetor de volta para a estrutura original."""
    if isinstance(estrutura, (VetorEstatico, VetorDinamico)):
        estrutura.de_lista(vetor)
    
    elif isinstance(estrutura, (PilhaEstatica, PilhaDinamica)):
        # Limpa a pilha
        while not estrutura.esta_vazia():
            estrutura.desempilhar()
        # Empilha os elementos
        for item in vetor:
            estrutura.empilhar(item)
    
    elif isinstance(estrutura, (FilaEstatica, FilaDinamica)):
        # Limpa a fila
        while not estrutura.esta_vazia():
            estrutura.desenfileirar()
        # Enfileira os elementos
        for item in vetor:
            estrutura.enfileirar(item)

def get_numeric_value(item, col_index):
    """Converte o valor de uma coluna para int para comparação (timestamp)."""
    try:
        return int(item[col_index])
    except (ValueError, IndexError):
        return 0

def swap(a, i, j):
    """Troca dois elementos em uma lista pelos índices."""
    a[i], a[j] = a[j], a[i]

def particao(a, ini, fim, col_index):
    """Realiza a partição usando esquema Lomuto com Mediana de Três."""
    if fim <= ini:
        return ini
        
    last_idx = fim - 1

    # Mediana de Três para escolha do pivô
    if fim - ini >= 3:
        mid_idx = (ini + last_idx) // 2

        # Comparações para encontrar a mediana
        val_ini = get_numeric_value(a[ini], col_index)
        val_mid = get_numeric_value(a[mid_idx], col_index)
        val_last = get_numeric_value(a[last_idx], col_index)

        if val_ini > val_mid:
            swap(a, ini, mid_idx)
        if val_ini > val_last:
            swap(a, ini, last_idx)
        if get_numeric_value(a[mid_idx], col_index) > get_numeric_value(a[last_idx], col_index):
            swap(a, mid_idx, last_idx)
        
        # Move a mediana para o final
        swap(a, mid_idx, last_idx)

    pivo_valor = get_numeric_value(a[last_idx], col_index)
    i = ini - 1

    for j in range(ini, last_idx):
        if get_numeric_value(a[j], col_index) <= pivo_valor:
            i += 1
            if i != j:
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


def read_csv_lines(file_path, num_lines_to_read=None):
    """Lê linhas do CSV e retorna uma lista de listas."""
    data_lines = []
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            next(file, None)  # Pula o cabeçalho
            line_count = 0
            for line in file:
                cleaned_line = line.strip()
                if cleaned_line:
                    columns = cleaned_line.split(',')
                    if len(columns) >= 4:
                        data_lines.append(columns)
                        line_count += 1
                        if num_lines_to_read is not None and line_count == num_lines_to_read:
                            break
    except FileNotFoundError:
        raise
    except Exception as e:
        raise
    return data_lines

def find_ratings_file():
    """Procura pelo arquivo ratings.csv em locais comuns."""
    possible_paths = [
        "ratings.csv",
        "../ratings.csv",
        "../dataset/ratings.csv",
        "../data/ratings.csv",
        "dataset/ratings.csv",
        "data/ratings.csv"
    ]
    
    for path in possible_paths:
        if os.path.isfile(path):
            return path
    
    return None

def ordenar_com_estrutura(dados, tipo_estrutura, coluna_ordenacao):
    """
    Executa o processo completo de ordenação seguindo as 5 etapas:
    1. Leitura do arquivo em uma estrutura de dados
    2. Passa para um vetor
    3. Inicia o tempo de ordenação com quicksort
    4. Termina a ordenação e passa para a estrutura de dados inicial
    5. Termina o tempo e printa na tela
    """
    
    # ETAPA 1: Criar estrutura e adicionar dados
    if tipo_estrutura == "VetorEstatico":
        estrutura = VetorEstatico()
        for linha in dados:
            estrutura.adicionar(linha)
    elif tipo_estrutura == "VetorDinamico":
        estrutura = VetorDinamico()
        for linha in dados:
            estrutura.adicionar(linha)
    elif tipo_estrutura == "PilhaEstatica":
        estrutura = PilhaEstatica()
        for linha in dados:
            estrutura.empilhar(linha)
    elif tipo_estrutura == "PilhaDinamica":
        estrutura = PilhaDinamica()
        for linha in dados:
            estrutura.empilhar(linha)
    elif tipo_estrutura == "FilaEstatica":
        estrutura = FilaEstatica()
        for linha in dados:
            estrutura.enfileirar(linha)
    elif tipo_estrutura == "FilaDinamica":
        estrutura = FilaDinamica()
        for linha in dados:
            estrutura.enfileirar(linha)
    
    
    start_time = time.time() # inicio do tempo
    # ETAPA 2: Converter para vetor
    vetor = estrutura_para_vetor(estrutura)
    
    # ETAPA 3: INÍCIO DO TEMPO + Ordenação
    print(f"Iniciando ordenação de {len(vetor)} linhas pelo 'timestamp' (coluna índice {coluna_ordenacao}) usando Mediana de Três (Recursiva e 'Low-Level')...")
    
    
   
    quick_sort(vetor, col_index=coluna_ordenacao)
    
    vetor_para_estrutura(vetor, estrutura)
    
    end_time = time.time()
    duration = end_time - start_time
    
    print(f"Ordenação concluída em {duration:.4f} segundos.")
    print("Primeiras 5 linhas de dados ORDENADAS por 'timestamp':")
    for i, row in enumerate(vetor[:5]):
        print(row)
    
    if len(vetor) > 1:
        print(f"Últimas 2 linhas do dataset ordenado: {vetor[-2:]}")
        # Verificação se a ordenação está correta no final da lista
        if get_numeric_value(vetor[-2], coluna_ordenacao) <= \
           get_numeric_value(vetor[-1], coluna_ordenacao):
            print("Verificação básica do final da lista: OK.")
        else:
            print("Verificação básica do final da lista: ERRO!")
    
    return duration

def main():
    # Encontrar arquivo
    csv_path = find_ratings_file()
    if not csv_path:
        print("Erro: O arquivo 'ratings.csv' não foi encontrado.")
        print("Certifique-se de que o arquivo 'ratings.csv' está na pasta 'dataset'.")
        return

    estruturas = [
        ("Vetor Estático", "VetorEstatico"),
        ("Vetor Dinâmico", "VetorDinamico"),
        ("Pilha Estática", "PilhaEstatica"),
        ("Pilha Dinâmica", "PilhaDinamica"),
        ("Fila Estática", "FilaEstatica"),
        ("Fila Dinâmica", "FilaDinamica")
    ]
    
    
    tamanhos = [100, 1000, 10000, 100000, 1000000]
    
    # Coluna para ordenação (timestamp)
    coluna_ordenacao = 3
    
    while True:
        # Escolher estrutura
        print("\nEscolha a estrutura de dados:")
        for i, (nome, _) in enumerate(estruturas, 1):
            print(f"{i}. {nome}")
        print("0. Sair")
        
        try:
            escolha = int(input("Opção: "))
            if escolha == 0:
                break
            if not (1 <= escolha <= len(estruturas)):
                print("Opção inválida!")
                continue
            
            nome_estrutura, tipo_estrutura = estruturas[escolha - 1]
            
            # Escolher tamanho
            print(f"\nQuantidade de linhas a processar:")
            for i, tamanho in enumerate(tamanhos, 1):
                print(f"{i}. {tamanho}")
            
            escolha_tamanho = int(input("Opção: "))
            if not (1 <= escolha_tamanho <= len(tamanhos)):
                print("Opção inválida!")
                continue
            
            tamanho_dados = tamanhos[escolha_tamanho - 1]
            
            print(f"\nTentando ler as primeiras {tamanho_dados} linhas de DADOS de '{csv_path}' (ignorando a primeira linha):")
            
            # Carregar dados
            dados = read_csv_lines(csv_path, tamanho_dados)
            
            if not dados:
                print("Erro ao carregar dados!")
                continue
            
            print(f"Número de linhas de dados lidas: {len(dados)}")
            print("Primeiras 5 linhas de dados lidas (não ordenado):")
            for i, row in enumerate(dados[:5]):
                print(row)
            
            # Executar ordenação
            ordenar_com_estrutura(dados, tipo_estrutura, coluna_ordenacao)
            
        except ValueError:
            print("Por favor, digite um número válido!")
        except Exception as e:
            print(f"Ocorreu um erro inesperado ao ler ou ordenar o arquivo: {e}")


if __name__ == "__main__":
    main()