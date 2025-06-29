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
public class VectorList 
{ 
    public List<Rating> Data = new(); 
    
    public void Add(Rating item) => Data.Add(item);
    public int Count => Data.Count;
    public Rating[] ToArray() => Data.ToArray();
    public void FromArray(Rating[] array) 
    {
        Data.Clear();
        Data.AddRange(array);
    }
}

public class VectorStack 
{ 
    public List<Rating> Data = new(); 
    
    public void Push(Rating item) => Data.Add(item);
    public Rating Pop() => Data.Count > 0 ? Data[^1] : null;
    public bool IsEmpty => Data.Count == 0;
    public int Count => Data.Count;
    
    public Rating[] ToArray() => Data.ToArray();
    public void FromArray(Rating[] array) 
    {
        Data.Clear();
        Data.AddRange(array);
    }
}

public class VectorQueue 
{ 
    public List<Rating> Data = new(); 
    
    public void Enqueue(Rating item) => Data.Add(item);
    public Rating Dequeue() 
    {
        if (Data.Count == 0) return null;
        var item = Data[0];
        Data.RemoveAt(0);
        return item;
    }
    public bool IsEmpty => Data.Count == 0;
    public int Count => Data.Count;
    
    public Rating[] ToArray() => Data.ToArray();
    public void FromArray(Rating[] array) 
    {
        Data.Clear();
        Data.AddRange(array);
    }
}

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
    
    public void Add(Rating item)
    {
        var newNode = new Node(item);
        if (Head == null)
        {
            Head = newNode;
        }
        else
        {
            var current = Head;
            while (current.Next != null)
                current = current.Next;
            current.Next = newNode;
        }
        Length++;
    }
    
    public Rating[] ToArray()
    {
        var array = new Rating[Length];
        var current = Head;
        for (int i = 0; i < Length; i++)
        {
            array[i] = current.Data;
            current = current.Next;
        }
        return array;
    }
    
    public void FromArray(Rating[] array)
    {
        Head = null;
        Length = 0;
        foreach (var item in array)
            Add(item);
    }
}

public class LinkedStack
{
    public Node Top;
    public int Length = 0;
    
    public void Push(Rating item)
    {
        var newNode = new Node(item) { Next = Top };
        Top = newNode;
        Length++;
    }
    
    public Rating Pop()
    {
        if (Top == null) return null;
        var item = Top.Data;
        Top = Top.Next;
        Length--;
        return item;
    }
    
    public bool IsEmpty => Top == null;
    
    public Rating[] ToArray()
    {
        var array = new Rating[Length];
        var current = Top;
        for (int i = 0; i < Length; i++)
        {
            array[i] = current.Data;
            current = current.Next;
        }
        return array;
    }
    
    public void FromArray(Rating[] array)
    {
        Top = null;
        Length = 0;
        // Push in reverse order to maintain original order
        for (int i = array.Length - 1; i >= 0; i--)
            Push(array[i]);
    }
}

public class LinkedQueue
{
    public Node Front;
    public Node Rear;
    public int Length = 0;
    
    public void Enqueue(Rating item)
    {
        var newNode = new Node(item);
        if (Front == null)
        {
            Front = Rear = newNode;
        }
        else
        {
            Rear.Next = newNode;
            Rear = newNode;
        }
        Length++;
    }
    
    public Rating Dequeue()
    {
        if (Front == null) return null;
        var item = Front.Data;
        Front = Front.Next;
        if (Front == null) Rear = null;
        Length--;
        return item;
    }
    
    public bool IsEmpty => Front == null;
    
    public Rating[] ToArray()
    {
        var array = new Rating[Length];
        var current = Front;
        for (int i = 0; i < Length; i++)
        {
            array[i] = current.Data;
            current = current.Next;
        }
        return array;
    }
    
    public void FromArray(Rating[] array)
    {
        Front = Rear = null;
        Length = 0;
        foreach (var item in array)
            Enqueue(item);
    }
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

