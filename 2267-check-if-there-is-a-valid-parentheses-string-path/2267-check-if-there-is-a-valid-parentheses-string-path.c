#include <stdbool.h>
#include <stdlib.h>

bool hasValidPath(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    // A valid parentheses string must have even length
    int len = m + n - 1;
    if (len % 2 != 0)
        return false;

    // dp[j][balance] = whether we can reach current row, column j
    // with the given balance.
    bool ***dp = malloc(m * sizeof(bool **));

    for (int i = 0; i < m; i++) {
        dp[i] = malloc(n * sizeof(bool *));
        for (int j = 0; j < n; j++) {
            dp[i][j] = calloc(len + 1, sizeof(bool));
        }
    }

    // Starting cell
    int startBalance = (grid[0][0] == '(') ? 1 : -1;

    if (startBalance < 0) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                free(dp[i][j]);
            free(dp[i]);
        }
        free(dp);
        return false;
    }

    dp[0][0][startBalance] = true;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {

            if (i == 0 && j == 0)
                continue;

            int change = (grid[i][j] == '(') ? 1 : -1;

            for (int balance = 0; balance <= len; balance++) {

                int previousBalance = balance - change;

                if (previousBalance < 0 || previousBalance > len)
                    continue;

                bool possible = false;

                // Come from the cell above
                if (i > 0 && dp[i - 1][j][previousBalance])
                    possible = true;

                // Come from the cell on the left
                if (j > 0 && dp[i][j - 1][previousBalance])
                    possible = true;

                if (possible)
                    dp[i][j][balance] = true;
            }
        }
    }

    bool answer = dp[m - 1][n - 1][0];

    // Free memory
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            free(dp[i][j]);
        free(dp[i]);
    }
    free(dp);

    return answer;
}