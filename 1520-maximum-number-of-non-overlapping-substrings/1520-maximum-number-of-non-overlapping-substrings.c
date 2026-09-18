#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** maxNumOfSubstrings(char* s, int* returnSize) {
    int n = strlen(s);

    // first[c] = first occurrence of character c
    // last[c]  = last occurrence of character c
    int first[26], last[26];

    for (int i = 0; i < 26; i++) {
        first[i] = n;
        last[i] = -1;
    }

    // Find first and last occurrence of every character
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';

        if (first[c] == n)
            first[c] = i;

        last[c] = i;
    }

    /*
     * intervals will contain all valid minimal substrings.
     * Each interval is [left, right].
     */
    int intervals[26][2];
    int count = 0;

    // Try starting from the first occurrence of every character
    for (int c = 0; c < 26; c++) {
        if (first[c] == n)
            continue;

        int left = first[c];
        int right = last[c];
        int valid = 1;

        /*
         * Expand the interval.
         * If we encounter a character whose first occurrence
         * is before 'left', then this substring cannot be valid.
         *
         * Otherwise, include all occurrences of that character
         * by extending 'right'.
         */
        for (int i = left; i <= right; i++) {
            int x = s[i] - 'a';

            if (first[x] < left) {
                valid = 0;
                break;
            }

            if (last[x] > right)
                right = last[x];
        }

        if (valid) {
            intervals[count][0] = left;
            intervals[count][1] = right;
            count++;
        }
    }

    /*
     * Sort intervals by their ending position.
     * Since there are only 26 possible intervals,
     * simple sorting is enough.
     */
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (intervals[i][1] > intervals[j][1]) {
                int tempLeft = intervals[i][0];
                int tempRight = intervals[i][1];

                intervals[i][0] = intervals[j][0];
                intervals[i][1] = intervals[j][1];

                intervals[j][0] = tempLeft;
                intervals[j][1] = tempRight;
            }
        }
    }

    /*
     * Greedily select non-overlapping intervals.
     *
     * Choosing the interval that finishes earliest
     * leaves maximum space for future substrings.
     */
    char** answer = (char**)malloc(26 * sizeof(char*));
    int ansCount = 0;
    int previousEnd = -1;

    for (int i = 0; i < count; i++) {
        int left = intervals[i][0];
        int right = intervals[i][1];

        if (left > previousEnd) {
            int len = right - left + 1;

            answer[ansCount] = (char*)malloc((len + 1) * sizeof(char));

            strncpy(answer[ansCount], s + left, len);
            answer[ansCount][len] = '\0';

            ansCount++;
            previousEnd = right;
        }
    }

    *returnSize = ansCount;
    return answer;
}