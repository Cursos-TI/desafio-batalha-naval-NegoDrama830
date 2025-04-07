#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Inicializa o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = AGUA;
}

// Exibe o tabuleiro com representação visual
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA) printf("~ ");
            else if (tabuleiro[i][j] == NAVIO) printf("# ");
            else if (tabuleiro[i][j] == HABILIDADE) printf("* ");
        }
        printf("\n");
    }
}

// Verifica se pode posicionar o navio
int podePosicionar(int tabuleiro[TAM][TAM], int linha[], int coluna[]) {
    for (int i = 0; i < 3; i++) {
        int l = linha[i], c = coluna[i];
        if (l < 0 || l >= TAM || c < 0 || c >= TAM || tabuleiro[l][c] != AGUA)
            return 0;
    }
    return 1;
}

// Posiciona o navio
void posicionarNavio(int tabuleiro[TAM][TAM], int linha[], int coluna[]) {
    for (int i = 0; i < 3; i++)
        tabuleiro[linha[i]][coluna[i]] = NAVIO;
}

// Aplica a matriz de habilidade ao tabuleiro
void aplicarHabilidade(int tabuleiro[TAM][TAM], int matriz[TAM_HAB][TAM_HAB], int origemLinha, int origemColuna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (matriz[i][j] == 1) {
                int linhaTab = origemLinha - TAM_HAB / 2 + i;
                int colunaTab = origemColuna - TAM_HAB / 2 + j;
                if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                    if (tabuleiro[linhaTab][colunaTab] == AGUA)
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                }
            }
        }
    }
}

// Gera uma matriz cone para habilidade
void gerarMatrizCone(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(j - TAM_HAB / 2) <= i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera uma matriz cruz
void gerarMatrizCruz(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Gera uma matriz octaedro (losango)
void gerarMatrizOctaedro(int matriz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (abs(i - TAM_HAB / 2) + abs(j - TAM_HAB / 2) <= TAM_HAB / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // ---------------- Posicionar Navios ----------------
    int linha1[] = {1, 1, 1}, coluna1[] = {2, 3, 4}; // horizontal
    int linha2[] = {5, 6, 7}, coluna2[] = {0, 0, 0}; // vertical

    if (podePosicionar(tabuleiro, linha1, coluna1)) posicionarNavio(tabuleiro, linha1, coluna1);
    if (podePosicionar(tabuleiro, linha2, coluna2)) posicionarNavio(tabuleiro, linha2, coluna2);

    // ---------------- Matrizes de Habilidade ----------------
    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];

    gerarMatrizCone(cone);
    gerarMatrizCruz(cruz);
    gerarMatrizOctaedro(octaedro);

    // ---------------- Aplicar Habilidades ----------------
    aplicarHabilidade(tabuleiro, cone, 2, 2);        // origem no topo esquerdo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);        // centro do tabuleiro
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);    // canto inferior direito

    // ---------------- Mostrar Tabuleiro Final ----------------
    exibirTabuleiro(tabuleiro);

    return 0;
}
