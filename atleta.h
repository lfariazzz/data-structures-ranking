#ifndef ATLETA_H
#define ATLETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 1. Definição do Objeto Real [cite: 17, 20] */
typedef struct {
    int numeroPeito;
    char nome[50];
    double tempoSegundos; // Critério de ordenação 1
    double pace;          // Critério de ordenação 2
} Atleta;

/* 2. Estrutura para Lista Encadeada Dinâmica [cite: 26] */
typedef struct No {
    Atleta dado;
    struct No *proximo;
} No;

/* 3. Estrutura para Lista Encadeada Estática  */
#define MAX 10000 // Volume exigido para testes grandes [cite: 36]
typedef struct {
    Atleta dado;
    int proximo; // Índice para o próximo elemento
} NoEstatico;

/* 4. Funções de Gerenciamento das Listas [cite: 27, 28] */

// Dinâmica
void inicializa_dinamica(No **inicio);
int insere_dinamica(No **inicio, Atleta a);
void imprime_dinamica(No *inicio);
void libera_dinamica(No **inicio);

// Estática (Gerenciamento manual de posições livres )
void inicializa_estatica(NoEstatico lista[], int *inicio, int *disponivel);
int insere_estatica(NoEstatico lista[], int *inicio, int *disponivel, Atleta a);
void imprime_estatica(NoEstatico lista[], int inicio);

/* 5. Algoritmos de Ordenação a Implementar [cite: 24] */
/* Critério: 1 para Tempo, 2 para Pace  */

// Versões para Lista Dinâmica
void bubble_sort_dinamico(No **inicio, int criterio);
void insertion_sort_dinamico(No **inicio, int criterio);
void selection_sort_dinamico(No **inicio, int criterio);
void quick_sort_dinamico(No **inicio, int criterio);
void merge_sort_dinamico(No **inicio, int criterio);

// Versões para Lista Estática
void bubble_sort_estatico(NoEstatico lista[], int inicio, int criterio);
void insertion_sort_estatico(NoEstatico lista[], int inicio, int criterio);
void selection_sort_estatico(NoEstatico lista[], int inicio, int criterio);
void quick_sort_estatico(NoEstatico lista[], int inicio, int criterio);
void merge_sort_estatico(NoEstatico lista[], int inicio, int criterio);

#endif
