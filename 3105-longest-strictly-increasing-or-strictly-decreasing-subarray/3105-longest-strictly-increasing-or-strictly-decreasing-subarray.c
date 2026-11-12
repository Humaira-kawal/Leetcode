int longestMonotonicSubarray(int* nums, int numsSize) {
    int inc = 1, dec = 1, ans = 1;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1]) {
            inc++;
            dec = 1;
        }
        else if (nums[i] < nums[i - 1]) {
            dec++;
            inc = 1;
        }
        else {
            inc = 1;
            dec = 1;
        }

        if (inc > ans)
            ans = inc;

        if (dec > ans)
            ans = dec;
    }

    return ans;
}