// Tradução inicial do código Julia para C#
// O código implementa estruturas de dados e ordenação de registros de avaliação de filmes

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.IO;

public class Rating
{
    public int UserId { get; set; }
    public int MovieId { get; set; }
    public double RatingValue { get; set; }
    public int Timestamp { get; set; }
}

// Estruturas de dados baseadas em vetor
public class VectorList { public List<Rating> Data = new(); }
public class VectorStack { public List<Rating> Data = new(); }
public class VectorQueue { public List<Rating> Data = new(); }

// Estruturas encadeadas
public class Node
{
    public Rating Data;
    public Node Next;
    public Node(Rating data) { Data = data; }
}

public class LinkedList
{
    public Node Head;
    public int Length = 0;
}

public class LinkedStack
{
    public Node Top;
    public int Length = 0;
}

public class LinkedQueue
{
    public Node Front;
    public Node Rear;
    public int Length = 0;
}

class Program
{
    static void Main()
    {
        Console.WriteLine("\n===============================");
        Console.WriteLine("PROJETO AEDS - ORDENAÇÃO DE DADOS");
        Console.WriteLine("===============================");
        MainMenu();
    }

    static void MainMenu()
    {
        var saveCsv = AskYesNo("Deseja salvar o resultado ordenado em CSV? (s/n): ");

        var inputSizes = new[] { 100, 1000, 10000, 100000, 1000000 , 10000000, 26000000 };
        var structures = new List<(string, Type)>
        {
            ("Lista (Vetor)", typeof(VectorList)),
            ("Lista Encadeada", typeof(LinkedList)),
            ("Pilha (Vetor)", typeof(VectorStack)),
            ("Pilha Encadeada", typeof(LinkedStack)),
            ("Fila (Vetor)", typeof(VectorQueue)),
            ("Fila Encadeada", typeof(LinkedQueue))
        };

        string filename = FindRatingsFile();
        if (filename == null) return;

        while (true)
        {
            Console.WriteLine("\n===============================");
            Console.WriteLine("MENU PRINCIPAL");
            Console.WriteLine("===============================");

            Console.WriteLine("\n📚 Escolha a estrutura de dados:");
            for (int i = 0; i < structures.Count; i++)
                Console.WriteLine($"{i + 1}. {structures[i].Item1}");
            Console.WriteLine("0. Sair");

            Console.Write("\nOpção: ");
            if (!int.TryParse(Console.ReadLine(), out int structChoice) || structChoice < 0 || structChoice > structures.Count)
            {
                Console.WriteLine("Opção inválida!");
                continue;
            }
            if (structChoice == 0) break;

            var (structName, structType) = structures[structChoice - 1];

            Console.WriteLine("\n📏 Escolha o tamanho dos dados:");
            for (int i = 0; i < inputSizes.Length; i++)
                Console.WriteLine($"{i + 1}. {inputSizes[i]} registros");

            Console.Write("\nOpção: ");
            if (!int.TryParse(Console.ReadLine(), out int sizeChoice) || sizeChoice < 1 || sizeChoice > inputSizes.Length)
            {
                Console.WriteLine("Opção inválida!");
                continue;
            }
            int inputSize = inputSizes[sizeChoice - 1];

            Console.WriteLine("\n🚀 Executando:");
            Console.WriteLine("- Estrutura: " + structName);
            Console.WriteLine("- Tamanho: " + inputSize + " registros");

            var ratings = ReadRatings(filename, inputSize);
            SortAndMeasureMultipleTimes(ratings, structType, inputSize, saveCsv);
        }

        Console.WriteLine("\nPrograma encerrado. Até mais! 👋");
    }

    static bool AskYesNo(string message)
    {
        Console.Write(message);
        var response = Console.ReadLine()?.Trim().ToLower();
        return response == "s" || response == "sim";
    }

    static string FindRatingsFile()
{
    // 1. Caminhos prioritários (personalizáveis)
    var possiblePaths = new List<string>
    {
        // Caminho local (dentro da pasta do projeto)
        Path.Combine(Directory.GetCurrentDirectory(), "dataset", "ratings.csv"),
        
        // Caminho relativo (para casos em que o executável está em /bin/)
        Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "dataset", "ratings.csv"),
        
        // Caminho absoluto típico (ex: seu desktop)
        @"C:\Users\Usuario\Desktop\ordenacaoAEDS-main\dataset\ratings.csv",
        
        // Caminho para Linux/WSL (se aplicável)
        "/home/seu_usuario/projetos/ordenacaoAEDS-main/dataset/ratings.csv",
        
        // Adicione outros caminhos comuns aqui...
    };

