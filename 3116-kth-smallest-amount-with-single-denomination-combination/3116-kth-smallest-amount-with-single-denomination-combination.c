long long gcd(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b;
}

long long countAmounts(int *coins, int n, long long x) {
    long long count = 0;
    int total = 1 << n;

    for (int mask = 1; mask < total; mask++) {
        long long currentLCM = 1;
        int bits = 0;
        int valid = 1;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                bits++;

                currentLCM = lcm(currentLCM, coins[i]);

                if (currentLCM > x) {
                    valid = 0;
                    break;
                }
            }
        }

        if (!valid)
            continue;

        long long multiples = x / currentLCM;

        // Inclusion-exclusion
        if (bits % 2 == 1)
            count += multiples;
        else
            count -= multiples;
    }

    return count;
}

long long findKthSmallest(int* coins, int coinsSize, int k) {
    long long low = 1;

    // The kth amount cannot be greater than k * minimum coin.
    int minCoin = coins[0];

    for (int i = 1; i < coinsSize; i++) {
        if (coins[i] < minCoin)
            minCoin = coins[i];
    }

    long long high = (long long)minCoin * k;

    while (low < high) {
        long long mid = low + (high - low) / 2;

        if (countAmounts(coins, coinsSize, mid) >= k)
            high = mid;
        else
            low = mid + 1;
    }

    return low;
}