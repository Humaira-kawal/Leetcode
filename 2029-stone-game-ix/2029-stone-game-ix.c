bool stoneGameIX(int* stones, int stonesSize) {
    int cnt[3] = {0, 0, 0};

    // Count stones based on remainder when divided by 3
    for (int i = 0; i < stonesSize; i++) {
        cnt[stones[i] % 3]++;
    }

    /*
        Stones with remainder 0 do not change the sum % 3.
        They only change whose turn it is.

        Alice wins if:
        1. cnt[1] > 0 and cnt[2] > 0, with the right balance, OR
        2. There are no remainder-0 stones and one remainder group
           is sufficiently larger than the other.
    */

    if (cnt[0] % 2 == 0) {
        return cnt[1] > 0 && cnt[2] > 0;
    }

    return (cnt[1] > cnt[2] + 2) ||
           (cnt[2] > cnt[1] + 2);
}