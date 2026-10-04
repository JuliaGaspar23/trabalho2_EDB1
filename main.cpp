#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include "ordenacao.hpp"


// FUNÇÃO AUXILIAR: Geração de Vetores por Cenário
// Cria e preenche o vetor de acordo com o cenário de teste (Melhor ou Pior Caso)
std::vector<int> gerarVetor(int tamanho, const std::string& cenario, const std::string& algoritmo) {
    std::vector<int> vec(tamanho);
    
    if (cenario == "melhor") {
        // Para a maioria dos algoritmos, o melhor caso é o vetor já ordenado [0, 1, 2, ..., N-1]
        for (int i = 0; i < tamanho; ++i) vec[i] = i;
    } 
    else if (cenario == "pior") {
        if (algoritmo == "quick") {
            // No QuickSort (com pivô no fim), o pior caso ocorre com vetor já ordenado
            for (int i = 0; i < tamanho; ++i) vec[i] = i;
        } else {
            // Para Insertion, Selection e Bubble, o pior caso é o vetor invertido [N, N-1, ..., 1]
            for (int i = 0; i < tamanho; ++i) vec[i] = tamanho - i;
        }
    }
    return vec;
}


// FUNÇÃO AUXILIAR: Roteamento dos Algoritmos
// Chama a função correspondente respeitando o intervalo semiaberto [0, n)
void executarAlgoritmo(const std::string& alg, std::vector<int>& vec, int n) {
    if (alg == "insertion") insertionSort(vec, 0, n);
    else if (alg == "selection") selectionSort(vec, 0, n);
    else if (alg == "bubble") bubbleSort(vec, 0, n);
    else if (alg == "merge") mergeSort(vec, 0, n);
    else if (alg == "quick") quickSort(vec, 0, n);
}

// FUNÇÃO PRINCIPAL: Coleta Empírica de Dados
int main(int argc, char* argv[]) {
    // Leitura dos argumentos de linha de comando: ./programa.exe <algoritmo> <cenario>
    std::string algoritmo = (argc > 1) ? argv[1] : "insertion";
    std::string cenario = (argc > 2) ? argv[2] : "pior";

    // DEFINIÇÃO DOS LIMITES DE AMOSTRAGEM:
    // Para algoritmos e cenários lentos O(N^2), usamos N até 30.000 para não travar o PC
    // Para algoritmos eficientes O(N log N) ou O(N), testamos até N = 500.000
    int tamanho_final = 30000;
    int passo = 1500;

    bool eh_rapido = (algoritmo == "merge") || 
                     (algoritmo == "quick" && cenario == "melhor") || 
                     (algoritmo == "insertion" && cenario == "melhor") || 
                     (algoritmo == "bubble" && cenario == "melhor");

    if (eh_rapido) {
        tamanho_final = 500000;
        passo = 25000;
    }

    const int REPETICOES = 5; // Média de 5 medições para reduzir ruído da CPU

    // Imprime o cabeçalho no formato CSV
    std::cout << "Tamanho,Tempo_NS\n";

    // Laço principal que varia o tamanho do vetor N
    for (int n = 0; n <= tamanho_final; n += passo) {
        long long tempo_total = 0;

        // Executa 5 repetições para cada tamanho N e calcula a média
        for (int rep = 0; rep < REPETICOES; ++rep) {
            std::vector<int> vec = gerarVetor(n, cenario, algoritmo);

            // Marcação do tempo inicial
            auto inicio = std::chrono::high_resolution_clock::now();
            
            // Executa a ordenação
            executarAlgoritmo(algoritmo, vec, n);
            
            // Marcação do tempo final
            auto fim = std::chrono::high_resolution_clock::now();

            // Acumula o tempo decorrido em nanosegundos
            tempo_total += std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio).count();
        }

        // Calcula a média e exibe o resultado formatado em CSV
        long long tempo_medio = tempo_total / REPETICOES;
        std::cout << n << "," << tempo_medio << "\n";
    }

    return 0;
}