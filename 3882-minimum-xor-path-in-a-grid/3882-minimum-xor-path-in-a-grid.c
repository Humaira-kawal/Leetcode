
#include <stdlib.h>
#include <string.h>

int minCost(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int K = 1024;

    unsigned char *dp = calloc((size_t)2 * n * K, sizeof(unsigned char));

    if (dp == NULL) return 0;

    for (int i = 0; i < m; i++) {
        int cur = (i % 2) * n * K;
        int prev = (1 - i % 2) * n * K;

        for (int j = 0; j < n; j++) {
            unsigned char *cell = dp + cur + j * K;
            memset(cell, 0, K * sizeof(unsigned char));

            int val = grid[i][j];

            if (i == 0 && j == 0) {
                cell[val] = 1;
                continue;
            }

            if (i > 0) {
                unsigned char *above = dp + prev + j * K;

                for (int x = 0; x < K; x++) {
                    if (above[x])
                        cell[x ^ val] = 1;
                }
            }

            if (j > 0) {
                unsigned char *left = dp + cur + (j - 1) * K;

                for (int x = 0; x < K; x++) {
                    if (left[x])
                        cell[x ^ val] = 1;
                }
            }
        }
    }

    int lastRow = ((m - 1) % 2) * n * K;
    unsigned char *lastCell = dp + lastRow + (n - 1) * K;

    for (int x = 0; x < K; x++) {
        if (lastCell[x]) {
            free(dp);
            return x;
        }
    }

    free(dp);
    return 0;
}
