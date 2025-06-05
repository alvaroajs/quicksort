import time
import sys

# --- IMPORTANTE: Ajustar o limite de recursão ---
sys.setrecursionlimit(2_000_000) 

class No:
    """Classe para representar um nó do vetor dinâmico"""
    def __init__(self, dados):
        self.dados = dados  # Os dados do CSV (lista de strings)
        self.proximo = None  # Ponteiro para o próximo nó

class VetorDinamico:
    """Classe para representar um vetor dinâmico baseado em nós"""
    def __init__(self):
        self.cabeca = None
        self.cauda = None  # Ponteiro para o último nó
        self.tamanho = 0
    
    def adicionar(self, dados):
        """Adiciona um elemento no final do vetor dinâmico"""
        novo_no = No(dados)
        if not self.cabeca:
            self.cabeca = self.cauda = novo_no
        else:
            self.cauda.proximo = novo_no
            self.cauda = novo_no
        self.tamanho += 1
    
    def para_vetor_estatico(self):
        """Converte o vetor dinâmico para vetor estático (Python list)"""
        if self.tamanho == 0:
            return []
        
        resultado = [None] * self.tamanho
        atual = self.cabeca
        i = 0
        while atual:
            resultado[i] = atual.dados
            atual = atual.proximo
            i += 1
        return resultado
    
    def de_vetor_estatico(self, vetor_estatico):
        """Reconstrói o vetor dinâmico a partir de um vetor estático"""
        # Limpa o vetor dinâmico atual
        self.cabeca = None
        self.cauda = None
        self.tamanho = 0
        
        if not vetor_estatico:
            return
        
        # Reconstrói de forma otimizada
        self.cabeca = No(vetor_estatico[0])
        self.cauda = self.cabeca
        self.tamanho = 1
        
        for i in range(1, len(vetor_estatico)):
            novo_no = No(vetor_estatico[i])
            self.cauda.proximo = novo_no
            self.cauda = novo_no
            self.tamanho += 1
    
    def __len__(self):
        return self.tamanho

def obter_valor_numerico(item, indice_coluna):
    """Auxiliar: converte o valor de uma coluna para float para comparação."""
    try:
        return float(item[indice_coluna])
    except (ValueError, IndexError):
        return 0.0

def trocar(a, i, j):
    """Auxiliar: troca dois elementos em uma lista pelos índices."""
    if i != j:
        a[i], a[j] = a[j], a[i]

def particao(a, ini, fim, indice_coluna):
    """
    Realiza a partição da sub-lista (a[ini:fim]) usando o esquema Lomuto.
    O pivô é escolhido pela Mediana de Três e posicionado em (fim - 1).
    """
    ultimo_indice = fim - 1

    # --- Mediana de Três para escolha do pivô ---
    if fim - ini >= 3: 
        meio_indice = (ini + ultimo_indice) // 2

        # Organiza os 3 elementos (ini, meio, ultimo) para que a mediana esteja em 'meio_indice'
        if obter_valor_numerico(a[ini], indice_coluna) > obter_valor_numerico(a[meio_indice], indice_coluna):
            trocar(a, ini, meio_indice)
        if obter_valor_numerico(a[ini], indice_coluna) > obter_valor_numerico(a[ultimo_indice], indice_coluna):
            trocar(a, ini, ultimo_indice)
        if obter_valor_numerico(a[meio_indice], indice_coluna) > obter_valor_numerico(a[ultimo_indice], indice_coluna):
            trocar(a, meio_indice, ultimo_indice)
        
        # Agora, a mediana está em a[meio_indice]. Movemos ela para a posição do pivô (ultimo_indice)
        trocar(a, meio_indice, ultimo_indice)

    # O pivô para o esquema Lomuto é sempre o último elemento da sub-lista atual
    valor_pivo = obter_valor_numerico(a[ultimo_indice], indice_coluna)
    
    # 'i' será o índice do último elemento menor ou igual ao pivô
    i = ini - 1 

    # Percorre a sub-lista do 'ini' até o elemento ANTES do pivô ('ultimo_indice')
    for j in range(ini, ultimo_indice):
        if obter_valor_numerico(a[j], indice_coluna) <= valor_pivo:
            i += 1
            trocar(a, i, j)
    
    # Coloca o pivô (que está em 'ultimo_indice') em sua posição final correta
    trocar(a, i + 1, ultimo_indice)
    
    return i + 1

