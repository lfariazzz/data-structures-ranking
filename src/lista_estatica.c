#include "lista_estatica.h"
#include <stdio.h>
#include <string.h>

// Implementação da Lista Encadeada Estática

void le_inicializa(ListaEstatica *lista) {
    lista->cabeca     = LE_NIL;
    lista->tamanho    = 0;
    lista->capacidade = MAX_LISTA_ESTATICA;

    // Inicializa a lista de livres
    for (int i = 0; i < MAX_LISTA_ESTATICA - 1; i++) {
        lista->nos[i].livre   = 1;
        lista->nos[i].proximo = i + 1;
    }
    lista->nos[MAX_LISTA_ESTATICA - 1].livre   = 1;
    lista->nos[MAX_LISTA_ESTATICA - 1].proximo = LE_NIL;

    lista->topo_livre = 0; /* Primeiro slot disponivel */
}

// Aloca um slot; retorna indice ou LE_NIL se cheio
static int alocar_slot(ListaEstatica *lista) {
    if (lista->topo_livre == LE_NIL)
        return LE_NIL;
    int idx          = lista->topo_livre;
    lista->topo_livre = lista->nos[idx].proximo;
    lista->nos[idx].livre   = 0;
    lista->nos[idx].proximo = LE_NIL;
    return idx;
}

// Libera um slot, colocando-o de volta na lista de livres
static void liberar_slot(ListaEstatica *lista, int idx) {
    lista->nos[idx].livre   = 1;
    lista->nos[idx].proximo = lista->topo_livre;
    lista->topo_livre       = idx;
}

// Insere no INICIO: O(1)
int le_insere_inicio(ListaEstatica *lista, Atleta atleta) {
    int idx = alocar_slot(lista);
    if (idx == LE_NIL) {
        fprintf(stderr, "[ERRO] le_insere_inicio: lista estatica cheia.\n");
        return 0;
    }
    lista->nos[idx].dado    = atleta;
    lista->nos[idx].proximo = lista->cabeca;
    lista->cabeca           = idx;
    lista->tamanho++;
    return 1;
}

// Insere no FIM: O(n)
int le_insere_fim(ListaEstatica *lista, Atleta atleta) {
    int idx = alocar_slot(lista);
    if (idx == LE_NIL) {
        fprintf(stderr, "[ERRO] le_insere_fim: lista estatica cheia.\n");
        return 0;
    }
    lista->nos[idx].dado    = atleta;
    lista->nos[idx].proximo = LE_NIL;

    if (lista->cabeca == LE_NIL) {
        lista->cabeca = idx;
    } else {
        int atual = lista->cabeca;
        while (lista->nos[atual].proximo != LE_NIL)
            atual = lista->nos[atual].proximo;
        lista->nos[atual].proximo = idx;
    }
    lista->tamanho++;
    return 1;
}

// Imprime a lista no formato "Posicao | Nome | Tempo | Pace"
void le_imprime(const ListaEstatica *lista) {
    if (lista->cabeca == LE_NIL) {
        printf("[Lista estatica vazia]\n");
        return;
    }
    printf("=== Lista Estatica (%d atletas) ===\n", lista->tamanho);
    int atual = lista->cabeca;
    int i = 1;
    while (atual != LE_NIL) {
        printf("%3d. [slot %4d] ", i++, atual);
        imprimir_atleta(&lista->nos[atual].dado);
        atual = lista->nos[atual].proximo;
    }
    printf("===================================\n");
}

// Busca por numero do dorsal: O(n)
int le_busca(const ListaEstatica *lista, int numero) {
    int atual = lista->cabeca;
    while (atual != LE_NIL) {
        if (lista->nos[atual].dado.numero == numero)
            return atual;
        atual = lista->nos[atual].proximo;
    }
    return LE_NIL;
}

// Remove por numero do dorsal: O(n)
int le_remove(ListaEstatica *lista, int numero) {
    if (lista->cabeca == LE_NIL)
        return 0;

    // Caso especial: remover o primeiro nó
    if (lista->nos[lista->cabeca].dado.numero == numero) {
        int alvo      = lista->cabeca;
        lista->cabeca = lista->nos[alvo].proximo;
        liberar_slot(lista, alvo);
        lista->tamanho--;
        return 1;
    }

    // Busca pelo nó anterior ao que queremos remover
    int anterior = lista->cabeca;
    while (lista->nos[anterior].proximo != LE_NIL &&
           lista->nos[lista->nos[anterior].proximo].dado.numero != numero) {
        anterior = lista->nos[anterior].proximo;
    }

    if (lista->nos[anterior].proximo == LE_NIL)
        return 0; // Não encontrado

    int alvo = lista->nos[anterior].proximo;
    lista->nos[anterior].proximo = lista->nos[alvo].proximo;
    liberar_slot(lista, alvo);
    lista->tamanho--;
    return 1;
}

// Para compatibilidade, embora nao seja necessario liberar memoria em lista estatica
void le_libera(ListaEstatica *lista) {
    le_inicializa(lista); /* Reinicia tudo */
}

// Converte a lista para um vetor (usado para ordenacao)
int le_para_vetor(const ListaEstatica *lista, Atleta *vetor, int max) {
    int i = 0;
    int atual = lista->cabeca;
    while (atual != LE_NIL && i < max) {
        vetor[i++] = lista->nos[atual].dado;
        atual = lista->nos[atual].proximo;
    }
    return i;
}

void le_de_vetor(ListaEstatica *lista, const Atleta *vetor, int n) {
    le_libera(lista);
    for (int i = 0; i < n; i++)
        le_insere_fim(lista, vetor[i]);
}

void le_atualizar_posicoes(ListaEstatica *lista) {
    int atual = lista->cabeca;
    int pos = 1;
    while (atual != LE_NIL) {
        lista->nos[atual].dado.posicao = pos++;
        atual = lista->nos[atual].proximo;
    }
}