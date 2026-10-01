#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>
#include "ordenacao.hpp"

// Função auxiliar para gerar vetor segundo o cenário de teste
std::vector<int> gerarVetor(int tamanho, const std::string& tipo) {
    std::vector<int> vec(tamanho);
    if (tipo == "melhor_caso") {
        for (int i = 0; i < tamanho; ++i) vec[i] = i; // Já ordenado: [0, 1, 2, ...]
    } else if (tipo == "pior_caso") {
        for (int i = 0; i < tamanho; ++i) vec[i] = tamanho - i; // Invertido: [N, N-1, ...]
    }
    return vec;
}

int main() {
    // Parâmetros de execução (Conforme especificação do trabalho)
    const int TAMANHO_INICIAL = 0;
    const int TAMANHO_FINAL = 100000; // Ajustado para testes quadráticos rápidos (expansível até 500k)
    const int PASSO = 5000;
    const int REPETICOES = 5; // Média de 5 execuções conforme item do PDF

    std::cout << "Tamanho,Tempo_NS\n";

    for (int n = TAMANHO_INICIAL; n <= TAMANHO_FINAL; n += PASSO) {
        long long tempo_total = 0;

        for (int rep = 0; rep < REPETICOES; ++rep) {
            // Gera o vetor para cada repetição
            std::vector<int> vec = gerarVetor(n, "pior_caso");

            auto inicio = std::chrono::high_resolution_clock::now();
            
            // Exemplo para o Insertion Sort no intervalo [0, n)
            insertionSort(vec, 0, n);
            
            auto fim = std::chrono::high_resolution_clock::now();

            tempo_total += std::chrono::duration_cast<std::chrono::nanoseconds>(fim - inicio).count();
        }

        long long tempo_medio = tempo_total / REPETICOES;
        std::cout << n << "," << tempo_medio << "\n";
    }

    return 0;
}