#include <stdio.h>

#define TAMANHO 10
#define NAVIO 3
#define HABILIDADE 5

// Função para inicializar o tabuleiro
void inicializaTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    for (int i = 0; i < TAMANHO; i++)
        for (int j = 0; j < TAMANHO; j++)
            tabuleiro[i][j] = 0;
}

// Função para imprimir o tabuleiro com legenda
void imprimeTabuleiro(int tabuleiro[TAMANHO][TAMANHO]) {
    printf("\nLegenda: ~ = Água | N = Navio | * = Habilidade\n\n");
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");
            else if (tabuleiro[i][j] == NAVIO) printf("N ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
            else printf("? ");
        }
        printf("\n");
    }
}

// Posiciona um navio 3x1 em qualquer direção
void posicionaNavio(int tabuleiro[TAMANHO][TAMANHO], int linha, int coluna, char direcao) {
    for (int i = 0; i < 3; i++) {
        int l = linha, c = coluna;
        if (direcao == 'H') c += i;
        else if (direcao == 'V') l += i;
        else if (direcao == 'D') { l += i; c += i; }
        tabuleiro[l][c] = NAVIO;
    }
}

// Gera matriz de habilidade cone 5x5 (ponta para baixo)
void geraCone(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == 0 && j == 2) matriz[i][j] = 1;
            else if (i == 1 && j >= 1 && j <= 3) matriz[i][j] = 1;
            else if (i == 2 && j >= 0 && j <= 4) matriz[i][j] = 1;
            else matriz[i][j] = 0;
        }
    }
}

// Gera matriz de habilidade cruz 5x5
void geraCruz(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (i == 2 || j == 2) ? 1 : 0;
        }
    }
}

// Gera matriz de habilidade octaedro (losango) 5x5
void geraOctaedro(int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matriz[i][j] = (abs(2 - i) + abs(2 - j) <= 2) ? 1 : 0;
        }
    }
}

// Aplica uma matriz de habilidade ao tabuleiro, centrando na origem
void aplicaHabilidade(int tabuleiro[TAMANHO][TAMANHO], int origemLinha, int origemColuna, int matriz[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            int l = origemLinha + (i - 2);
            int c = origemColuna + (j - 2);
            if (l >= 0 && l < TAMANHO && c >= 0 && c < TAMANHO && matriz[i][j] == 1 && tabuleiro[l][c] != NAVIO) {
                tabuleiro[l][c] = HABILIDADE;
            }
        }
    }
}

int main() {
    int tabuleiro[TAMANHO][TAMANHO];
    inicializaTabuleiro(tabuleiro);

    // Posicionando alguns navios
    posicionaNavio(tabuleiro, 1, 1, 'H');
    posicionaNavio(tabuleiro, 6, 3, 'V');
    posicionaNavio(tabuleiro, 4, 4, 'D');

    // Matrizes de habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];
    geraCone(cone);
    geraCruz(cruz);
    geraOctaedro(octaedro);

    // Aplicando habilidades em pontos definidos
    aplicaHabilidade(tabuleiro, 3, 3, cone);        // centro do cone
    aplicaHabilidade(tabuleiro, 7, 2, cruz);        // centro da cruz
    aplicaHabilidade(tabuleiro, 5, 7, octaedro);    // centro do losango

    // Imprimindo tabuleiro
    imprimeTabuleiro(tabuleiro);

    return 0;
}
