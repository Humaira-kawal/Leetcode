int minimumDeletions(int* nums, int numsSize) {
    int minIndex = 0;
    int maxIndex = 0;

    // Find indices of minimum and maximum
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < nums[minIndex]) {
            minIndex = i;
        }

        if (nums[i] > nums[maxIndex]) {
            maxIndex = i;
        }
    }

    // Arrange indices so left < right
    int left = minIndex < maxIndex ? minIndex : maxIndex;
    int right = minIndex > maxIndex ? minIndex : maxIndex;

    // 1. Remove both from front
    int fromFront = right + 1;

    // 2. Remove both from back
    int fromBack = numsSize - left;

    // 3. Remove left from front and right from back
    int bothEnds = (left + 1) + (numsSize - right);

    // Return minimum
    int ans = fromFront;

    if (fromBack < ans) {
        ans = fromBack;
    }

    if (bothEnds < ans) {
        ans = bothEnds;
    }

    return ans;
}