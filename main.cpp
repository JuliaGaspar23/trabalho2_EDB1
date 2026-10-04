#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include "ordenacao.hpp"

// Função para gerar os dados do vetor
std::vector<int> gerarVetor(int tamanho, const std::string& cenario, const std::string& algoritmo) {
    std::vector<int> vec(tamanho);
    
    if (cenario == "melhor") {
        // Para a maioria, melhor caso é o vetor ordenado crescente: [0, 1, 2, ..., N-1]
        for (int i = 0; i < tamanho; ++i) vec[i] = i;
    } 
    else if (cenario == "pior") {
        if (algoritmo == "quick") {
            // No QuickSort com pivô no último elemento, o pior caso ocorre quando o vetor já está ordenado
            for (int i = 0; i < tamanho; ++i) vec[i] = i;
        } else {
            // Para Insertion, Selection e Bubble, o pior caso é o vetor invertido: [N, N-1, ..., 1]
            for (int i = 0; i < tamanho; ++i) vec[i] = tamanho - i;
        }
    }
    return vec;
}

// Executa o algoritmo selecionado sobre a cópia do vetor
void executarAlgoritmo(const std::string& alg, std::vector<int>& vec, int n) {
    if (alg == "insertion") insertionSort(vec, 0, n);
    else if (alg == "selection") selectionSort(vec, 0, n);
    else if (alg == "bubble") bubbleSort(vec, 0, n);
    else if (alg == "merge") mergeSort(vec, 0, n);
    else if (alg == "quick") quickSort(vec, 0, n);
}

int main(int argc, char* argv[]) {
    // Parâmetros de execução esperados: ./programa.exe <algoritmo> <cenario>
    std::string algoritmo = (argc > 1) ? argv[1] : "insertion";
    std::string cenario = (argc > 2) ? argv[2] : "pior";

    // Para algoritmos O(N^2) no pior caso, limitamos a 100k para não demorar horas no terminal
    int tamanho_final = (algoritmo == "merge" || algoritmo == "quick" || cenario == "melhor") ? 500000 : 100000;
    int passo = (tamanho_final == 500000) ? 25000 : 5000;
    const int REPETICOES = 5; // Média de 5 medições (requisito do trabalho)

    std::cout << "Tamanho,Tempo_NS\n";

    for (int n = 0; n <= tamanho_final; n += passo) {
        long long tempo_total = 0;

        for (int rep = 0; rep < REPETICOES; ++rep) {
            std::vector<int> vec = gerarVetor(n, cenario, algoritmo);

            auto inicio = std::chrono::high_resolution_clock::now();
            executarAlgoritmo(algoritmo, vec, n);
            auto fim = std::chrono::high_resolution_clock::now();

            tempo_total += std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio).count();
        }

        long long tempo_medio = tempo_total / REPETICOES;
        std::cout << n << "," << tempo_medio << "\n";
    }

    return 0;
}