#include <stdlib.h>

typedef struct {
    int value;
    int index;
} Pair;

int cmpPair(const void* a, const void* b) {
    Pair* p1 = (Pair*)a;
    Pair* p2 = (Pair*)b;

    if (p1->value < p2->value)
        return -1;
    if (p1->value > p2->value)
        return 1;

    return 0;
}

int cmpInt(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int* lexicographicallySmallestArray(
    int* nums,
    int numsSize,
    int limit,
    int* returnSize
) {
    *returnSize = numsSize;

    // Store value + original index
    Pair* arr = (Pair*)malloc(numsSize * sizeof(Pair));

    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].index = i;
    }

    // Sort according to values
    qsort(arr, numsSize, sizeof(Pair), cmpPair);

    int start = 0;

    while (start < numsSize) {

        int end = start;

        // Find the complete connected group
        while (end + 1 < numsSize &&
               (long long)arr[end + 1].value - arr[end].value <= limit) {
            end++;
        }

        int size = end - start + 1;

        // Extract original indices of this group
        int* indices = (int*)malloc(size * sizeof(int));

        for (int i = 0; i < size; i++) {
            indices[i] = arr[start + i].index;
        }

        // Smallest index gets smallest value
        qsort(indices, size, sizeof(int), cmpInt);

        // Values are already sorted because arr is sorted
        for (int i = 0; i < size; i++) {
            nums[indices[i]] = arr[start + i].value;
        }

        free(indices);

        start = end + 1;
    }

    free(arr);

    return nums;
}