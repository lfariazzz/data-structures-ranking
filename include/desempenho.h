#ifndef DESEMPENHO_H
#define DESEMPENHO_H

#include "atleta.h"
#include "lista_dinamica.h"
#include "lista_estatica.h"
#include "ordenacao.h"

typedef int (*CmpFn)(const Atleta*, const Atleta*);

typedef enum {
    ENTRADA_ALEATORIO    = 0,
    ENTRADA_ORDENADO     = 1,
    ENTRADA_INV_ORDENADO = 2
} TipoEntrada;

typedef struct {
    long   comparacoes;
    double tempo_ns;
} ResultadoExec;

typedef struct {
    double media_tempo_ns;
    double media_comparacoes;
    double desvio_tempo_ns;
} ResultadoAgregado;

void gerar_entrada(Atleta *v, int n, TipoEntrada tipo);

ResultadoAgregado medir_sort_vetor(
    long (*sort)(Atleta*, int, CmpFn),
    int n, TipoEntrada tipo, CmpFn cmp, int repeticoes);

ResultadoAgregado medir_sort_lista_dinamica(
    long (*sort)(Atleta*, int, CmpFn),
    int n, TipoEntrada tipo, CmpFn cmp, int repeticoes);

ResultadoAgregado medir_sort_lista_estatica(
    long (*sort)(Atleta*, int, CmpFn),
    int n, TipoEntrada tipo, CmpFn cmp, int repeticoes);

void imprimir_cabecalho_csv(void);

void imprimir_linha_csv(
    const char *algoritmo,
    const char *estrutura,
    int n,
    const char *tipo_entrada,
    const ResultadoAgregado *res);

void executar_bateria_completa(int repeticoes);

#endif