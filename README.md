
# ✨ Projeto desenvolvido para disciplina de Algoritmos e Estruturas de Dados

<div align="center" style="background: linear-gradient(135deg, #f5f7fa 0%, #c3cfe2 100%); padding: 2rem; border-radius: 15px; box-shadow: 0 10px 20px rgba(0,0,0,0.1);">

### 👥 Equipe do Projeto

| **Alunos** | **Professor** |
|:----------:|:-------------:|
| <div style="display: flex; flex-wrap: wrap; justify-content: center; gap: 15px; max-width: 600px;"><div style="flex: 1 0 180px;"><a href="https://github.com/msjujubr"><img src="https://github.com/msjujubr.png" width="100" style="border-radius: 50%; box-shadow: 0 0 10px #FF6B6B; border: 2px solid #FF6B6B;"></a><br>**Júlia D'Moura**<br>[![GitHub](https://img.shields.io/badge/@msjujubr-FF6B6B?style=flat-square&logo=github)](https://github.com/msjujubr)</div><div style="flex: 1 0 180px;"><a href="https://github.com/Rutrama"><img src="https://github.com/Rutrama.png" width="100" style="border-radius: 50%; box-shadow: 0 0 10px #4ECDC4; border: 2px solid #4ECDC4;"></a><br>**Arthur Santana**<br>[![GitHub](https://img.shields.io/badge/@Rutrama-4ECDC4?style=flat-square&logo=github)](https://github.com/Rutrama)</div><div style="flex: 1 0 180px;"><a href="https://github.com/ImArthz"><img src="https://github.com/ImArthz.png" width="100" style="border-radius: 50%; box-shadow: 0 0 10px #239A3B; border: 2px solid #239A3B;"></a><br>**Arthur Mendonça**<br>[![GitHub](https://img.shields.io/badge/@ImArthz-239A3B?style=flat-square&logo=github)](https://github.com/ImArthz)</div></div><div style="display: flex; flex-wrap: wrap; justify-content: center; gap: 15px; margin-top: 15px;"><div style="flex: 1 0 180px;"><a href="https://github.com/LuizFernandosq"><img src="https://github.com/LuizFernandosq.png" width="100" style="border-radius: 50%; box-shadow: 0 0 10px #FFD166; border: 2px solid #FFD166;"></a><br>**Luiz Fernando**<br>[![GitHub](https://img.shields.io/badge/@fernando--horita-FFD166?style=flat-square&logo=github)](https://github.com/fernando-horita-siratuti)</div><div style="flex: 1 0 180px;"><a href="https://github.com/alvaroajs"><img src="https://github.com/alvaroajs.png" width="100" style="border-radius: 50%; box-shadow: 0 0 10px #06D6A0; border: 2px solid #06D6A0;"></a><br>**Álvaro Silva**<br>[![GitHub](https://img.shields.io/badge/@alvaroajs-06D6A0?style=flat-square&logo=github)](https://github.com/alvaroajs)</div></div> | <a href="https://github.com/mpiress"><img src="https://github.com/mpiress.png" width="100" style="border-radius: 50%; box-shadow: 0 0 10px #00599C; border: 2px solid #00599C;"></a><br>**Prof. Michel Pires**<br>[![GitHub](https://img.shields.io/badge/@mpiress-00599C?style=flat-square&logo=github)](https://github.com/mpiress) |

</div>

## 📂 ESTRUTURA DO PROJETO
```text
projeto-aeds-quicksort/
├── C/                  # Implementação em C
│   └── main.c
├── C++/                # Implementação em C++
│   └── main.cpp
├── C#/                 # Implementação em C# 
│   └── ConsoleApp1/
│       ├── Program.cs
│       └── Quicksort.csproj
├── julia/              # Implementação em Julia
│   └── main.jl
├── python/             # Implementação em Python
│   └── main.py
└── data/               # Dados compartilhados
    └── ratings.csv     # Dataset obrigatório
```
# 🚀 COMO EXECUTAR



## 🔹 PRÉ-REQUISITOS COMUNS
- Arquivo `ratings.csv` na pasta `data/`
- Formato: `userId,movieId,rating,timestamp`

## 📋 MENU DE IMPLEMENTAÇÕES
```bash
| Linguagem  | Comando de Execução                      | Dependências   |
|------------|------------------------------------------|----------------|
| C          | `./C/quicksort_c`                        | GCC 9.0+       |
| C++        | `./C++/quicksort_cpp`                    | G++ 9.0+       |
| C#         | `dotnet run --project C#/ConsoleApp1`    | .NET 9.0+      |
| Julia      | `julia julia/main.jl`                    | Julia 1.6+     |
| Python     | `python python/main.py`                  | Python 3.8+    |
```
## 🧹 LIMPEZA DE ARQUIVOS TEMPORÁRIOS

### 🔧 Limpeza Geral (todas linguagens)
```bash
# Remove binários, objetos e caches
find . -type d \( -name "bin" -o -name "obj" -o -name "__pycache__" -o -name "*.o" -o -name "*.out" \) -exec rm -rf {} +
```

### 🔍 Limpeza Específica por Linguagem

| Linguagem  | Comando de Limpeza                          |
|------------|---------------------------------------------|
| **C**      | `rm -f C/*.o C/quicksort_c`                 |
| **C++**    | `rm -f C++/*.o C++/quicksort_cpp`           |
| **C#**     | `rm -rf C#/ConsoleApp1/{bin,obj}`           |
| **Julia**  | `rm -f julia/*.jl.*.cov julia/*.jl.mem`     |
| **Python** | `rm -rf python/__pycache__`                 |

### 💡 Dicas Adicionais
1. Para Windows (PowerShell):
   ```powershell
   Remove-Item -Recurse -Force bin, obj, __pycache__
   ```
2. Para limpar todos os arquivos gerados:
   ```bash
   make clean  # Se estiver usando Makefile
   ```

## 📌 DICAS IMPORTANTES

### 🧠 Teste de Consumo de Memória

```bash
# Julia
/usr/bin/time -v julia julia/main.jl

# C
/usr/bin/time -v ./C/quicksort_c

# C++
/usr/bin/time -v ./C++/quicksort_cpp

# C# (Linux/Mac)
dotnet run --project C#/ConsoleApp1 & /usr/bin/time -v wait $!

# Python
/usr/bin/time -v python python/main.py

# Windows (PowerShell)
Measure-Command { dotnet run --project C#/ConsoleApp1 }
```

## 📦 ONDE BAIXAR O DATASET

**Use EXATAMENTE este dataset oficial:**  
👉 [MovieLens 25M Dataset](https://grouplens.org/datasets/movielens/25m/)  
*(Link direto: https://files.grouplens.org/datasets/movielens/ml-25m.zip)*

### Passos:
1. **Acesse o link acima**  
2. **Clique em "ml-25m.zip"** (≈250MB)  
3. **Extraia o arquivo `ratings.csv`** para a pasta `/data` do seu projeto

### Verificação:
```bash
# Confira se o arquivo está correto (primeiras linhas):
head -n 5 data/ratings.csv
# Saída esperada:
# userId,movieId,rating,timestamp
# 1,296,5.0,1147880044
# 1,306,3.5,1147868817
```

