#include <stdlib.h>

typedef long long ll;

typedef struct {
    int l, r;
    ll w;
    int idx;
} Interval;

typedef struct {
    ll score;
    int len;
    int ids[4];
} State;


/* Sort intervals by left endpoint */
int cmpInterval(const void *a, const void *b) {
    const Interval *x = (const Interval *)a;
    const Interval *y = (const Interval *)b;

    if (x->l != y->l)
        return (x->l > y->l) - (x->l < y->l);

    if (x->r != y->r)
        return (x->r > y->r) - (x->r < y->r);

    return x->idx - y->idx;
}


/* First interval whose left endpoint > r */
int findNext(Interval *a, int n, int r) {
    int lo = 0, hi = n;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        if (a[mid].l > r)
            hi = mid;
        else
            lo = mid + 1;
    }

    return lo;
}


/*
 * Compare two index arrays lexicographically.
 *
 * Return:
 *   -1 if A < B
 *    0 if A == B
 *    1 if A > B
 */
int lexCompare(State *a, State *b) {
    int n = a->len < b->len ? a->len : b->len;

    for (int i = 0; i < n; i++) {
        if (a->ids[i] < b->ids[i])
            return -1;

        if (a->ids[i] > b->ids[i])
            return 1;
    }

    if (a->len < b->len)
        return -1;

    if (a->len > b->len)
        return 1;

    return 0;
}


/*
 * Insert an index into an already sorted array.
 */
void insertIndex(int *src, int len, int value, int *dest) {
    int i = 0, j = 0;
    int inserted = 0;

    while (i < len) {

        if (!inserted && value < src[i]) {
            dest[j++] = value;
            inserted = 1;
        }

        dest[j++] = src[i++];
    }

    if (!inserted)
        dest[j] = value;
}


/*
 * Return the better of two states:
 * 1. Higher score
 * 2. If scores are equal, lexicographically smaller indices
 */
State better(State a, State b) {
    if (a.score > b.score)
        return a;

    if (b.score > a.score)
        return b;

    if (lexCompare(&a, &b) <= 0)
        return a;

    return b;
}


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumWeight(int** intervals,
                   int intervalsSize,
                   int* intervalsColSize,
                   int* returnSize) {

    int n = intervalsSize;

    Interval *a = malloc(n * sizeof(Interval));

    for (int i = 0; i < n; i++) {
        a[i].l = intervals[i][0];
        a[i].r = intervals[i][1];
        a[i].w = intervals[i][2];
        a[i].idx = i;
    }

    /*
     * Sort by left endpoint.
     */
    qsort(a, n, sizeof(Interval), cmpInterval);

    /*
     * next[i] = first interval whose
     * left endpoint is strictly greater than a[i].r
     */
    int *next = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        next[i] = findNext(a, n, a[i].r);
    }

    /*
     * dp[i][k]:
     * Best result using intervals from i onward,
     * choosing at most k intervals.
     */
    State (*dp)[5] = malloc((n + 1) * sizeof(*dp));

    /*
     * Base case:
     * With zero intervals available, score = 0.
     */
    for (int k = 0; k <= 4; k++) {
        dp[n][k].score = 0;
        dp[n][k].len = 0;
    }

    /*
     * With 0 choices allowed, answer is empty.
     */
    for (int i = 0; i <= n; i++) {
        dp[i][0].score = 0;
        dp[i][0].len = 0;
    }


    /*
     * DP from right to left.
     */
    for (int i = n - 1; i >= 0; i--) {

        for (int k = 1; k <= 4; k++) {

            /*
             * Option 1: Skip interval i.
             */
            State skip = dp[i + 1][k];

            /*
             * Option 2: Take interval i.
             */
            State take;

            take.score = a[i].w + dp[next[i]][k - 1].score;
            take.len = dp[next[i]][k - 1].len + 1;

            /*
             * Add original index a[i].idx.
             * We need the resulting array sorted by original index
             * because the answer must be lexicographically smallest.
             */
            insertIndex(
                dp[next[i]][k - 1].ids,
                dp[next[i]][k - 1].len,
                a[i].idx,
                take.ids
            );

            /*
             * Pick:
             * - larger score
             * - lexicographically smaller indices on tie
             */
            dp[i][k] = better(skip, take);
        }
    }


    /*
     * dp[0][4] is the answer.
     */
    State ans = dp[0][4];

    int *result = malloc(ans.len * sizeof(int));

    for (int i = 0; i < ans.len; i++)
        result[i] = ans.ids[i];

    *returnSize = ans.len;

    free(a);
    free(next);
    free(dp);

    return result;
}