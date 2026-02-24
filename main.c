#include "atleta.h"

int main() {
    // 1. Setup da Estrutura Estática (Pool de 10.000 posições)
    NoEstatico rankingEstatico[MAX];
    int inicio, disponivel;
    inicializa_estatica(rankingEstatico, &inicio, &disponivel);

    // 2. Criando atletas para o teste
    // Exemplo: 5km (5000m) em tempos diferentes
    Atleta a1 = {101, "Levi", 5.0, 1200.0}; // 20:00 min (Pace 4.0)
    Atleta a2 = {202, "Ana", 5.0, 1140.0};  // 19:00 min (Pace 3.8)
    Atleta a3 = {303, "Neto", 5.0, 1320.0}; // 22:00 min (Pace 4.4)

    // 3. Calculando o Pace de cada um (Regra de Negócio do atleta.c)
    calcula_pace(&a1);
    calcula_pace(&a2);
    calcula_pace(&a3);

    // 4. Inserindo na Lista (Gerenciamento do lista_estatica.c)
    // Note que a inserção padrão é no início (LIFO)
    insere_estatica(rankingEstatico, &inicio, &disponivel, a1);
    insere_estatica(rankingEstatico, &inicio, &disponivel, a2);
    insere_estatica(rankingEstatico, &inicio, &disponivel, a3);

    // 5. Atribuindo Posições
    // Em um cenário real, o SORT viria antes disso.
    // Aqui, vamos apenas numerar a ordem atual da lista.
    atribui_posicoes_estatica(rankingEstatico, inicio);

    // 6. Exibindo o Resultado
    imprime_estatica(rankingEstatico, inicio);

    return 0;
}
