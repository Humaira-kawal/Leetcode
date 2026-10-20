#include <stdlib.h>

static void update(int *freq, int value, int delta, int *nonzero) {
    int old = freq[value];
    int now = old + delta;

    if (old == 0 && now != 0)
        (*nonzero)++;
    else if (old != 0 && now == 0)
        (*nonzero)--;

    freq[value] = now;
}

static int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int sortableIntegers(int* nums, int numsSize) {
    int n = numsSize;
    int *sorted = malloc(n * sizeof(int));
    int *freq = calloc(100001, sizeof(int));

    for (int i = 0; i < n; i++)
        sorted[i] = nums[i];

    qsort(sorted, n, sizeof(int), cmp);

    int ans = 0;

    for (int k = 1; k <= n; k++) {
        if (n % k != 0)
            continue;

        int valid = 1;

        for (int start = 0; start < n && valid; start += k) {
            int nonzero = 0;

            for (int j = start; j < start + k; j++) {
                update(freq, nums[j], 1, &nonzero);
                update(freq, sorted[j], -1, &nonzero);
            }

            if (nonzero != 0) {
                valid = 0;
            }

            int descents = 0;

            for (int j = start; j < start + k; j++) {
                int next = (j + 1 == start + k) ? start : j + 1;

                if (nums[j] > nums[next])
                    descents++;
            }

            if (descents > 1)
                valid = 0;

            for (int j = start; j < start + k; j++) {
                update(freq, nums[j], -1, &nonzero);
                update(freq, sorted[j], 1, &nonzero);
            }
        }

        if (valid)
            ans += k;
    }

    free(sorted);
    free(freq);

    return ans;
}