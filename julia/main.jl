using Base: @kwdef
using Printf
using Dates

# Estrutura para armazenar cada registro
mutable struct Rating
userId::Int
movieId::Int
rating::Float64
timestamp::Int
end

# Nó para estruturas encadeadas
mutable struct Node
data::Rating
next::Union{Node, Nothing}
Node(data::Rating) = new(data, nothing)
end

# Implementações baseadas em vetor
@kwdef mutable struct VectorList
data::Vector{Rating} = Rating[]
end

@kwdef mutable struct VectorStack
data::Vector{Rating} = Rating[]
end

@kwdef mutable struct VectorQueue
data::Vector{Rating} = Rating[]
end

# Implementações baseadas em nós encadeados
@kwdef mutable struct LinkedList
head::Union{Node, Nothing} = nothing
length::Int = 0
end

@kwdef mutable struct LinkedStack
top::Union{Node, Nothing} = nothing
length::Int = 0
end

@kwdef mutable struct LinkedQueue
front::Union{Node, Nothing} = nothing
rear::Union{Node, Nothing} = nothing
length::Int = 0
end

# Função para salvar ratings em CSV
function save_ratings(filename, ratings::Vector{Rating})
open(filename, "w") do f
    println(f, "userId,movieId,rating,timestamp")
    for r in ratings
        println(f, "$(r.userId),$(r.movieId),$(r.rating),$(r.timestamp)")
    end
end
println("\n✅ Arquivo $filename salvo com sucesso.")
println("   Tamanho: $(length(ratings)) registros")
end

# Função segura para ler o CSV
function read_ratings(filename, max_entries=1_000_000)
ratings = Rating[]
try
    open(filename) do f
        readline(f)  # Pular cabeçalho
        count = 0
        while !eof(f) && count < max_entries
            line = readline(f)
            parts = split(line, ',')
            length(parts) < 4 && continue

            try
                push!(ratings, Rating(
                    parse(Int, parts[1]),
                    parse(Int, parts[2]),
                    parse(Float64, parts[3]),
                    parse(Int, parts[4])
                ))
                count += 1
            catch e
                @warn "Erro ao processar linha: $line. Erro: $e"
            end
        end
    end
    println("📊 Dados carregados: $(length(ratings)) registros")
catch e
    @error "Erro ao abrir arquivo: $filename. Verifique o caminho."
    println("Diretório atual: ", pwd())
    println("Arquivos no diretório: ")
    foreach(println, readdir())
    rethrow(e)
end
return ratings
end

# Funções para converter entre estruturas
function to_vector(structure)
if structure isa Union{VectorList, VectorStack, VectorQueue}
    return copy(structure.data)
elseif structure isa LinkedList
    vector = Rating[]
    current = structure.head
    while current !== nothing
        push!(vector, current.data)
        current = current.next
    end
    return vector
elseif structure isa LinkedStack
    vector = Rating[]
    current = structure.top
    while current !== nothing
        push!(vector, current.data)
        current = current.next
    end
    return vector
elseif structure isa LinkedQueue
    vector = Rating[]
    current = structure.front
    while current !== nothing
        push!(vector, current.data)
        current = current.next
    end
    return vector
end
end

function from_vector(vector, struct_type)
if struct_type == VectorList
    return VectorList(data=copy(vector))
elseif struct_type == VectorStack
    return VectorStack(data=copy(vector))
elseif struct_type == VectorQueue
    return VectorQueue(data=copy(vector))
elseif struct_type == LinkedList
    list = LinkedList()
    isempty(vector) && return list
    list.head = Node(vector[1])
    current = list.head
    list.length = 1
    for i in 2:length(vector)
        node = Node(vector[i])
        current.next = node
        current = node
        list.length += 1
    end
    return list
elseif struct_type == LinkedStack
    stack = LinkedStack()
    isempty(vector) && return stack
    for i in length(vector):-1:1
        node = Node(vector[i])
        node.next = stack.top
        stack.top = node
        stack.length += 1
    end
    return stack
elseif struct_type == LinkedQueue
    queue = LinkedQueue()
    isempty(vector) && return queue
    queue.front = Node(vector[1])
    queue.rear = queue.front
    queue.length = 1
    for i in 2:length(vector)
        node = Node(vector[i])
        queue.rear.next = node
        queue.rear = node
        queue.length += 1
    end
    return queue
end
end

# Algoritmo Quicksort otimizado
function quicksort!(arr::AbstractVector, low=1, high=length(arr))
@inbounds while low < high
    high - low <= 20 && return insertionsort!(arr, low, high)
    pi = partition!(arr, low, high)
    if pi - low < high - pi
        quicksort!(arr, low, pi - 1)
        low = pi + 1
    else
        quicksort!(arr, pi + 1, high)
        high = pi - 1
    end
