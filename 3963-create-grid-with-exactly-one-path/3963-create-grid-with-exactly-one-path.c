
#include <stdlib.h>

char** createGrid(int m, int n, int* returnSize) {
    char** grid = (char**)malloc(m * sizeof(char*));
    *returnSize = m;

    for (int i = 0; i < m; i++) {
        grid[i] = (char*)malloc((n + 1) * sizeof(char));

        for (int j = 0; j < n; j++) {
            if (i == 0 || j == n - 1) {
                grid[i][j] = '.';
            } else {
                grid[i][j] = '#';
            }
        }

        grid[i][n] = '\0';
    }

    return grid;
}
