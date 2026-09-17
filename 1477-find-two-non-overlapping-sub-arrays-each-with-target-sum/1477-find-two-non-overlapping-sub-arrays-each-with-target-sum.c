#include <limits.h>

int minSumOfLengths(int* arr, int arrSize, int target) {
    int INF = INT_MAX / 2;

    // best[i] = minimum length of a valid subarray
    // completely inside arr[0...i]
    int* best = (int*)malloc(arrSize * sizeof(int));

    for (int i = 0; i < arrSize; i++) {
        best[i] = INF;
    }

    int left = 0;
    long long sum = 0;
    int answer = INF;

    for (int right = 0; right < arrSize; right++) {
        sum += arr[right];

        // Shrink window if sum becomes greater than target
        while (sum > target && left <= right) {
            sum -= arr[left];
            left++;
        }

        // We found a subarray [left ... right]
        if (sum == target) {
            int currentLength = right - left + 1;

            // Check if another valid subarray exists before 'left'
            if (left > 0 && best[left - 1] != INF) {
                int totalLength = currentLength + best[left - 1];

                if (totalLength < answer) {
                    answer = totalLength;
                }
            }

            // Store the shortest valid subarray found so far
            if (right == 0) {
                best[right] = currentLength;
            } else {
                best[right] = best[right - 1] < currentLength
                              ? best[right - 1]
                              : currentLength;
            }
        } else {
            // No subarray ending at right,
            // so carry forward the previous best
            if (right > 0) {
                best[right] = best[right - 1];
            }
        }
    }

    free(best);

    return answer == INF ? -1 : answer;
}