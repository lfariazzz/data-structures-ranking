#include "ordenacao.h"
#include "atleta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar para trocar dois Atletas
static inline void trocar(Atleta *a, Atleta *b) {
    Atleta tmp = *a;
    *a = *b;
    *b = tmp;
}

// --- DEFINIÇÕES QUE DEVERIAM ESTAR NO .H MAS VAMOS COLOCAR AQUI ---

// Estrutura para a Lista Dinâmica (baseada nas suas fotos)
typedef struct No {
    Atleta dado;        
    struct No *proximo; 
} No;

// Estrutura para a Lista Estática (encadeada sobre vetor)
#define MAX 10000 
typedef struct {
    Atleta dado;
    int proximo;
} NoEstatico;

// --- FUNÇÃO DE COMPARAÇÃO ---

int comparar(Atleta a, Atleta b, int criterio) {
    if (criterio == 1) { // Por Tempo
        return a.tempoSegundos <= b.tempoSegundos;
    } else { // Por Pace
        return a.pace <= b.pace;
    }
}

// --- MERGE SORT DINÂMICO (Para a Issue #6) ---

No* merge_dinamico(No* a, No* b, int criterio) {
    if (a == NULL) return b;
    if (b == NULL) return a;

    No* result = NULL;
    if (comparar(a->dado, b->dado, criterio)) {
        result = a;
        result->proximo = merge_dinamico(a->proximo, b, criterio);
    } else {
        result = b;
        result->proximo = merge_dinamico(a, b->proximo, criterio);
    }
    return result;
}

void split_dinamica(No* fonte, No** frente, No** tras) {
    No* rapido;
    No* lento;
    lento = fonte;
    rapido = fonte->proximo;

    while (rapido != NULL) {
        rapido = rapido->proximo;
        if (rapido != NULL) {
            lento = lento->proximo;
            rapido = rapido->proximo;
        }
    }
    *frente = fonte;
    *tras = lento->proximo;
    lento->proximo = NULL;
}

void mergeSortDinamico(No** inicio, int criterio) {
    No* head = *inicio;
    No *a, *b;

    if ((head == NULL) || (head->proximo == NULL)) return;

    split_dinamica(head, &a, &b);
    mergeSortDinamico(&a, criterio);
    mergeSortDinamico(&b, criterio);
    *inicio = merge_dinamico(a, b, criterio);
}

// merge estático 

int merge_estatico(NoEstatico lista[], int esq, int dir, int criterio) {
    if (esq == -1) return dir;
    if (dir == -1) return esq;

    int resultado;
    // Compara usando a função 'comparar' que já está no topo do seu sorts.c
    if (comparar(lista[esq].dado, lista[dir].dado, criterio)) {
        resultado = esq;
        lista[resultado].proximo = merge_estatico(lista, lista[esq].proximo, dir, criterio);
    } else {
        resultado = dir;
        lista[resultado].proximo = merge_estatico(lista, esq, lista[dir].proximo, criterio);
    }
    return resultado;
}

void mergeSortEstatico(NoEstatico lista[], int *inicio, int criterio) {
    int head = *inicio;
    if (head == -1 || lista[head].proximo == -1) return;

    // Divide a lista (Slow and Fast pointers com índices)
    int lento = head;
    int rapido = lista[head].proximo;

    while (rapido != -1) {
        rapido = lista[rapido].proximo;
        if (rapido != -1) {
            lento = lista[lento].proximo;
            rapido = lista[rapido].proximo;
        }
    }

    int esquerda = head;
    int direita = lista[lento].proximo;
    lista[lento].proximo = -1; // Quebra a lista em duas

    mergeSortEstatico(lista, &esquerda, criterio);
    mergeSortEstatico(lista, &direita, criterio);

    *inicio = merge_estatica(lista, esquerda, direita, criterio);
}

// Implementação do insertion_sort
long insertion_sort(Atleta *v, int n, FuncComparacao cmp) {
    long comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Atleta chave = v[i];
        int j = i - 1;
        while (j >= 0) {
            comparacoes++;
            if (cmp(&v[j], &chave) > 0) {
                v[j+1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j+1] = chave;
    }
    return comparacoes;
}


// Implementação do quick_sort
long _quick_sort_rec(Atleta *v, int esq, int dir, FuncComparacao cmp) {
    long comparacoes = 0;
    if (esq >= dir)
        return 0;

    // Escolhe o pivô (aqui usando o elemento do meio)    
    Atleta pivo = v[(esq + dir) / 2];
    int i = esq;
    int j = dir;

    while (i <= j) {
        // Avança i enquanto v[i] < pivo
        while (1) {
            comparacoes++;
            if (cmp(&v[i], &pivo) < 0) i++;
            else break;
        }
        // Recua j enquanto v[j] > pivo
        while (1) {
            comparacoes++;
            if (cmp(&v[j], &pivo) > 0) j--;
            else break;
        }
        if (i <= j) {
            trocar(&v[i], &v[j]);
            i++;
            j--;
        }
    }

    comparacoes += _quick_sort_rec(v, esq, j, cmp);
    comparacoes += _quick_sort_rec(v, i, dir, cmp);
    return comparacoes;
}

long quick_sort(Atleta *v, int n, FuncComparacao cmp) {
    if (n <= 1) return 0;
    return _quick_sort_rec(v, 0, n - 1, cmp);
}

// Implementação do bubble_sort
long bubble_sort(Atleta *v, int n, FuncComparacao cmp) {
    long comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            comparacoes++;
            if (cmp(&v[j], &v[j+1]) > 0) {
                trocar(&v[j], &v[j+1]);
                trocou = 1;
            }
        }
        if (!trocou)
            break; // Otimização: se não houve trocas, o vetor já está ordenado
    }
    return comparacoes;
}

// Implementação do selection_sort 
long selection_sort(Atleta *v, int n, FuncComparacao cmp) {
    long comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int idx_min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (cmp(&v[j], &v[idx_min]) < 0)
                idx_min = j;
        }
        if (idx_min != i)
            trocar(&v[i], &v[idx_min]);
    }
    return comparacoes;
}