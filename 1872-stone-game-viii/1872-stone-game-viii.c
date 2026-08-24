int stoneGameVIII(int* stones, int stonesSize) {
    // Convert stones[] into prefix sums
    for (int i = 1; i < stonesSize; i++) {
        stones[i] += stones[i - 1];
    }

    // If Alice takes all stones
    int dp = stones[stonesSize - 1];

    // Try all possible prefix choices
    for (int i = stonesSize - 2; i > 0; i--) {
        int take = stones[i] - dp;
        
        if (take > dp) {
            dp = take;
        }
    }

    return dp;
}