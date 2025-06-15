#include <stdio.h>
#include <stdlib.h> // Para abs()

// Constantes
#define TAMANHO 10
#define TAM_HABILIDADE 5

#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5

// Inicializa todo o tabuleiro com água
void inicializaTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = AGUA;
}

// Imprime o tabuleiro com coordenadas e legenda
void imprimeTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nLegenda: ~ = Água | N = Navio | * = Habilidade\n\n    ");
    for (int j = 0; j < TAMANHO; j++) printf("%2d", j);
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%2d |", i);
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == AGUA) printf("~ ");
            else if (tabuleiro[i][j] == NAVIO) printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
            else printf("? ");
        }
        printf("\n");
    }
}

// Posiciona um navio 3x1 nas direções Horizontal, Vertical ou Diagonal (D)
void posicionaNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }

        // Garante que não passa dos limites
        if (l >= 0 && l < TAMANHO && c >= 0 && c < TAMANHO)
            tabuleiro[l][c] = NAVIO;
    }
}

// Cria uma matriz cone 5x5 com a "ponta" para cima (expande pra baixo)
void geraCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == 0 && j == 2) matriz[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) matriz[i][j] = 1;
            else if (i == 2) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// Cria matriz em formato de cruz (linha e coluna central ativas)
void geraCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
        }
    }
}

// Cria matriz octaedro (losango) com origem no centro
void geraOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (abs(2 - i) + abs(2 - j) <= 2) ? 1 : 0;
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro com origem centralizada
void aplicaHabilidade(int tabuleiro[TAMANHO][TAMANHO], int origemLinha, int origemColuna, int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int l = origemLinha + (i - 2);
            int c = origemColuna + (j - 2);
            if (l >= 0 && l < TAMANHO && c >= 0 && c < TAMANHO) {
                // Só marca se não for navio
                if (matriz[i][j] == 1 && tabuleiro[l][c] != NAVIO) {
                    tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializaTabuleiro(tabuleiro);

    // Posiciona navios em diferentes orientações
    posicionaNavio(tabuleiro, 1, 1, 'H'); // Horizontal
    posicionaNavio(tabuleiro, 6, 3, 'V'); // Vertical
    posicionaNavio(tabuleiro, 4, 4, 'D'); // Diagonal

    // Matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    // Geração dinâmica das matrizes
    geraCone(cone);
    geraCruz(cruz);
    geraOctaedro(octaedro);

    // Aplicação das habilidades em posições específicas
    aplicaHabilidade(tabuleiro, 3, 3, cone);        // Centro do cone
    aplicaHabilidade(tabuleiro, 7, 2, cruz);        // Centro da cruz
    aplicaHabilidade(tabuleiro, 5, 7, octaedro);    // Centro do octaedro

    // Exibe o tabuleiro final
    imprimeTabuleiro(tabuleiro);

    return 0;
}