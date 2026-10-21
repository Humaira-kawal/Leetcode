#include <string.h>

int minOperations(char* s) {
    int n = strlen(s);

    if (n <= 1) return 0;

    int sorted = 1;
    for (int i = 1; i < n; i++) {
        if (s[i] < s[i - 1]) {
            sorted = 0;
            break;
        }
    }

    if (sorted) return 0;
    if (n == 2) return -1;

    char mn = s[0], mx = s[0];
    int minCount = 0, maxCount = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] < mn) mn = s[i];
        if (s[i] > mx) mx = s[i];
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == mn) minCount++;
        if (s[i] == mx) maxCount++;
    }

    if (s[0] == mn || s[n - 1] == mx)
        return 1;

    if (s[0] == mx && s[n - 1] == mn &&
        maxCount == 1 && minCount == 1)
        return 3;

    return 2;
}