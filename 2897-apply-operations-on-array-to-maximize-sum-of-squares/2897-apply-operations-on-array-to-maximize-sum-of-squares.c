
int maxSum(int* nums, int numsSize, int k) {
    long long MOD = 1000000007LL;
    long long bitCount[32] = {0};

    // Count how many numbers contain each bit
    for (int i = 0; i < numsSize; i++) {
        for (int b = 0; b < 31; b++) {
            if (nums[i] & (1 << b)) {
                bitCount[b]++;
            }
        }
    }

    long long ans = 0;

    // Construct the largest possible numbers greedily
    for (int i = 0; i < k; i++) {
        long long num = 0;

        for (int b = 30; b >= 0; b--) {
            if (bitCount[b] > 0) {
                num |= (1LL << b);
                bitCount[b]--;
            }
        }

        ans = (ans + num * num) % MOD;
    }

    return (int)ans;
}
