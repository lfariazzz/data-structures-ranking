#include "atleta.h"

int main() {
    // 1. Declaração das estruturas para a lista estática
    NoEstatico ranking[MAX];
    int inicio, disponivel;

    // 2. Inicialização (organiza o vetor de espaços livres)
    inicializa_estatica(ranking, &inicio, &disponivel);

    // 3. Criando atletas para o teste
    Atleta a1 = {101, "Levi", 3600.5, 4.5};
    Atleta a2 = {202, "Ana", 3450.2, 4.2};
    Atleta a3 = {303, "Carlos", 3800.0, 4.8};

    // 4. Inserindo no ranking (Simulando a chegada na corrida)
    insere_estatica(ranking, &inicio, &disponivel, a1);
    insere_estatica(ranking, &inicio, &disponivel, a2);
    insere_estatica(ranking, &inicio, &disponivel, a3);

    // 5. Exibindo o resultado final no console
    imprime_estatica(ranking, inicio);

    return 0;
}
