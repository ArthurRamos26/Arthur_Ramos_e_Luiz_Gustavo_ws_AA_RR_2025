#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX_N 20
#define INF   INT_MAX

/* Funçoes utilitarias */

void imprimeRota(int *rota, int n, int custo) {
    printf("  Rota: ");
    for (int i = 0; i < n; i++)
        printf("%d -> ", rota[i] + 1);
    printf("%d\n", rota[0] + 1);
    printf("  Custo total: %d\n", custo);
}

void imprimeMatriz(int dist[][MAX_N], int n) {
    printf("  Matriz de distâncias:\n     ");
    for (int i = 0; i < n; i++) printf("%4d", i + 1);
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("  %2d:", i + 1);
        for (int j = 0; j < n; j++)
            printf("%4d", dist[i][j]);
        printf("\n");
    }
}

/* Held-Karp */

int dp[1 << MAX_N][MAX_N];
int pai[1 << MAX_N][MAX_N];

void caixeiroHeldKarp(int dist[][MAX_N], int n,
                      int *custoOtimo, int *rotaOtima) {
    int total = 1 << n;

    /* Inicializa tabela */
    for (int s = 0; s < total; s++)
        for (int i = 0; i < n; i++) {
            dp[s][i]  = INF;
            pai[s][i] = -1;
        }

    dp[1][0] = 0;   /* cidade 0 visitada, custo 0 */

    /* Preenche a tabela para todos os subconjuntos */
    for (int s = 1; s < total; s++) {
        for (int u = 0; u < n; u++) {
            if (!(s & (1 << u))) continue;  /* u não está em s */
            if (dp[s][u] == INF)  continue;

            for (int v = 0; v < n; v++) {
                if (s & (1 << v))      continue; /* v já visitado */
                if (dist[u][v] == INF) continue;

                int ns       = s | (1 << v);
                int novoCusto = dp[s][u] + dist[u][v];

                if (novoCusto < dp[ns][v]) {
                    dp[ns][v]  = novoCusto;
                    pai[ns][v] = u;
                }
            }
        }
    }

    /* Encontra o melhor nó final antes de voltar à cidade 0 */
    int full   = total - 1;
    *custoOtimo = INF;
    int ultimo = -1;

    for (int u = 1; u < n; u++) {
        if (dp[full][u] == INF)    continue;
        if (dist[u][0]  == INF)    continue;
        int c = dp[full][u] + dist[u][0];
        if (c < *custoOtimo) {
            *custoOtimo = c;
            ultimo = u;
        }
    }

    /* Reconstrói a rota pelo caminho dos pais */
    int idx = n - 1;
    int s   = full;
    int cur = ultimo;
    rotaOtima[idx--] = cur;

    while (cur != 0) {
        int prev = pai[s][cur];
        s ^= (1 << cur);
        cur = prev;
        rotaOtima[idx--] = cur;
    }
}

/* EXPERIMENTO*/

void geraMatrizAleatoria(int dist[][MAX_N], int n, int maxDist) {
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
        for (int j = i + 1; j < n; j++) {
            int d = (rand() % maxDist) + 1;
            dist[i][j] = dist[j][i] = d;
        }
    }
}

void experimento() {
    printf("\n========================================\n");
    printf("  EXPERIMENTO - Tempo de Execução\n");
    printf("========================================\n");
    printf("  %-8s %-20s\n", "Cidades", "Held-Karp (s)");
    printf("  %-8s %-20s\n", "-------", "-------------");

    int dist[MAX_N][MAX_N];

    for (int n = 3; n <= 18; n++) {
        srand(42 + n);
        geraMatrizAleatoria(dist, n, 100);

        int custo, rota[MAX_N];
        clock_t ini = clock();
        caixeiroHeldKarp(dist, n, &custo, rota);
        clock_t fim = clock();
        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("  %-8d %-20.6f\n", n, tempo);
    }
}

/*MAIN*/

int main(void) {
    printf("============================================\n");
    printf("  CAIXEIRO VIAJANTE com o Held-Karp\n");
    printf("============================================\n\n");

    int n = 5;
    int dist[MAX_N][MAX_N] = {
        {  0, 10, 15, 20, 25 },
        { 10,  0, 35, 25, 30 },
        { 15, 35,  0, 30, 10 },
        { 20, 25, 30,  0, 15 },
        { 25, 30, 10, 15,  0 }
    };

    printf("Número de cidades: %d\n\n", n);
    imprimeMatriz(dist, n);

    printf("\n--- Resultado ---\n");
    int custoOtimo, rotaOtima[MAX_N];
    clock_t t1 = clock();
    caixeiroHeldKarp(dist, n, &custoOtimo, rotaOtima);
    clock_t t2 = clock();

    imprimeRota(rotaOtima, n, custoOtimo);
    printf("  Tempo: %.6f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    experimento();

    return 0;
}