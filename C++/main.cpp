#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <memory>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <functional>

// Estrutura otimizada de Rating
struct Rating {
    int userId;
    int movieId;
    float rating;
    int timestamp;
    
    Rating() = default;
    Rating(int uid, int mid, float r, int ts) : userId(uid), movieId(mid), rating(r), timestamp(ts) {}
};


class EstruturaBase {
public:
    virtual ~EstruturaBase() = default;
    virtual void adicionar(const Rating& r) = 0;
    virtual void limpar() = 0;
    virtual size_t tamanho() const = 0;
    virtual std::vector<Rating> paraVetor() const = 0;
    virtual void deVetor(const std::vector<Rating>& v) = 0;
};

class QuickSort {
private:
    // Insertion sort ultra otimizado (como Julia com @inbounds)
    static inline void insertionSort(std::vector<Rating>& arr, int low, int high) {
        for (int i = low + 1; i <= high; ++i) {
            Rating temp = arr[i];
            int tempTimestamp = temp.timestamp;
            int j = i - 1;
            
            // Loop otimizado sem bounds checking
            while (j >= low && arr[j].timestamp > tempTimestamp) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = temp;
        }
    }
    
    // Partição com mediana de três (exatamente como Julia)
    static inline int partition(std::vector<Rating>& arr, int low, int high) {
        // Mediana de três exatamente como Julia
        int mid = (low + high) / 2;
        
        int a = arr[low].timestamp;
        int b = arr[mid].timestamp; 
        int c = arr[high].timestamp;
        
        // Ordena os três valores (como Julia)
        if (a > b) {
            std::swap(arr[low], arr[mid]);
            std::swap(a, b);
        }
        if (a > c) {
            std::swap(arr[low], arr[high]);
            std::swap(a, c);
        }
        if (b > c) {
            std::swap(arr[mid], arr[high]);
            std::swap(b, c);
        }
        
        // Move mediana para o final
        std::swap(arr[mid], arr[high]);
        
        // Partição Lomuto otimizada
        int pivot = arr[high].timestamp;
        int i = low;
        
        for (int j = low; j < high; ++j) {
            if (arr[j].timestamp <= pivot) {
                std::swap(arr[i], arr[j]);
                ++i;
            }
        }
        
        std::swap(arr[i], arr[high]);
        return i;
    }
    
    // QuickSort com tail recursion optimization (como Julia)
    static void quickSortTailOptimized(std::vector<Rating>& arr, int low, int high) {
        while (low < high) {
            // Insertion sort para arrays pequenos (como Julia: ≤20)
            if (high - low <= 20) {
                insertionSort(arr, low, high);
                break;
            }
            
            int pi = partition(arr, low, high);
            
            // Tail recursion optimization (como Julia)
            if (pi - low < high - pi) {
                quickSortTailOptimized(arr, low, pi - 1);
                low = pi + 1;
            } else {
                quickSortTailOptimized(arr, pi + 1, high);
                high = pi - 1;
            }
        }
    }
    
public:
    static inline void ordenar(std::vector<Rating>& arr) {
        if (arr.size() <= 1) return;
        quickSortTailOptimized(arr, 0, static_cast<int>(arr.size()) - 1);
    }
};


class VetorEstatico : public EstruturaBase {
private:
    std::vector<Rating> data;
    
public:
    VetorEstatico() {
        data.reserve(100000000); // Reserve para 100M como Julia
    }
    
    inline void adicionar(const Rating& r) override {
        data.push_back(r);
    }
    
    inline void limpar() override {
        data.clear();
    }
    
    inline size_t tamanho() const override {
        return data.size();
    }
    
    inline std::vector<Rating> paraVetor() const override {
        return data; // Move semantics quando possível
    }
    
    inline void deVetor(const std::vector<Rating>& v) override {
        data = v;
    }
};

class VetorDinamico : public EstruturaBase {
private:
    struct No {
        Rating dado;
        No* proximo;
        
        No(const Rating& r) : dado(r), proximo(nullptr) {}
    };
    
    No* cabeca;
    No* cauda;
    size_t _tamanho;
    
public:
    VetorDinamico() : cabeca(nullptr), cauda(nullptr), _tamanho(0) {}
    
    ~VetorDinamico() {
        limpar();
    }
    
    inline void adicionar(const Rating& r) override {
        No* novo = new No(r);
        if (!cabeca) {
            cabeca = cauda = novo;
        } else {
            cauda->proximo = novo;
            cauda = novo;
        }
        ++_tamanho;
    }
    
    void limpar() override {
        while (cabeca) {
            No* temp = cabeca;
            cabeca = cabeca->proximo;
            delete temp;
        }
        cauda = nullptr;
        _tamanho = 0;
    }
    