    // 2. Verifica se uma variável de ambiente define o caminho
    string envPath = Environment.GetEnvironmentVariable("RATINGS_CSV_PATH");
    if (!string.IsNullOrEmpty(envPath))
    {
        possiblePaths.Insert(0, envPath); // Prioriza o caminho da variável de ambiente
    }

    // 3. Varre todos os caminhos possíveis
    foreach (string path in possiblePaths)
    {
        string fullPath = Path.GetFullPath(path); // Normaliza o caminho
        Console.WriteLine($"🔍 Procurando em: {fullPath}");

        if (File.Exists(fullPath))
        {
            Console.WriteLine($"✅ Arquivo encontrado: {fullPath}");
            return fullPath;
        }
    }

    // 4. Se nenhum caminho funcionar, exibe ajuda
    Console.WriteLine("❌ Nenhum caminho válido encontrado para ratings.csv. Tente:");
    Console.WriteLine("- Colocar o arquivo em uma pasta 'dataset' dentro do projeto;");
    Console.WriteLine("- Definir a variável de ambiente 'RATINGS_CSV_PATH';");
    Console.WriteLine("- Verificar se o arquivo existe nos locais:");
    foreach (string path in possiblePaths)
    {
        Console.WriteLine($"  - {Path.GetFullPath(path)}");
    }

    return null;
}

    static List<Rating> ReadRatings(string filename, int maxEntries)
    {
        var ratings = new List<Rating>();
        try
        {
            using var reader = new StreamReader(filename);
            reader.ReadLine(); // skip header
            while (!reader.EndOfStream && ratings.Count < maxEntries)
            {
                var line = reader.ReadLine();
                var parts = line.Split(',');
                if (parts.Length < 4) continue;

                if (int.TryParse(parts[0], out int userId) &&
                    int.TryParse(parts[1], out int movieId) &&
                    double.TryParse(parts[2], NumberStyles.Any, CultureInfo.InvariantCulture, out double rating) &&
                    int.TryParse(parts[3], out int timestamp))
                {
                    ratings.Add(new Rating { UserId = userId, MovieId = movieId, RatingValue = rating, Timestamp = timestamp });
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine("Erro ao ler arquivo: " + ex.Message);
        }
        Console.WriteLine($"📊 Dados carregados: {ratings.Count} registros");
        return ratings;
    }

    static void SortAndMeasureMultipleTimes(List<Rating> ratings, Type structType, int inputSize, bool saveCsv)
{
    string metricFile = "metricas.txt";

    // Cria ou sobrescreve e escreve cabeçalho
    using (var writer = new StreamWriter(metricFile, true))
    {
        writer.WriteLine($"{structType.Name} {inputSize}");
    }

    for (int i = 1; i <= 5; i++)
    {
        var stopwatch = Stopwatch.StartNew();

        var subset = ratings.GetRange(0, Math.Min(inputSize, ratings.Count));
        subset.Sort((a, b) => a.Timestamp.CompareTo(b.Timestamp));

        stopwatch.Stop();
        var elapsed = stopwatch.Elapsed;

        Console.WriteLine($"⏱️ Execução {i}: {FormatTime(elapsed)}");

        // Anexa ao arquivo
        using (var writer = new StreamWriter(metricFile, true))
        {
            writer.WriteLine(elapsed.TotalSeconds.ToString("F6", CultureInfo.InvariantCulture));
        }

        if (saveCsv)
        {
            string filename = $"sorted_{structType.Name}_{inputSize}_run{i}_{DateTime.Now:yyyy-MM-dd_HH-mm-ss}.csv";
            SaveRatings(filename, subset);
        }
    }
}


    static void SaveRatings(string filename, List<Rating> ratings)
    {
        using var writer = new StreamWriter(filename);
        writer.WriteLine("userId,movieId,rating,timestamp");
        foreach (var r in ratings)
            writer.WriteLine($"{r.UserId},{r.MovieId},{r.RatingValue.ToString(CultureInfo.InvariantCulture)},{r.Timestamp}");

        Console.WriteLine($"\n✅ Arquivo {filename} salvo com sucesso.");
        Console.WriteLine($"   Tamanho: {ratings.Count} registros");
    }

    static string FormatTime(TimeSpan elapsed)
    {
        if (elapsed.TotalSeconds >= 1)
            return elapsed.TotalSeconds.ToString("F6") + " s";
        else if (elapsed.TotalMilliseconds >= 1)
            return elapsed.TotalMilliseconds.ToString("F3") + " ms";
        else
            return (elapsed.TotalMilliseconds * 1000).ToString("F0") + " µs";
    }
}
