#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define TAMANHO_NAVIO 3

// Função para verificar se o navio cabe dentro do tabuleiro
// considerando direção: 'H' = horizontal, 'V' = vertical, 'D' = diagonal
int cabeNoTabuleiro(int linha, int coluna, char direcao) {
    switch (direcao) {
        case 'H': // horizontal, avança coluna
            return (coluna + TAMANHO_NAVIO <= TAMANHO);
        case 'V': // vertical, avança linha
            return (linha + TAMANHO_NAVIO <= TAMANHO);
        case 'D': // diagonal, avança linha e coluna
            return (linha + TAMANHO_NAVIO <= TAMANHO && coluna + TAMANHO_NAVIO <= TAMANHO);
        default:
            return 0;
    }
}

// Função para checar sobreposição
// retorna 1 se houver sobreposição, 0 caso contrário
int verificaSobreposicao(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        switch (direcao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
        }
        if (tabuleiro[l][c] == NAVIO) {
            return 1;
        }
    }
    return 0;
}

// Função para posicionar o navio no tabuleiro
void posicionaNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        switch (direcao) {
            case 'H': c += i; break;
            case 'V': l += i; break;
            case 'D': l += i; c += i; break;
        }
        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO] = {0};  // Inicializa com água

    // Definições dos navios: linha, coluna, direção
    // 2 navios horizontais/verticais:
    int naviosHV[2][3] = {
        {2, 4, 'H'}, // linha 2, coluna 4, horizontal
        {5, 7, 'V'}  // linha 5, coluna 7, vertical
    };

    // 2 navios diagonais:
    int naviosD[2][3] = {
        {0, 0, 'D'}, // diagonal começando no canto superior esquerdo
        {4, 5, 'D'}  // diagonal qualquer dentro do tabuleiro
    };

    // Posicionar navios horizontais/verticais
    for (int i = 0; i < 2; i++) {
        int linha = naviosHV[i][0];
        int coluna = naviosHV[i][1];
        char direcao = (char)naviosHV[i][2];

        if (!cabeNoTabuleiro(linha, coluna, direcao)) {
            printf("Erro: navio HV %d fora dos limites!\n", i+1);
            return 1;
        }
        if (verificaSobreposicao(tabuleiro, linha, coluna, direcao)) {
            printf("Erro: navio HV %d sobreposto!\n", i+1);
            return 1;
        }
        posicionaNavio(tabuleiro, linha, coluna, direcao);
    }

    // Posicionar navios diagonais
    for (int i = 0; i < 2; i++) {
        int linha = naviosD[i][0];
        int coluna = naviosD[i][1];
        char direcao = (char)naviosD[i][2];

        if (!cabeNoTabuleiro(linha, coluna, direcao)) {
            printf("Erro: navio diagonal %d fora dos limites!\n", i+1);
            return 1;
        }
        if (verificaSobreposicao(tabuleiro, linha, coluna, direcao)) {
            printf("Erro: navio diagonal %d sobreposto!\n", i+1);
            return 1;
        }
        posicionaNavio(tabuleiro, linha, coluna, direcao);
    }

    // Mostrar tabuleiro
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
