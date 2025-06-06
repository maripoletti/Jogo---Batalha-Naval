#include <stdio.h>

// Tamanho fixo do tabuleiro
#define TAMANHO 10
// Valor que representa um navio
#define NAVIO 3
// Tamanho fixo dos navios
#define TAMANHO_NAVIO 3

int main() {
    // Matriz que representa o tabuleiro, inicializada com água (0)
    int tabuleiro[TAMANHO][TAMANHO] = {0};

    // Coordenadas iniciais para o navio horizontal
    int linha_horizontal = 2;
    int coluna_horizontal = 4;

    // Coordenadas iniciais para o navio vertical
    int linha_vertical = 5;
    int coluna_vertical = 7;

    // Verificações: se o navio cabe no tabuleiro (horizontalmente)
    if (coluna_horizontal + TAMANHO_NAVIO > TAMANHO) {
        printf("Erro: navio horizontal fora dos limites!\n");
        return 1;
    }

    // Verificações: se o navio cabe no tabuleiro (verticalmente)
    if (linha_vertical + TAMANHO_NAVIO > TAMANHO) {
        printf("Erro: navio vertical fora dos limites!\n");
        return 1;
    }

    // Verificação de sobreposição
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha_horizontal][coluna_horizontal + i] == NAVIO ||
            tabuleiro[linha_vertical + i][coluna_vertical] == NAVIO) {
            printf("Erro: sobreposição de navios!\n");
            return 1;
        }
    }

    // Posicionando navio horizontal
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_horizontal][coluna_horizontal + i] = NAVIO;
    }

    // Posicionando navio vertical
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha_vertical + i][coluna_vertical] = NAVIO;
    }

    // Exibindo o tabuleiro
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}