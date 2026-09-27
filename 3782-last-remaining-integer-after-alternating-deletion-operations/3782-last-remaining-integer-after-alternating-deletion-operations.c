long long solve(long long n, int left) {
    if (n == 1)
        return 1;

    long long remaining = (n + 1) / 2;

    long long ans = solve(remaining, !left);

    if (left) {
        // Delete every second number from the left.
        // Survivors are: 1, 3, 5, 7, ...
        return 2 * ans - 1;
    } else {
        // Delete every second number from the right.
        if (n % 2 == 0) {
            // Survivors are: 2, 4, 6, 8, ...
            return 2 * ans;
        } else {
            // Survivors are: 1, 3, 5, 7, ...
            return 2 * ans - 1;
        }
    }
}

long long lastInteger(long long n) {
    return solve(n, 1);
}