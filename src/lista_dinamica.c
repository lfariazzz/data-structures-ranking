#include "lista_dinamica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Implementação da Lista Encadeada Dinâmica

void ld_inicializa(ListaDinamica *lista) {
    lista->cabeca   = NULL;
    lista->tamanho  = 0;
}

// Insere no INICIO: O(1)
int ld_insere_inicio(ListaDinamica *lista, Atleta atleta) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] ld_insere_inicio: malloc falhou.\n");
        return 0;
    }
    novo->dado = atleta;
    novo->prox = lista->cabeca;
    lista->cabeca = novo;
    lista->tamanho++;
    return 1;
}

// Insere no FIM: O(n)
int ld_insere_fim(ListaDinamica *lista, Atleta atleta) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        fprintf(stderr, "[ERRO] ld_insere_fim: malloc falhou.\n");
        return 0;
    }
    novo->dado = atleta;
    novo->prox = NULL;

    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
    } else {
        No *atual = lista->cabeca;
        while (atual->prox != NULL)
            atual = atual->prox;
        atual->prox = novo;
    }
    lista->tamanho++;
    return 1;
}

// Imprime a lista no formato "Posicao | Nome | Tempo | Pace"
void ld_imprime(const ListaDinamica *lista) {
    if (lista->cabeca == NULL) {
        printf("[Lista dinamica vazia]\n");
        return;
    }
    printf("=== Lista Dinamica (%d atletas) ===\n", lista->tamanho);
    No *atual = lista->cabeca;
    int i = 1;
    while (atual != NULL) {
        printf("%3d. ", i++);
        imprimir_atleta(&atual->dado);
        atual = atual->prox;
    }
    printf("===================================\n");
}

// Busca por numero do dorsal: O(n)
No *ld_busca(const ListaDinamica *lista, int numero) {
    No *atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->dado.numero == numero)
            return atual;
        atual = atual->prox;
    }
    return NULL;
}

// Remove por numero do dorsal: O(n)
int ld_remove(ListaDinamica *lista, int numero) {
    if (lista->cabeca == NULL)
        return 0;

    // Caso especial: remover o primeiro nó
    if (lista->cabeca->dado.numero == numero) {
        No *temp = lista->cabeca;
        lista->cabeca = lista->cabeca->prox;
        free(temp);
        lista->tamanho--;
        return 1;
    }

    // Busca pelo nó anterior ao que queremos remover
    No *anterior = lista->cabeca;
    while (anterior->prox != NULL &&
           anterior->prox->dado.numero != numero) {
        anterior = anterior->prox;
    }

    if (anterior->prox == NULL)
        return 0; // Não encontrado

    No *alvo = anterior->prox;
    anterior->prox = alvo->prox;
    free(alvo);
    lista->tamanho--;
    return 1;
}

// Libera toda a memória alocada para a lista
void ld_libera(ListaDinamica *lista) {
    No *atual = lista->cabeca;
    while (atual != NULL) {
        No *prox = atual->prox;
        free(atual);
        atual = prox;
    }
    lista->cabeca  = NULL;
    lista->tamanho = 0;
}

// Converte a lista para um vetor (usado para ordenacao)
int ld_para_vetor(const ListaDinamica *lista, Atleta *vetor, int max) {
    int i = 0;
    No *atual = lista->cabeca;
    while (atual != NULL && i < max) {
        vetor[i++] = atual->dado;
        atual = atual->prox;
    }
    return i;
}

// Reconstrói a lista a partir de um vetor ordenado
void ld_de_vetor(ListaDinamica *lista, const Atleta *vetor, int n) {
    ld_libera(lista);
    for (int i = 0; i < n; i++)
        ld_insere_fim(lista, vetor[i]);
}

// Recalcula posicoes com base na ordem atual da lista
void ld_atualizar_posicoes(ListaDinamica *lista) {
    No *atual = lista->cabeca;
    int pos = 1;
    while (atual != NULL) {
        atual->dado.posicao = pos++;
        atual = atual->prox;
    }
}