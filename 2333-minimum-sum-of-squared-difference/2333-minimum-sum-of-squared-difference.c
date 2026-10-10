
long long minSumSquareDiff(int* nums1, int nums1Size, int* nums2, int nums2Size, int k1, int k2) {
    int n = nums1Size;
    int maxDiff = 0;
    long long operations = (long long)k1 + k2;

    int *diff = (int *)calloc(100001, sizeof(int));
    if (diff == NULL) return 0;

    for (int i = 0; i < n; i++) {
        int d = abs(nums1[i] - nums2[i]);
        diff[d]++;
        if (d > maxDiff) {
            maxDiff = d;
        }
    }

    if (operations >= 0) {
        long long total = 0;
        for (int d = 1; d <= maxDiff; d++) {
            total += (long long)d * diff[d];
        }

        if (operations >= total) {
            free(diff);
            return 0;
        }
    }

    for (int d = maxDiff; d > 0 && operations > 0; d--) {
        if (diff[d] == 0) continue;

        long long count = diff[d];
        long long use = count < operations ? count : operations;

        diff[d] -= (int)use;
        diff[d - 1] += (int)use;
        operations -= use;
    }

    long long answer = 0;

    for (int d = 1; d <= maxDiff; d++) {
        answer += (long long)d * d * diff[d];
    }

    free(diff);
    return answer;
}
