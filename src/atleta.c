#include "atleta.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
// Comparadores para os diferentes critérios de ordenação
 
int cmp_posicao(const Atleta *a, const Atleta *b) {
    return a->posicao - b->posicao;
}
 
int cmp_pace(const Atleta *a, const Atleta *b) {
    // Menor pace = primeiro (atleta mais rápido)
    if (a->pace < b->pace) return -1;
    if (a->pace > b->pace) return  1;
    return 0;
}
 
int cmp_tempo(const Atleta *a, const Atleta *b) {
    if (a->tempo_segundos < b->tempo_segundos) return -1;
    if (a->tempo_segundos > b->tempo_segundos) return  1;
    return 0;
}
 
int cmp_nome(const Atleta *a, const Atleta *b) {
    return strncmp(a->nome, b->nome, MAX_NOME);
}
 
int cmp_numero(const Atleta *a, const Atleta *b) {
    return a->numero - b->numero;
}
 
int cmp_distancia(const Atleta *a, const Atleta *b) {
    // Maior distância = primeiro (atleta mais avançado)
    if (a->distancia_km > b->distancia_km) return -1;
    if (a->distancia_km < b->distancia_km) return  1;
    return 0;
}
 
FuncComparacao obter_comparador(CriterioOrdenacao criterio) {
    switch (criterio) {
        case CRITERIO_POSICAO:   return cmp_posicao;
        case CRITERIO_PACE:      return cmp_pace;
        case CRITERIO_TEMPO:     return cmp_tempo;
        case CRITERIO_NOME:      return cmp_nome;
        case CRITERIO_NUMERO:    return cmp_numero;
        case CRITERIO_DISTANCIA: return cmp_distancia;
        default:                 return cmp_posicao;
    }
}
 
// Utilitário para imprimir um atleta (usado para debug e visualização)

static const char *status_str(StatusAtleta s) {
    switch (s) {
        case ATIVO:       return "ATIVO";
        case FINALIZADO:  return "FINALIZADO";
        case DNF:         return "DNF";
        default:          return "?";
    }
}
 
void imprimir_atleta(const Atleta *a) {
    int min  = (int)(a->tempo_segundos / 60);
    int seg  = (int)(a->tempo_segundos) % 60;
    printf(
        "#%-4d | %-24s | Tempo: %02d:%02ds | Pace: %.2f min/km | "
        "Dist: %5.2f km | Pos: %4d | [%s]\n",
        a->numero,
        a->nome,
        min, seg,
        a->pace,
        a->distancia_km,
        a->posicao,
        status_str(a->status)
    );
}
 
// Gerador de atletas aleatórios usando IA para testes e simulações
static const char *nomes_base[] = {
    "Carlos","Ana","Pedro","Maria","Lucas","Julia","Bruno","Fernanda",
    "Rafael","Beatriz","Diego","Camila","Thiago","Larissa","Mateus","Gabriela",
    "Felipe","Isabela","Rodrigo","Amanda","Andre","Patricia","Guilherme","Mariana",
    "Victor","Leticia","Leonardo","Carolina","Eduardo","Vanessa","Marcelo","Renata",
    "Henrique","Aline","Fabio","Priscila","Roberto","Simone","Paulo","Debora"
};
#define N_NOMES (int)(sizeof(nomes_base)/sizeof(nomes_base[0]))
 
static const char *sobrenomes_base[] = {
    "Silva","Santos","Oliveira","Souza","Lima","Pereira","Costa","Ferreira",
    "Rodrigues","Almeida","Nascimento","Carvalho","Gomes","Martins","Araujo","Dias",
    "Barbosa","Ribeiro","Rocha","Cardoso","Mendes","Freitas","Teixeira","Moreira",
    "Moraes","Correia","Nunes","Azevedo","Monteiro","Neto","Vieira","Pinto"
};
#define N_SOBRENOMES (int)(sizeof(sobrenomes_base)/sizeof(sobrenomes_base[0]))
 
void gerar_atleta_aleatorio(Atleta *a, int numero) {
    a->numero = numero;
 
    // Gerar nome aleatório combinando um nome e um sobrenome
    snprintf(a->nome, MAX_NOME, "%s %s",
             nomes_base[rand() % N_NOMES],
             sobrenomes_base[rand() % N_SOBRENOMES]);
 
    // Gerar tempo, pace e distância aleatórios dentro de faixas realistas
    a->distancia_km   = ((float)(rand() % 1000)) / 100.0f;   /* 0.00 .. 9.99 km */
    a->pace           = 4.0f + ((float)(rand() % 400)) / 100.0f; /* 4.00 .. 8.00   */
    a->tempo_segundos = a->distancia_km * a->pace * 60.0f;
 
    // Gerar status aleatório com maior probabilidade de ser ATIVO
    int r = rand() % 100;
    if      (r < 80)  a->status = ATIVO;
    else if (r < 95)  a->status = FINALIZADO;
    else              a->status = DNF;
 
    a->posicao = 0; // Será atualizado posteriormente com base na ordenação por tempo/pace/distância
}