#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>
#include <cmath>

// Implementação do Bubble Sort com contagem de operações
void bubbleSort(std::vector<int>& arr, int& comparacoes, int& trocas) {
    comparacoes = 0;
    trocas = 0;
    int n = arr.size();
    bool trocaFeita;
    
    for (int i = 0; i < n - 1; i++) {
        trocaFeita = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                trocas++;
                trocaFeita = true;
            }
        }
        // Se nenhuma troca foi feita na passagem, o array já está ordenado
        if (!trocaFeita)
            break;
    }
}

// Implementação do Insertion Sort com contagem de operações
void insertionSort(std::vector<int>& arr, int& comparacoes, int& trocas) {
    comparacoes = 0;
    trocas = 0;
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int chave = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (arr[j] > chave) {
                arr[j + 1] = arr[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = chave;
        if (j + 1 != i) {
            trocas++; // Consideramos a colocação final da chave como uma troca
        }
    }
}

// Implementação do Selection Sort com contagem de operações
void selectionSort(std::vector<int>& arr, int& comparacoes, int& trocas) {
    comparacoes = 0;
    trocas = 0;
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int indiceMinimo = i;
        
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (arr[j] < arr[indiceMinimo]) {
                indiceMinimo = j;
            }
        }
        
        if (indiceMinimo != i) {
            std::swap(arr[i], arr[indiceMinimo]);
            trocas++;
        }
    }
}

// Função para gerar vetor aleatório
std::vector<int> gerarVetorAleatorio(int tamanho, bool crescente = false, bool decrescente = false) {
    std::vector<int> vetor(tamanho);
    
    if (crescente) {
        // Vetor já ordenado (melhor caso)
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = i;
        }
    } else if (decrescente) {
        // Vetor em ordem inversa (pior caso)
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = tamanho - i - 1;
        }
    } else {
        // Vetor aleatório (caso medio)
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, tamanho * 10);
        
        for (int i = 0; i < tamanho; i++) {
            vetor[i] = dis(gen);
        }
    }
    
    return vetor;
}

// Função para exibir resultados teóricos
void exibirResultadosTeoricos(int tamanho) {
    double n = tamanho;
    
    std::cout << "\nResultados Teoricos para n = " << tamanho << ":\n";
    
    // Bubble Sort
    std::cout << "Bubble Sort:\n";
    std::cout << "  Melhor caso (O(n)): " << tamanho << " comparacoes\n";
    std::cout << "  Pior caso/Caso medio (O(n2)): " << (n * (n - 1)) / 2 << " comparacoes, " 
              << (n * (n - 1)) / 2 << " trocas\n";
    
    // Insertion Sort
    std::cout << "Insertion Sort:\n";
    std::cout << "  Melhor caso (O(n)): " << tamanho - 1 << " comparacoes, 0 trocas\n";
    std::cout << "  Pior caso (O(n2)): " << (n * (n - 1)) / 2 << " comparacoes, " 
              << (n * (n - 1)) / 2 << " trocas\n";
    
    // Selection Sort
    std::cout << "Selection Sort:\n";
    std::cout << "  Todos os casos (O(n2)): " << (n * (n - 1)) / 2 << " comparacoes, " 
              << std::min(n - 1, n) << " trocas\n";
}

// Função para testar os algoritmos
void testarAlgoritmos(int tamanho) {
    std::cout << "\n===== Testes com vetor de tamanho " << tamanho << " =====\n";
    
    // Gerar vetores para teste
    std::vector<int> vetorMelhorCaso = gerarVetorAleatorio(tamanho, true);
    std::vector<int> vetorCasoMedio = gerarVetorAleatorio(tamanho);
    std::vector<int> vetorPiorCaso = gerarVetorAleatorio(tamanho, false, true);
    
    // Variáveis para contagem
    int comparacoes, trocas;
    
    // Teste do Bubble Sort
    std::cout << "\nBubble Sort:\n";
    
    // Melhor caso
    std::vector<int> testeBubble = vetorMelhorCaso;
    bubbleSort(testeBubble, comparacoes, trocas);
    std::cout << "  Melhor caso: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Caso medio
    testeBubble = vetorCasoMedio;
    bubbleSort(testeBubble, comparacoes, trocas);
    std::cout << "  Caso medio: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Pior caso
    testeBubble = vetorPiorCaso;
    bubbleSort(testeBubble, comparacoes, trocas);
    std::cout << "  Pior caso: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Teste do Insertion Sort
    std::cout << "\nInsertion Sort:\n";
    
    // Melhor caso
    std::vector<int> testeInsertion = vetorMelhorCaso;
    insertionSort(testeInsertion, comparacoes, trocas);
    std::cout << "  Melhor caso: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Caso medio
    testeInsertion = vetorCasoMedio;
    insertionSort(testeInsertion, comparacoes, trocas);
    std::cout << "  Caso medio: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Pior caso
    testeInsertion = vetorPiorCaso;
    insertionSort(testeInsertion, comparacoes, trocas);
    std::cout << "  Pior caso: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Teste do Selection Sort
    std::cout << "\nSelection Sort:\n";
    
    // Melhor caso
    std::vector<int> testeSelection = vetorMelhorCaso;
    selectionSort(testeSelection, comparacoes, trocas);
    std::cout << "  Melhor caso: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Caso medio
    testeSelection = vetorCasoMedio;
    selectionSort(testeSelection, comparacoes, trocas);
    std::cout << "  Caso medio: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Pior caso
    testeSelection = vetorPiorCaso;
    selectionSort(testeSelection, comparacoes, trocas);
    std::cout << "  Pior caso: " << comparacoes << " comparacoes, " << trocas << " trocas\n";
    
    // Exibir resultados teóricos para comparação
    exibirResultadosTeoricos(tamanho);
}

int main() {
    std::cout << "ANALISE DE ALGORITMOS DE ORDENACAO\n";
    std::cout << "=================================\n";
    
    // Testar com diferentes tamanhos de entrada
    testarAlgoritmos(10);
    testarAlgoritmos(100);
    testarAlgoritmos(1000);
    
    return 0;
}