    inline size_t tamanho() const override {
        return _tamanho;
    }
    
    std::vector<Rating> paraVetor() const override {
        std::vector<Rating> result;
        result.reserve(_tamanho);
        
        No* atual = cabeca;
        while (atual) {
            result.push_back(atual->dado);
            atual = atual->proximo;
        }
        return result;
    }
    
    void deVetor(const std::vector<Rating>& v) override {
        limpar();
        for (const auto& r : v) {
            adicionar(r);
        }
    }
};

class PilhaEstatica : public EstruturaBase {
private:
    std::vector<Rating> pilha;
    
public:
    PilhaEstatica() {
        pilha.reserve(100000000);
    }
    
    inline void adicionar(const Rating& r) override {
        pilha.push_back(r);
    }
    
    inline void limpar() override {
        pilha.clear();
    }
    
    inline size_t tamanho() const override {
        return pilha.size();
    }
    
    inline std::vector<Rating> paraVetor() const override {
        return pilha;
    }
    
    inline void deVetor(const std::vector<Rating>& v) override {
        pilha = v;
    }
};

class PilhaDinamica : public EstruturaBase {
private:
    struct No {
        Rating dado;
        No* proximo;
        No(const Rating& r) : dado(r), proximo(nullptr) {}
    };
    
    No* topo;
    size_t _tamanho;
    
public:
    PilhaDinamica() : topo(nullptr), _tamanho(0) {}
    
    ~PilhaDinamica() {
        limpar();
    }
    
    inline void adicionar(const Rating& r) override {
        No* novo = new No(r);
        novo->proximo = topo;
        topo = novo;
        ++_tamanho;
    }
    
    void limpar() override {
        while (topo) {
            No* temp = topo;
            topo = topo->proximo;
            delete temp;
        }
        _tamanho = 0;
    }
    
    inline size_t tamanho() const override {
        return _tamanho;
    }
    
    std::vector<Rating> paraVetor() const override {
        std::vector<Rating> result;
        result.reserve(_tamanho);
        
        // Coleta em ordem reversa e depois reverte (como Julia)
        No* atual = topo;
        while (atual) {
            result.push_back(atual->dado);
            atual = atual->proximo;
        }
        
        std::reverse(result.begin(), result.end());
        return result;
    }
    
    void deVetor(const std::vector<Rating>& v) override {
        limpar();
        for (const auto& r : v) {
            adicionar(r);
        }
    }
};

class FilaEstatica : public EstruturaBase {
private:
    std::vector<Rating> buffer;
    size_t inicio;
    size_t fim;
    size_t _tamanho;
    size_t capacidade;
    
    void expandir() {
        const size_t nova_cap = capacidade << 1;
        std::vector<Rating> novo_buffer(nova_cap);
        
        for (size_t i = 0; i < _tamanho; ++i) {
            novo_buffer[i] = buffer[(inicio + i) % capacidade];
        }
        
        buffer = std::move(novo_buffer);
        capacidade = nova_cap;
        inicio = 0;
        fim = _tamanho;
    }
    
public:
    FilaEstatica(size_t cap = 1000) : buffer(cap), inicio(0), fim(0), _tamanho(0), capacidade(cap) {}
    
    inline void adicionar(const Rating& r) override {
        if (_tamanho == capacidade) {
            expandir();
        }
        buffer[fim] = r;
        fim = (fim + 1) % capacidade;
        ++_tamanho;
    }
    
    inline void limpar() override {
        inicio = fim = _tamanho = 0;
    }
    
    inline size_t tamanho() const override {
        return _tamanho;
    }
    
    std::vector<Rating> paraVetor() const override {
        std::vector<Rating> result;
        result.reserve(_tamanho);
        
        for (size_t i = 0; i < _tamanho; ++i) {
            result.push_back(buffer[(inicio + i) % capacidade]);
        }
        return result;
    }
    
    void deVetor(const std::vector<Rating>& v) override {
        limpar();
        for (const auto& r : v) {
            adicionar(r);
        }
    }
};

class FilaDinamica : public EstruturaBase {
private:
    struct No {
        Rating dado;
        No* proximo;
        No(const Rating& r) : dado(r), proximo(nullptr) {}
    };
    
    No* inicio;
    No* fim;
    size_t _tamanho;
    
public:
    FilaDinamica() : inicio(nullptr), fim(nullptr), _tamanho(0) {}
    
    ~FilaDinamica() {
        limpar();
    }
    
    inline void adicionar(const Rating& r) override {
        No* novo = new No(r);
        if (!inicio) {
            inicio = fim = novo;
        } else {
            fim->proximo = novo;
            fim = novo;
        }
        ++_tamanho;
    }
    
