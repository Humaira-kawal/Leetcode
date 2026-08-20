#include <stdlib.h>

#define MOD 12345

int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    
    int n = gridSize;
    int m = gridColSize[0];
    int total = n * m;
    
    // Flatten array
    int* arr = (int*)malloc(sizeof(int) * total);
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[idx++] = grid[i][j] % MOD;
        }
    }
    
    // Prefix and suffix
    int* prefix = (int*)malloc(sizeof(int) * total);
    int* suffix = (int*)malloc(sizeof(int) * total);
    
    prefix[0] = 1;
    for (int i = 1; i < total; i++) {
        prefix[i] = (prefix[i - 1] * arr[i - 1]) % MOD;
    }
    
    suffix[total - 1] = 1;
    for (int i = total - 2; i >= 0; i--) {
        suffix[i] = (suffix[i + 1] * arr[i + 1]) % MOD;
    }
    
    // Allocate result matrix
    int** result = (int**)malloc(sizeof(int*) * n);
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    
    idx = 0;
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(sizeof(int) * m);
        (*returnColumnSizes)[i] = m;
        
        for (int j = 0; j < m; j++) {
            result[i][j] = (prefix[idx] * suffix[idx]) % MOD;
            idx++;
        }
    }
    
    *returnSize = n;
    
    // Free temp arrays
    free(arr);
    free(prefix);
    free(suffix);
    
    return result;
}