end
end

function partition!(arr::AbstractVector, low, high)
pivot = arr[(low + high) ÷ 2].timestamp
i, j = low, high
@inbounds while true
    while arr[i].timestamp < pivot
        i += 1
    end
    while arr[j].timestamp > pivot
        j -= 1
    end
    i >= j && return j
    arr[i], arr[j] = arr[j], arr[i]
    i += 1
    j -= 1
end
end

function insertionsort!(arr::AbstractVector, low=1, high=length(arr))
@inbounds for i in low+1:high
    j = i
    temp = arr[i]
    while j > low && temp.timestamp < arr[j-1].timestamp
        arr[j] = arr[j-1]
        j -= 1
    end
    arr[j] = temp
end
return arr
end

# Função para ordenar e salvar
function sort_and_save(ratings::Vector{Rating}, struct_type, input_size)
n = min(input_size, length(ratings))
println("\n🔨 Preparando $n registros para ordenação...")

# Criar e converter estrutura
subset = ratings[1:n]
target_structure = from_vector(subset, struct_type)

# Medir tempo de ordenação
println("⏱️  Ordenando dados...")
start_time = time()
sorted_struct = sort_structure(target_structure)
elapsed = time() - start_time

# Converter de volta para vetor
sorted_vec = to_vector(sorted_struct)

# Salvar resultados
timestamp = Dates.format(now(), "yyyy-mm-dd_HH-MM-SS")
struct_name = string(typeof(sorted_struct))[1:end-2]
output_filename = "sorted_$(struct_name)_$(n)_$(timestamp).csv"

println("\n💾 Salvando resultados em $output_filename")
save_ratings(output_filename, sorted_vec)

println("\n📋 Resultados:")
println("- Tempo de ordenação: $(round(elapsed; digits=6)) segundos")


return elapsed
end

function sort_structure(structure)
vec = to_vector(structure)
quicksort!(vec)
return from_vector(vec, typeof(structure))
end

# Menu principal
function main()
input_sizes = [100, 1000, 10000, 100000, 1000000]

filename = find_ratings_file()
filename === nothing && return

println("\n📂 Carregando dados...")
ratings = read_ratings(filename, maximum(input_sizes))

structures = [
    ("Lista (Vetor)", VectorList),
    ("Lista Encadeada", LinkedList),
    ("Pilha (Vetor)", VectorStack),
    ("Pilha Encadeada", LinkedStack),
    ("Fila (Vetor)", VectorQueue),
    ("Fila Encadeada", LinkedQueue)
]

while true
    println("\n" * "="^50)
    println("MENU PRINCIPAL")
    println("="^50)

    # Escolher estrutura
    println("\n📚 Escolha a estrutura de dados:")
    for (i, (name, _)) in enumerate(structures)
        println("$i. $name")
    end
    println("0. Sair")
    print("\nOpção: ")
    choice = tryparse(Int, readline())
    choice === nothing && continue
    choice == 0 && break
    1 ≤ choice ≤ length(structures) || (println("Opção inválida!"); continue)
    struct_type = structures[choice][2]
    struct_name = structures[choice][1]

    # Escolher tamanho
    println("\n📏 Escolha o tamanho dos dados:")
    for (i, size) in enumerate(input_sizes)
        println("$i. $size registros")
    end
    print("\nOpção: ")
    size_choice = tryparse(Int, readline())
    size_choice === nothing && continue
    1 ≤ size_choice ≤ length(input_sizes) || (println("Opção inválida!"); continue)
    input_size = input_sizes[size_choice]

    # Confirmar
    println("\n🚀 Executando:")
    println("- Estrutura: $struct_name")
    println("- Tamanho: $input_size registros")

    # Executar ordenação e salvamento
    sort_and_save(ratings, struct_type, input_size)
end

println("\nPrograma encerrado. Até mais! 👋")
end

function find_ratings_file()
possible_paths = [
    "ratings.csv",
    "../ratings.csv",
    "data/ratings.csv",
    "../data/ratings.csv",
    joinpath(dirname(@__FILE__), "ratings.csv"),
    joinpath(dirname(@__FILE__), "..", "ratings.csv")
]

for path in possible_paths
    if isfile(path)
        println("✅ Arquivo encontrado em: $path")
        return path
    end
end

@error "❌ Arquivo ratings.csv não encontrado. Procurou em:"
for path in possible_paths
    println(" - $path")
end
return nothing
end

# Executar programa
if abspath(PROGRAM_FILE) == @__FILE__
println("\n" * "="^50)
println("PROJETO AEDS - ORDENAÇÃO DE DADOS")
println("="^50)
main()
end