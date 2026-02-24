#include "atleta.h"

void inicializa_estatica(NoEstatico lista[], int *inicio, int *disponivel) {
    *inicio = -1;
    *disponivel = 0;
    for (int i = 0; i < MAX - 1; i++) {
        lista[i].proximo = i + 1;
    }
    lista[MAX - 1].proximo = -1;
}

int insere_estatica(NoEstatico lista[], int *inicio, int *disponivel, Atleta a) {
    if (*disponivel == -1) return 0;
    int novo = *disponivel;
    *disponivel = lista[novo].proximo;
    lista[novo].dado = a;
    lista[novo].proximo = *inicio;
    *inicio = novo;
    return 1;
}

void atribui_posicoes_estatica(NoEstatico lista[], int inicio) {
    int i = inicio;
    int p = 1;
    while (i != -1) {
        lista[i].dado.posicao = p++;
        i = lista[i].proximo;
    }
}

void imprime_estatica(NoEstatico lista[], int inicio) {
    int i = inicio;
    printf("\n--- RANKING ESTÁTICO ---\n");
    if (inicio == -1) printf("Lista vazia.\n");
    while (i != -1) {
        printf("%dº | %-15s | Tempo: %.1fs | Pace: %.2f\n",
               lista[i].dado.posicao, lista[i].dado.nome,
               lista[i].dado.tempoSegundos, lista[i].dado.pace);
        i = lista[i].proximo;
    }
}
