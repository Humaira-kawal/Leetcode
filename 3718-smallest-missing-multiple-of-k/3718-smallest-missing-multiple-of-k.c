int missingMultiple(int* nums, int numsSize, int k) {
    int multiple = k;

    while (1) {
        int found = 0;

        for (int i = 0; i < numsSize; i++) {
            if (nums[i] == multiple) {
                found = 1;
                break;
            }
        }

        if (!found)
            return multiple;

        multiple += k;
    }
}