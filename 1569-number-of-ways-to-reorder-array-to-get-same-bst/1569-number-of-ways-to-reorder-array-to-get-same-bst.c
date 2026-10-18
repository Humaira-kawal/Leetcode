#define MOD 1000000007

long long comb[1001][1001];

long long solve(int *arr, int n) {
    if (n <= 2)
        return 1;

    int left[1001], right[1001];
    int l = 0, r = 0;

    int root = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < root)
            left[l++] = arr[i];
        else
            right[r++] = arr[i];
    }

    long long leftWays = solve(left, l);
    long long rightWays = solve(right, r);

    long long ways = comb[n - 1][l];

    ways = (ways * leftWays) % MOD;
    ways = (ways * rightWays) % MOD;

    return ways;
}

int numOfWays(int* nums, int numsSize) {
    for (int i = 0; i <= numsSize; i++) {
        comb[i][0] = comb[i][i] = 1;

        for (int j = 1; j < i; j++) {
            comb[i][j] =
                (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }

    return (solve(nums, numsSize) - 1 + MOD) % MOD;
}