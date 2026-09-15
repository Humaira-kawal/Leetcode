#include <string.h>
#include <stdlib.h>

int maxPalindromes(char* s, int k) {
    int n = strlen(s);

    // pal[i][j] = 1 if s[i...j] is a palindrome
    char **pal = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        pal[i] = (char *)calloc(n, sizeof(char));
    }

    // Build palindrome table
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i; j < n; j++) {
            if (s[i] == s[j] &&
                (j - i <= 1 || pal[i + 1][j - 1])) {
                pal[i][j] = 1;
            }
        }
    }

    // dp[i] = maximum palindromes using first i characters
    int *dp = (int *)calloc(n + 1, sizeof(int));

    for (int i = 0; i < n; i++) {

        // Option 1: don't start a palindrome at i
        if (dp[i + 1] < dp[i])
            dp[i + 1] = dp[i];

        // Option 2: take a palindrome starting at i
        for (int j = i + k - 1; j < n; j++) {
            if (pal[i][j]) {
                if (dp[j + 1] < dp[i] + 1)
                    dp[j + 1] = dp[i] + 1;
            }
        }
    }

    int answer = dp[n];

    // Free memory
    for (int i = 0; i < n; i++)
        free(pal[i]);
    free(pal);
    free(dp);

    return answer;
}