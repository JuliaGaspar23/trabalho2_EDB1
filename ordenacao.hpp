#ifndef ORDENACAO_HPP
#define ORDENACAO_HPP

#include <vector>
#include <utility> // Para std::swap

// 1. INSERTION SORT (Ordenação por Inserção)
// Convenção de acesso: intervalo semiaberto [esq, dir)
void insertionSort(std::vector<int>& vec, int esq, int dir) {
    // Percorre o vetor a partir do segundo elemento até 'dir - 1'
    for (int i = esq + 1; i < dir; ++i) {
        int chave = vec[i]; // Elemento atual a ser inserido na sublista ordenada
        int j = i - 1;

        // Desloca os elementos maiores que 'chave' para uma posição à frente
        while (j >= esq && vec[j] > chave) {
            vec[j + 1] = vec[j];
            --j;
        }
        // Insere a chave na sua posição correta
        vec[j + 1] = chave;
    }
}

// 2. SELECTION SORT (Ordenação por Seleção)
// Convenção de acesso: intervalo semiaberto [esq, dir)
void selectionSort(std::vector<int>& vec, int esq, int dir) {
    // Percorre o vetor até ao penúltimo elemento
    for (int i = esq; i < dir - 1; ++i) {
        int min_idx = i; // Assume que o menor elemento está no índice 'i'

        // Procura pelo menor elemento no restante do vetor [i+1, dir)
        for (int j = i + 1; j < dir; ++j) {
            if (vec[j] < vec[min_idx]) {
                min_idx = j; // Atualiza o índice do menor elemento encontrado
            }
        }

        // Troca o menor elemento encontrado com o elemento da posição 'i'
        if (min_idx != i) {
            std::swap(vec[i], vec[min_idx]);
        }
    }
}

// 3. BUBBLE SORT (Ordenação por Troca / Bolha)
// Convenção de acesso: intervalo semiaberto [esq, dir)
void bubbleSort(std::vector<int>& vec, int esq, int dir) {
    bool trocou; // Flag de otimização para identificar se o vetor já está ordenado
    
    for (int i = esq; i < dir - 1; ++i) {
        trocou = false;
        
        // Empurra o maior elemento para o final da sublista não ordenada
        for (int j = esq; j < dir - 1 - (i - esq); ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
                trocou = true; // Houve troca
            }
        }
        
        // Se nenhuma troca ocorreu nesta passagem, o vetor já está ordenado
        if (!trocou) break;
    }
}

// 4. MERGE SORT (Ordenação por Intercalação)
// Convenção de acesso: intervalo semiaberto [esq, dir)
void merge(std::vector<int>& vec, int esq, int meio, int dir) {
    // Cria vetores auxiliares para as duas metades
    std::vector<int> esq_vec(vec.begin() + esq, vec.begin() + meio);
    std::vector<int> dir_vec(vec.begin() + meio, vec.begin() + dir);

    size_t i = 0, j = 0;
    int k = esq;

    // Intercala os dois subvetores de volta no vetor original 'vec'
    while (i < esq_vec.size() && j < dir_vec.size()) {
        if (esq_vec[i] <= dir_vec[j]) {
            vec[k++] = esq_vec[i++];
        } else {
            vec[k++] = dir_vec[j++];
        }
    }

    // Copia os elementos restantes, se houver
    while (i < esq_vec.size()) vec[k++] = esq_vec[i++];
    while (j < dir_vec.size()) vec[k++] = dir_vec[j++];
}

void mergeSort(std::vector<int>& vec, int esq, int dir) {
    // Caso base: se o intervalo tiver 1 ou 0 elementos, já está ordenado
    if (dir - esq <= 1) return;

    int meio = esq + (dir - esq) / 2; // Calcula o ponto médio
    mergeSort(vec, esq, meio);       // Ordena a metade esquerda [esq, meio)
    mergeSort(vec, meio, dir);       // Ordena a metade direita [meio, dir)
    merge(vec, esq, meio, dir);      // Intercala as duas metades
}

int particiona(std::vector<int>& vec, int esq, int dir) {
    int pivo = vec[dir - 1]; // Escolhe o último elemento do intervalo como pivô
    int i = esq - 1;

    // Agrupa elementos menores que o pivô à esquerda
    for (int j = esq; j < dir - 1; ++j) {
        if (vec[j] < pivo) {
            ++i;
            std::swap(vec[i], vec[j]);
        }
    }
    // Posiciona o pivô no local correto
    std::swap(vec[i + 1], vec[dir - 1]);
    return i + 1; // Retorna o índice onde o pivô ficou
}

void quickSort(std::vector<int>& vec, int esq, int dir) {
    // Caso base: se o intervalo tiver 1 ou 0 elementos, encerra
    if (dir - esq <= 1) return;

    // Particiona o vetor em torno do pivô
    int pivo_idx = particiona(vec, esq, dir);

    // Chamadas recursivas para as duas metades
    quickSort(vec, esq, pivo_idx);     // Metade esquerda [esq, pivo_idx)
    quickSort(vec, pivo_idx + 1, dir); // Metade direita [pivo_idx + 1, dir)
}

#endif 