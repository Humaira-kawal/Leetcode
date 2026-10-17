
#include <stdlib.h>

typedef struct {
    int value;
    int digitSum;
    int originalIndex;
} Element;

int getDigitSum(int n) {
    int sum = 0;

    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }

    return sum;
}

int compare(const void *a, const void *b) {
    const Element *x = (const Element *)a;
    const Element *y = (const Element *)b;

    if (x->digitSum != y->digitSum)
        return x->digitSum - y->digitSum;

    return x->value - y->value;
}

int minSwaps(int* nums, int numsSize) {
    Element *arr = malloc(numsSize * sizeof(Element));
    int *visited = calloc(numsSize, sizeof(int));

    for (int i = 0; i < numsSize; i++) {
        arr[i].value = nums[i];
        arr[i].digitSum = getDigitSum(nums[i]);
        arr[i].originalIndex = i;
    }

    qsort(arr, numsSize, sizeof(Element), compare);

    int swaps = 0;

    for (int i = 0; i < numsSize; i++) {
        if (visited[i] || arr[i].originalIndex == i)
            continue;

        int cycleSize = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = 1;
            j = arr[j].originalIndex;
            cycleSize++;
        }

        if (cycleSize > 1)
            swaps += cycleSize - 1;
    }

    free(arr);
    free(visited);

    return swaps;
}

