#ifndef ORDENACAO_H
#define ORDENACAO_H
 
#include "atleta.h"
#include <stddef.h>   /* size_t */
 
//Algoritmos de ordenacao: recebem vetor de Atletas, tamanho e funcao de comparacao; retornam numero de comparacoes realizadas
 
// Cada algoritmo deve ser implementado de forma a contar o numero de comparacoes feitas entre Atletas usando a funcao de comparacao fornecida.
 
long bubble_sort    (Atleta *v, int n, FuncComparacao cmp);
long insertion_sort (Atleta *v, int n, FuncComparacao cmp);
long selection_sort (Atleta *v, int n, FuncComparacao cmp);
long quick_sort     (Atleta *v, int n, FuncComparacao cmp);
long merge_sort     (Atleta *v, int n, FuncComparacao cmp);
 
// Funcoes auxiliares para os algoritmos de ordenacao recursivos
long _quick_sort_rec (Atleta *v, int esq, int dir, FuncComparacao cmp);
long _merge_sort_rec (Atleta *v, Atleta *aux, int esq, int dir, FuncComparacao cmp);
 
#endif
 