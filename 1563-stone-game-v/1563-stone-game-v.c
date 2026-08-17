#include <stdlib.h>

int stoneGameV(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;

    if (n <= 1)
        return 0;

    // Prefix sum
    int* prefix = (int*)malloc((n + 1) * sizeof(int));
    prefix[0] = 0;

    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + stoneValue[i];
    }

    // dp[l][r] = maximum score for subarray [l...r]
    int** dp = (int**)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++) {
        dp[i] = (int*)calloc(n, sizeof(int));
    }

    // Length of interval
    for (int len = 2; len <= n; len++) {

        for (int l = 0; l + len <= n; l++) {

            int r = l + len - 1;

            // Try every split
            for (int k = l; k < r; k++) {

                int leftSum = prefix[k + 1] - prefix[l];
                int rightSum = prefix[r + 1] - prefix[k + 1];

                if (leftSum < rightSum) {

                    dp[l][r] =
                        (dp[l][r] > leftSum + dp[l][k])
                        ? dp[l][r]
                        : leftSum + dp[l][k];

                }
                else if (leftSum > rightSum) {

                    dp[l][r] =
                        (dp[l][r] > rightSum + dp[k + 1][r])
                        ? dp[l][r]
                        : rightSum + dp[k + 1][r];

                }
                else {

                    int option1 = leftSum + dp[l][k];
                    int option2 = rightSum + dp[k + 1][r];

                    if (option1 > dp[l][r])
                        dp[l][r] = option1;

                    if (option2 > dp[l][r])
                        dp[l][r] = option2;
                }
            }
        }
    }

    int answer = dp[0][n - 1];

    // Free memory
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }

    free(dp);
    free(prefix);

    return answer;
}