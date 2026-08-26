#include <string.h>
#include <stdlib.h>

char* shortestBeautifulSubstring(char* s, int k) {
    int n = strlen(s);
    int bestLen = n + 1;
    int bestStart = -1;

    for (int i = 0; i < n; i++) {
        int ones = 0;

        for (int j = i; j < n; j++) {

            if (s[j] == '1')
                ones++;

            if (ones == k) {
                int len = j - i + 1;

                if (len < bestLen) {
                    bestLen = len;
                    bestStart = i;
                }
                else if (len == bestLen) {
                    if (strncmp(s + i, s + bestStart, len) < 0)
                        bestStart = i;
                }

                // Adding more characters can only increase length,
                // so stop for this starting position.
                break;
            }
        }
    }

    if (bestStart == -1) {
        char* ans = malloc(1);
        ans[0] = '\0';
        return ans;
    }

    char* ans = malloc(bestLen + 1);

    strncpy(ans, s + bestStart, bestLen);
    ans[bestLen] = '\0';

    return ans;
}