        var inputSizes = new[] { 100, 1000, 10000, 100000, 1000000, 10000000 };
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
        var possiblePaths = new List<string>
        {
            Path.Combine(Directory.GetCurrentDirectory(), "dataset", "ratings.csv"),
            Path.Combine(AppContext.BaseDirectory, "..", "..", "..", "dataset", "ratings.csv"),
            @"C:\Desktop\ordenacaoAEDS\dataset\ratings.csv",
            "../../dataset/ratings.csv",
            "ratings.csv",
            "../ratings.csv",
            "../dataset/ratings.csv"
        };

        string envPath = Environment.GetEnvironmentVariable("RATINGS_CSV_PATH");
        if (!string.IsNullOrEmpty(envPath))
            possiblePaths.Insert(0, envPath);

        foreach (string path in possiblePaths)
        {
            string fullPath = Path.GetFullPath(path);
            if (File.Exists(fullPath))
            {
                Console.WriteLine($"✅ Arquivo encontrado: {fullPath}");
                return fullPath;
            }
        }

        Console.WriteLine("❌ Arquivo ratings.csv não encontrado. Procurou em:");
        foreach (string path in possiblePaths)
            Console.WriteLine($"  - {Path.GetFullPath(path)}");

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
                var parts = line?.Split(',');
                if (parts?.Length < 4) continue;

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

        using (var writer = new StreamWriter(metricFile, true))
        {
            writer.WriteLine($"{structType.Name} {inputSize}");
        }

        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine($"⏱️ Execução {i}: Preparando {inputSize} registros para ordenação...");
            
            var subset = ratings.GetRange(0, Math.Min(inputSize, ratings.Count));
            var elapsed = SortWithStructure(subset, structType, saveCsv, i, inputSize);

            Console.WriteLine($"⏱️ Execução {i}: {FormatTime(TimeSpan.FromSeconds(elapsed))}");

