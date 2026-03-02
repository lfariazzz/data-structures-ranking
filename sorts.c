#include "atleta.h"

// 0 = Ordenar por Tempo | 1 = Ordenar por Pace
static int modo_ordenacao = 0; 

/**
 * Funções para o seu main.c definir o critério antes de chamar o Sort
 */
void configurar_sort_tempo() { modo_ordenacao = 0; }
void configurar_sort_pace() { modo_ordenacao = 1; }

/**
 * Função Auxiliar de Comparação que atende a descrição do projeto
 */
int deve_vir_antes(Atleta a, Atleta b) {
    if (modo_ordenacao == 1) {
        return a.pace < b.pace; // Critério de Aceite: Pace
    }
    return a.tempoSegundos < b.tempoSegundos; // Critério de Aceite: Tempo
}

/* --- QUICK SORT DINÂMICO --- */

No* particionar_dinamico(No* inicio, No* fim) {
    Atleta pivo = fim->dado;
    No* i = inicio;
    No* j = inicio;

    while (j != fim) {
        if (deve_vir_antes(j->dado, pivo)) { 
            Atleta temp = i->dado;
            i->dado = j->dado;
            j->dado = temp;
            i = i->proximo;
        }
        j = j->proximo;
    }
    Atleta temp = i->dado;
    i->dado = fim->dado;
    fim->dado = temp;
    return i;
}

void quick_sort_recursivo_dinamico(No* inicio, No* fim) {
    if (inicio != NULL && fim != NULL && inicio != fim && inicio != fim->proximo) {
        No* pivo = particionar_dinamico(inicio, fim);
        
        No* anterior = inicio;
        while (anterior != NULL && anterior->proximo != pivo) {
            anterior = anterior->proximo;
        }

        if (pivo != inicio)
            quick_sort_recursivo_dinamico(inicio, anterior);
            
        quick_sort_recursivo_dinamico(pivo->proximo, fim);
    }
}

void quick_sort_dinamico(No *inicio, No *fim) {
    if (inicio == NULL || inicio->proximo == NULL) return;
    
    if (fim == NULL) {
        No* cauda = inicio;
        while (cauda->proximo != NULL) cauda = cauda->proximo;
        fim = cauda;
    }
    quick_sort_recursivo_dinamico(inicio, fim);
}

/* --- QUICK SORT ESTÁTICO --- */

int particionar_estatico(NoEstatico lista[], int baixo, int alto) {
    Atleta pivo = lista[alto].dado;
    int i = (baixo - 1);

    for (int j = baixo; j < alto; j++) {
        if (deve_vir_antes(lista[j].dado, pivo)) {
            i++;
            Atleta temp = lista[i].dado;
            lista[i].dado = lista[j].dado;
            lista[j].dado = temp;
        }
    }
    Atleta temp = lista[i + 1].dado;
    lista[i + 1].dado = lista[alto].dado;
    lista[alto].dado = temp;
    return (i + 1);
}

void quick_sort_recursivo_estatico(NoEstatico lista[], int baixo, int alto) {
    if (baixo < alto) {
        int pi = particionar_estatico(lista, baixo, alto);
        quick_sort_recursivo_estatico(lista, baixo, pi - 1);
        quick_sort_recursivo_estatico(lista, pi + 1, alto);
    }
}

void quick_sort_estatico(NoEstatico lista[], int inicio, int fim_logico) {
    if (fim_logico <= 0) return;
    // Ordena do índice 0 até o último elemento inserido no vetor
    quick_sort_recursivo_estatico(lista, 0, fim_logico);
}