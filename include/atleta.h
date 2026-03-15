#ifndef ATLETA_H
#define ATLETA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 64
#define MAX 10010
#define MAX_LISTA_ESTATICA 10010

typedef enum {
    ATIVO      = 0,
    FINALIZADO = 1,
    DNF        = 2
} StatusAtleta;

typedef struct {
    int numero;
    char nome[MAX_NOME];
    float tempo_segundos;
    float pace;
    float distancia_km;
    int posicao;
    StatusAtleta status;
} Atleta;

typedef enum {
    CRITERIO_POSICAO   = 0,
    CRITERIO_PACE      = 1,
    CRITERIO_TEMPO     = 2,
    CRITERIO_NOME      = 3,
    CRITERIO_NUMERO    = 4,
    CRITERIO_DISTANCIA = 5
} CriterioOrdenacao;

typedef int (*FuncComparacao)(const Atleta *a, const Atleta *b);

FuncComparacao obter_comparador(CriterioOrdenacao criterio);

int cmp_posicao  (const Atleta *a, const Atleta *b);
int cmp_pace     (const Atleta *a, const Atleta *b);
int cmp_tempo    (const Atleta *a, const Atleta *b);
int cmp_nome     (const Atleta *a, const Atleta *b);
int cmp_numero   (const Atleta *a, const Atleta *b);
int cmp_distancia(const Atleta *a, const Atleta *b);

void imprimir_atleta(const Atleta *a);
void gerar_atleta_aleatorio(Atleta *a, int numero);

#endif