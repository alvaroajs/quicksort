if __name__ == "__main__":
   
    csv_file_path = '../dataset/ratings.csv'
    
    
    lines_limit = 10 # Limite de linhas a serem lidas, None para ler todas as linhas

    print(f"Tentando ler as primeiras {lines_limit if lines_limit is not None else 'todas as'} linhas de DADOS de '{csv_file_path}' (ignorando a primeira linha):\n")

    try:
        
        movie_data = read_csv_lines_manually(csv_file_path, num_lines_to_read=lines_limit)
        
        if movie_data: 
            print("Conteúdo das linhas de dados lidas:")
            for row in movie_data:
                print(row)
        else:
            print("Nenhuma linha de dados foi lida ou o arquivo pode estar vazio após o cabeçalho.")

    except FileNotFoundError:
        print(f"Erro: O arquivo '{csv_file_path}' não foi encontrado.")
        print("Certifique que o arquito ratings.csv esta na pasta datasets.")
        print("Caso contrário baixe o arquivo em: https://www.kaggle.com/datasets/garymk/movielens-25m-dataset.")
    except Exception as e:
        print(f"Ocorreu um erro inesperado ao ler o arquivo: {e}")
        
        
def read_csv_lines_manually(file_path, num_lines_to_read=None):

    data_lines = []
    
    with open(file_path, 'r', encoding='utf-8') as file:
        
        next(file, None) # pula a primeira linha do cabeçalho 
        
        line_count = 0
        for line in file:
            cleaned_line = line.strip()
            columns = cleaned_line.split(',')
            data_lines.append(columns)
            
            line_count += 1
            if num_lines_to_read is not None and line_count >= num_lines_to_read:
                break #
    return data_lines
