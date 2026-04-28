
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX_N 12
#define INF   INT_MAX

/* Funções utilitárias */

void swap(int *a, int *b) {
    int tmp = *a; *a = *b; *b = tmp;
}

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

/* 
   FORÇA BRUTA  */

int dist_fb[MAX_N][MAX_N];
int melhorCusto;
int melhorRota[MAX_N];
int n_cidades;

int calculaCusto(int *perm, int n) {
    int custo = 0;
    for (int i = 0; i < n - 1; i++) {
        if (dist_fb[perm[i]][perm[i+1]] == INF) return INF;
        custo += dist_fb[perm[i]][perm[i+1]];
    }
    if (dist_fb[perm[n-1]][perm[0]] == INF) return INF;
    custo += dist_fb[perm[n-1]][perm[0]];
    return custo;
}

/* Gera todas as permutações via Heap's Algorithm */
void permutacoes(int *arr, int k, int n) {
    if (k == 1) {
        int custo = calculaCusto(arr, n);
        if (custo < melhorCusto) {
            melhorCusto = custo;
            memcpy(melhorRota, arr, n * sizeof(int));
        }
        return;
    }
    permutacoes(arr, k - 1, n);
    for (int i = 0; i < k - 1; i++) {
        if (k % 2 == 0) swap(&arr[i], &arr[k-1]);
        else             swap(&arr[0], &arr[k-1]);
        permutacoes(arr, k - 1, n);
    }
}

void caixeiroForcaBruta(int dist[][MAX_N], int n) {
    n_cidades = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist_fb[i][j] = dist[i][j];

    int cidades[MAX_N];
    for (int i = 0; i < n; i++) cidades[i] = i;

    melhorCusto = INF;
    permutacoes(cidades, n, n);
}

/* 
   EXPERIMENTO
*/

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
    printf("  %-8s %-20s\n", "Cidades", "Força Bruta (s)");
    printf("  %-8s %-20s\n", "-------", "---------------");

    int dist[MAX_N][MAX_N];

    for (int n = 3; n <= 11; n++) {
        srand(42 + n);
        geraMatrizAleatoria(dist, n, 100);

        if (n > 10) {
            printf("  %-8d %-20s\n", n, "> tempo limite");
            continue;
        }

        clock_t ini = clock();
        caixeiroForcaBruta(dist, n);
        clock_t fim = clock();
        double tempo = (double)(fim - ini) / CLOCKS_PER_SEC;

        printf("  %-8d %-20.6f\n", n, tempo);
    }
}

/* 
   MAIN
*/

int main(void) {
    printf("============================================\n");
    printf("  CAIXEIRO VIAJANTE - Força Bruta  O(n!)\n");
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
    clock_t t1 = clock();
    caixeiroForcaBruta(dist, n);
    clock_t t2 = clock();

    imprimeRota(melhorRota, n, melhorCusto);
    printf("  Tempo: %.6f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

    experimento();

    printf("\n============================================\n");
    printf("  Complexidade: O(n!)\n");
    printf("  Função de custo: T(n) = n! operações\n");
    printf("============================================\n");

    return 0;
}
