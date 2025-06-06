# Jogo - Batalha Naval ⚓

Projeto em C que posiciona dois navios num tabuleiro 10x10. Desafio básico para treinar matrizes, validação e lógica.

## Como funciona

- O tabuleiro é uma matriz 10x10 preenchida com `0` (água)
- Dois navios são inseridos com valor `3`
  - Um navio horizontal
  - Um navio vertical
- Verifica se cabem no tabuleiro e se não se sobrepõem

## Como rodar

Compile com `gcc`:

```bash
gcc batalhanaval.c -o batalha
./batalha