    void limpar() override {
        while (inicio) {
            No* temp = inicio;
            inicio = inicio->proximo;
            delete temp;
        }
        fim = nullptr;
        _tamanho = 0;
    }
    
    inline size_t tamanho() const override {
        return _tamanho;
    }
    
    std::vector<Rating> paraVetor() const override {
        std::vector<Rating> result;
        result.reserve(_tamanho);
        
        No* atual = inicio;
        while (atual) {
            result.push_back(atual->dado);
            atual = atual->proximo;
        }
        return result;
    }
    
    void deVetor(const std::vector<Rating>& v) override {
        limpar();
        for (const auto& r : v) {
            adicionar(r);
        }
    }
};


class SistemaOrdenacao {
private:
    std::string arquivoCSV;
    std::ofstream metricas;
    
    // Parser otimizado (mais rápido que istringstream)
    Rating parseLinha(const std::string& linha) {
        Rating r;
        size_t pos = 0;
        size_t next = linha.find(',', pos);
        
        r.userId = std::stoi(linha.substr(pos, next - pos));
        pos = next + 1;
        next = linha.find(',', pos);
        
        r.movieId = std::stoi(linha.substr(pos, next - pos));
        pos = next + 1;
        next = linha.find(',', pos);
        
        r.rating = std::stof(linha.substr(pos, next - pos));
        pos = next + 1;
        
        r.timestamp = std::stoi(linha.substr(pos));
        
        return r;
    }
    
    std::vector<Rating> lerCSV(size_t limite) {
        std::vector<Rating> dados;
        dados.reserve(limite);
        
        std::ifstream file(arquivoCSV);
        if (!file.is_open()) {
            throw std::runtime_error("Erro ao abrir arquivo: " + arquivoCSV);
        }
        
        // Buffer maior para I/O mais eficiente
        file.rdbuf()->pubsetbuf(nullptr, 65536);
        
        std::string linha;
        std::getline(file, linha); // Pula cabeçalho
        
        size_t count = 0;
        while (count < limite && std::getline(file, linha)) {
            if (!linha.empty()) {
                try {
                    dados.push_back(parseLinha(linha));
                    ++count;
                } catch (const std::exception&) {
                    continue;
                }
            }
        }
        
        file.close();
        return dados;
    }
    
    std::string encontrarArquivo() {
        std::vector<std::string> caminhos = {
            "ratings.csv",
            "../ratings.csv", 
            "../dataset/ratings.csv",
            "dataset/ratings.csv",
            "../data/ratings.csv",
            "data/ratings.csv"
        };
        
        for (const auto& caminho : caminhos) {
            std::ifstream teste(caminho);
            if (teste.good()) {
                teste.close();
                return caminho;
            }
        }
        
        return "";
    }
    
    // MEDIÇÃO EXATA COMO JULIA (desde o início total)
    double ordenarComEstrutura(const std::vector<Rating>& dados, 
                               std::unique_ptr<EstruturaBase>& estrutura) {
        
        // INÍCIO - exato como Julia time_ns()
        auto inicio = std::chrono::high_resolution_clock::now();
        
        size_t n = dados.size();
        std::cout << "\n🔨 Preparando " << n << " registros para ordenação..." << std::endl;
        
        // Etapa 1: Adicionar dados à estrutura (incluso no tempo)
        for (const auto& r : dados) {
            estrutura->adicionar(r);
        }
        
        // Etapa 2: Converter para vetor (incluso no tempo)
        std::cout << "⏱️  Ordenando dados..." << std::endl;
        std::vector<Rating> vetor = estrutura->paraVetor();
        
        // Etapa 3: Ordenação (core do tempo)
        std::cout << "Iniciando ordenação de " << vetor.size() 
                  << " linhas pelo 'timestamp' (coluna índice 3) usando Mediana de Três..." 
                  << std::endl;
        
        QuickSort::ordenar(vetor);
        
        // Etapa 4: Converter de volta (incluso no tempo)
        estrutura->deVetor(vetor);
        
        // FIM - exato como Julia
        auto fim = std::chrono::high_resolution_clock::now();
        auto duracao = std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio);
        double tempo_segundos = duracao.count() / 1e9;
        
        // Formato de tempo como Julia
        std::string tempo_formatado;
        if (tempo_segundos >= 1) {
            tempo_formatado = std::to_string(tempo_segundos) + " s";
        } else if (tempo_segundos >= 1e-3) {
            tempo_formatado = std::to_string(tempo_segundos * 1e3) + " ms";
        } else {
            tempo_formatado = std::to_string(tempo_segundos * 1e6) + " µs";
        }
        
