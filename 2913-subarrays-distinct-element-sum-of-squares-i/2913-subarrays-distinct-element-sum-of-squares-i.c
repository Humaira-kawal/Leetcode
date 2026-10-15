int sumCounts(int* nums, int numsSize) {
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        int freq[101] = {0};
        int distinct = 0;

        for (int j = i; j < numsSize; j++) {
            if (freq[nums[j]] == 0) {
                distinct++;
            }

            freq[nums[j]]++;

            ans += distinct * distinct;
        }
    }

    return ans;
}