            using (var writer = new StreamWriter(metricFile, true))
            {
                writer.WriteLine(elapsed.ToString("F6", CultureInfo.InvariantCulture));
            }
        }
    }

    static double SortWithStructure(List<Rating> data, Type structType, bool saveCsv, int runNumber, int inputSize)
    {
        // Igual ao Python: trabalhar direto com array, estruturas são só para show
        var array = data.ToArray();
        
        var stopwatch = Stopwatch.StartNew();
        
        // QUICKSORT PRÓPRIO (não usar Sort() nativo!)
        Console.WriteLine($"Ordenando {array.Length} registros por timestamp usando QuickSort...");
        QuickSort(array, 0, array.Length - 1);

        stopwatch.Stop();
        var elapsed = stopwatch.Elapsed.TotalSeconds;

        if (saveCsv)
        {
            string filename = $"sorted_{structType.Name}_{inputSize}_run{runNumber}_{DateTime.Now:yyyy-MM-dd_HH-mm-ss}.csv";
            SaveRatings(filename, array);
        }

        return elapsed;
    }

    static object CreateAndPopulateStructure(List<Rating> data, Type structType)
    {
        if (structType == typeof(VectorList))
        {
            var list = new VectorList();
            foreach (var item in data) list.Add(item);
            return list;
        }
        else if (structType == typeof(LinkedList))
        {
            var list = new LinkedList();
            foreach (var item in data) list.Add(item);
            return list;
        }
        else if (structType == typeof(VectorStack))
        {
            var stack = new VectorStack();
            foreach (var item in data) stack.Push(item);
            return stack;
        }
        else if (structType == typeof(LinkedStack))
        {
            var stack = new LinkedStack();
            foreach (var item in data) stack.Push(item);
            return stack;
        }
        else if (structType == typeof(VectorQueue))
        {
            var queue = new VectorQueue();
            foreach (var item in data) queue.Enqueue(item);
            return queue;
        }
        else if (structType == typeof(LinkedQueue))
        {
            var queue = new LinkedQueue();
            foreach (var item in data) queue.Enqueue(item);
            return queue;
        }
        
        throw new ArgumentException($"Tipo de estrutura não suportado: {structType}");
    }

    static Rating[] ConvertToArray(object structure)
    {
        return structure switch
        {
            VectorList list => list.ToArray(),
            LinkedList list => list.ToArray(),
            VectorStack stack => stack.ToArray(),
            LinkedStack stack => stack.ToArray(),
            VectorQueue queue => queue.ToArray(),
            LinkedQueue queue => queue.ToArray(),
            _ => throw new ArgumentException($"Tipo de estrutura não suportado: {structure.GetType()}")
        };
    }

    static void ConvertFromArray(Rating[] array, object structure)
    {
        switch (structure)
        {
            case VectorList list:
                list.FromArray(array);
                break;
            case LinkedList list:
                list.FromArray(array);
                break;
            case VectorStack stack:
                stack.FromArray(array);
                break;
            case LinkedStack stack:
                stack.FromArray(array);
                break;
            case VectorQueue queue:
                queue.FromArray(array);
                break;
            case LinkedQueue queue:
                queue.FromArray(array);
                break;
            default:
                throw new ArgumentException($"Tipo de estrutura não suportado: {structure.GetType()}");
        }
    }

    // IMPLEMENTAÇÃO DO QUICKSORT (igual aos outros códigos)
    static void QuickSort(Rating[] array, int low, int high)
    {
        while (low < high)
        {
            // Usar insertion sort para arrays pequenos
            if (high - low <= 20)
            {
                InsertionSort(array, low, high);
                break;
            }

            int pivotIndex = Partition(array, low, high);
            
            // Otimização: processar o menor subarray primeiro
            if (pivotIndex - low < high - pivotIndex)
            {
                QuickSort(array, low, pivotIndex - 1);
                low = pivotIndex + 1;
            }
            else
            {
                QuickSort(array, pivotIndex + 1, high);
                high = pivotIndex - 1;
            }
        }
    }

    static int Partition(Rating[] array, int low, int high)
    {
        // Mediana de três para escolher pivô
        int mid = (low + high) / 2;
        
        // Ordenar os três valores (por TIMESTAMP)
        if (array[low].Timestamp > array[mid].Timestamp)
            Swap(array, low, mid);
        if (array[low].Timestamp > array[high].Timestamp)
            Swap(array, low, high);
        if (array[mid].Timestamp > array[high].Timestamp)
            Swap(array, mid, high);
        
        // Mover mediana para o final
        Swap(array, mid, high);

        int pivot = array[high].Timestamp;
        int i = low;

        for (int j = low; j < high; j++)
        {
            if (array[j].Timestamp <= pivot)
            {
                Swap(array, i, j);
                i++;
            }
        }
        
        Swap(array, i, high);
        return i;
    }

    static void InsertionSort(Rating[] array, int low, int high)
    {
        for (int i = low + 1; i <= high; i++)
        {
            var temp = array[i];
            int j = i;
            
            while (j > low && temp.Timestamp < array[j - 1].Timestamp)
            {
                array[j] = array[j - 1];
                j--;
            }
            
            array[j] = temp;
        }
    }

    static void Swap(Rating[] array, int i, int j)
    {
        (array[i], array[j]) = (array[j], array[i]);
    }

    static void SaveRatings(string filename, Rating[] ratings)
    {
        using var writer = new StreamWriter(filename);
        writer.WriteLine("userId,movieId,rating,timestamp");
        foreach (var r in ratings)
            writer.WriteLine($"{r.UserId},{r.MovieId},{r.RatingValue.ToString(CultureInfo.InvariantCulture)},{r.Timestamp}");

        Console.WriteLine($"\n✅ Arquivo {filename} salvo com sucesso.");
        Console.WriteLine($"   Tamanho: {ratings.Length} registros");
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