def quick_sort(a, ini=0, fim=None, indice_coluna=0):
    """
    Função principal do Quick Sort recursivo.
    Ordena a lista 'a' in-place (diretamente).
    """
    fim = fim if fim is not None else len(a)
    
    if ini < fim: 
        pp = particao(a, ini, fim, indice_coluna)
        quick_sort(a, ini, pp, indice_coluna)       
        quick_sort(a, pp + 1, fim, indice_coluna)   
    
    return a

def ler_csv_para_vetor_dinamico(caminho_arquivo, num_linhas_para_ler=None):
    """Lê o arquivo CSV diretamente para um vetor dinâmico"""
    vetor_dinamico = VetorDinamico()
    
    try:
        with open(caminho_arquivo, 'r', encoding='utf-8') as arquivo:
            next(arquivo, None)  # Pula a primeira linha (cabeçalho)
            contador_linhas = 0
            
            for linha in arquivo:
                linha_limpa = linha.strip()
                colunas = linha_limpa.split(',')
                vetor_dinamico.adicionar(colunas)
                contador_linhas += 1
                if num_linhas_para_ler is not None and contador_linhas == num_linhas_para_ler:
                    break
                        
    except FileNotFoundError:
        raise
    except Exception as e:
        raise
    return vetor_dinamico

# --- Bloco Principal de Execução ---
if __name__ == "__main__":
    caminho_csv = '../dataset/ratings.csv'
    limite_linhas = 100000

    print(f"Tentando ler as primeiras {limite_linhas if limite_linhas is not None else 'todas as'} linhas de DADOS de '{caminho_csv}' (ignorando a primeira linha):")

    try:
        # Lê os dados do CSV diretamente em vetor dinâmico
        dados_filme_dinamico = ler_csv_para_vetor_dinamico(caminho_csv, num_linhas_para_ler=limite_linhas)
        
        if len(dados_filme_dinamico) > 0:
            print(f"Número de linhas de dados lidas: {len(dados_filme_dinamico)}")

            # Converte vetor dinâmico para vetor estático
            dados_filme_estatico = dados_filme_dinamico.para_vetor_estatico()
            
            print("Primeiras 5 linhas de dados lidas (não ordenado):")
            for i, linha in enumerate(dados_filme_estatico[:5]):
                print(linha)

            # Executa Quick Sort no vetor estático
            indice_coluna_ordenacao = 1
            print(f"Iniciando ordenação de {len(dados_filme_estatico)} linhas pelo 'rating' (coluna índice {indice_coluna_ordenacao}) usando Mediana de Três (Recursiva e 'Low-Level')...")
            
            tempo_inicio = time.time()
            quick_sort(dados_filme_estatico, ini=0, fim=len(dados_filme_estatico), indice_coluna=indice_coluna_ordenacao)
            tempo_fim = time.time()
            
            duracao = tempo_fim - tempo_inicio
            print(f"Ordenação concluída em {duracao:.4f} segundos.")

            # Converte vetor estático de volta para vetor dinâmico
            dados_filme_dinamico.de_vetor_estatico(dados_filme_estatico)

            print("Primeiras 5 linhas de dados ORDENADAS por 'rating':")
            for i, linha in enumerate(dados_filme_estatico[:5]):
                print(linha)
            
            if len(dados_filme_estatico) > 1:
                print(f"Últimas 2 linhas do dataset ordenado: {dados_filme_estatico[-2:]}")
                # Verificação se a ordenação está correta no final da lista
                if obter_valor_numerico(dados_filme_estatico[-2], indice_coluna_ordenacao) <= \
                   obter_valor_numerico(dados_filme_estatico[-1], indice_coluna_ordenacao):
                    print("Verificação básica do final da lista: OK.")
                else:
                    print("Verificação básica do final da lista: ERRO!")

        else:
            print("Nenhuma linha de dados foi lida ou o arquivo pode estar vazio após o cabeçalho.")

    except FileNotFoundError:
        print(f"Erro: O arquivo '{caminho_csv}' não foi encontrado.")
        print("Certifique-se de que o arquivo 'ratings.csv' está na pasta 'dataset'.")
        print("Caso contrário, baixe o arquivo em: https://www.kaggle.com/datasets/garymk/movielens-25m-dataset.")
    except Exception as e:
        print(f"Ocorreu um erro inesperado ao ler ou ordenar o arquivo: {e}")