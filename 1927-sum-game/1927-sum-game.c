#include <stdlib.h>

bool sumGame(char* num) {
    int n = 0;

    while (num[n] != '\0')
        n++;

    int half = n / 2;

    int sum1 = 0, sum2 = 0;
    int q1 = 0, q2 = 0;

    for (int i = 0; i < half; i++) {
        if (num[i] == '?')
            q1++;
        else
            sum1 += num[i] - '0';
    }

    for (int i = half; i < n; i++) {
        if (num[i] == '?')
            q2++;
        else
            sum2 += num[i] - '0';
    }

    int qDiff = q1 - q2;
    int sumDiff = sum1 - sum2;

    // If the number of '?' is odd, Alice always wins.
    if ((q1 + q2) % 2 == 1)
        return true;

    // Bob can win only when the current difference can
    // be exactly compensated by the remaining '?'.
    if (sumDiff * 2 == -9 * qDiff)
        return false;

    return true;
}