        std::cout << "Ordenação concluída em " << std::fixed << std::setprecision(9) 
                  << tempo_segundos << " segundos." << std::endl;
        std::cout << "- Tempo de ordenação: " << tempo_formatado << std::endl;
        
        return tempo_segundos;
    }
    
public:
    SistemaOrdenacao() {
        arquivoCSV = encontrarArquivo();
        if (arquivoCSV.empty()) {
            throw std::runtime_error("Arquivo ratings.csv não encontrado!");
        }
        metricas.open("metricas.txt", std::ios::app);
    }
    
    ~SistemaOrdenacao() {
        if (metricas.is_open()) {
            metricas.close();
        }
    }
    
    void executar() {
        struct EstruturaDef {
            std::string nome;
            std::function<std::unique_ptr<EstruturaBase>()> criar;
        };
        
        // Nomes exatos como Julia
        std::vector<EstruturaDef> estruturas = {
            {"Lista (Vetor)", []() -> std::unique_ptr<EstruturaBase> { 
                return std::make_unique<VetorEstatico>(); 
            }},
            {"Lista Encadeada", []() -> std::unique_ptr<EstruturaBase> { 
                return std::make_unique<VetorDinamico>(); 
            }},
            {"Pilha (Vetor)", []() -> std::unique_ptr<EstruturaBase> { 
                return std::make_unique<PilhaEstatica>(); 
            }},
            {"Pilha Encadeada", []() -> std::unique_ptr<EstruturaBase> { 
                return std::make_unique<PilhaDinamica>(); 
            }},
            {"Fila (Vetor)", []() -> std::unique_ptr<EstruturaBase> { 
                return std::make_unique<FilaEstatica>(); 
            }},
            {"Fila Encadeada", []() -> std::unique_ptr<EstruturaBase> { 
                return std::make_unique<FilaDinamica>(); 
            }}
        };
        
        std::vector<size_t> tamanhos = {100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
        
        while (true) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::cout << "MENU PRINCIPAL" << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            
            std::cout << "\n📚 Escolha a estrutura de dados:" << std::endl;
            for (size_t i = 0; i < estruturas.size(); i++) {
                std::cout << (i + 1) << ". " << estruturas[i].nome << std::endl;
            }
            std::cout << "0. Sair" << std::endl;
            
            int escolha;
            std::cout << "\nOpção: ";
            std::cin >> escolha;
            
            if (escolha == 0) break;
            if (escolha < 1 || escolha > static_cast<int>(estruturas.size())) {
                std::cout << "Opção inválida!" << std::endl;
                continue;
            }
            
            EstruturaDef& estrutura_selecionada = estruturas[escolha - 1];
            
            std::cout << "\n📏 Escolha o tamanho dos dados:" << std::endl;
            for (size_t i = 0; i < tamanhos.size(); i++) {
                std::cout << (i + 1) << ". " << tamanhos[i] << " registros" << std::endl;
            }
            
            int idx_tamanho;
            std::cout << "\nOpção: ";
            std::cin >> idx_tamanho;
            
            if (idx_tamanho < 1 || idx_tamanho > static_cast<int>(tamanhos.size())) {
                std::cout << "Opção inválida!" << std::endl;
                continue;
            }
            
            size_t tamanho = tamanhos[idx_tamanho - 1];
            
            try {
                std::cout << "\n🚀 Executando:" << std::endl;
                std::cout << "- Estrutura: " << estrutura_selecionada.nome << std::endl;
                std::cout << "- Tamanho: " << tamanho << " registros" << std::endl;
                
                std::cout << "\n📂 Carregando dados..." << std::endl;
                std::vector<Rating> dados = lerCSV(tamanho);
                
                std::cout << "📊 Dados carregados: " << dados.size() << " registros" << std::endl;
                
                metricas << estrutura_selecionada.nome << " " << tamanho << std::endl;
                
                // 10 execuções como Julia
                for (int i = 0; i < 10; i++) {
                    std::cout << "\nTentativa " << (i + 1) << " de ordenação com " 
                              << estrutura_selecionada.nome << "..." << std::endl;
                    
                    auto estrutura = estrutura_selecionada.criar();
                    double tempo = ordenarComEstrutura(dados, estrutura);
                    
                    metricas << std::fixed << std::setprecision(9) << tempo << std::endl;
                }
                
                metricas << std::endl;
                metricas.flush();
                
            } catch (const std::exception& e) {
                std::cerr << "Erro: " << e.what() << std::endl;
            }
        }
        
        std::cout << "\nPrograma encerrado. Até mais! 👋" << std::endl;
    }
};


int main() {
    try {
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "PROJETO AEDS - ORDENAÇÃO DE DADOS" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
        
        SistemaOrdenacao sistema;
        sistema.executar();
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Erro fatal: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}