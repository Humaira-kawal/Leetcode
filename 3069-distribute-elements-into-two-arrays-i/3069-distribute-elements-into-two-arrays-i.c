/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultArray(int* nums, int numsSize, int* returnSize) {
    
    int* arr1 = (int*)malloc(numsSize * sizeof(int));
    int* arr2 = (int*)malloc(numsSize * sizeof(int));
    int* result = (int*)malloc(numsSize * sizeof(int));

    int size1 = 0;
    int size2 = 0;

    // First operation
    arr1[size1++] = nums[0];

    // Second operation
    arr2[size2++] = nums[1];

    // Remaining elements
    for (int i = 2; i < numsSize; i++) {
        if (arr1[size1 - 1] > arr2[size2 - 1]) {
            arr1[size1++] = nums[i];
        } else {
            arr2[size2++] = nums[i];
        }
    }

    // Concatenate arr1 and arr2
    int index = 0;

    for (int i = 0; i < size1; i++) {
        result[index++] = arr1[i];
    }

    for (int i = 0; i < size2; i++) {
        result[index++] = arr2[i];
    }

    *returnSize = numsSize;

    free(arr1);
    free(arr2);

    return result;
}