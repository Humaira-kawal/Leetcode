
#include <stdlib.h>
#include <string.h>

char* maxSumOfSquares(int num, int sum) {
    if (sum > 9 * num) {
        char *ans = malloc(1);
        ans[0] = '\0';
        return ans;
    }

    char *ans = malloc((num + 1) * sizeof(char));
    if (ans == NULL) return NULL;

    for (int i = 0; i < num; i++) {
        int digit = (sum >= 9) ? 9 : sum;
        ans[i] = '0' + digit;
        sum -= digit;
    }

    ans[num] = '\0';
    return ans;
}
