#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* lexPalindromicPermutation(char* s, char* target) {
    int n = strlen(s);
    int cnt[26] = {0};

    // Count characters in s
    for (int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;

    // A palindrome can have at most one character with odd frequency
    int odd = 0, mid = -1;
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2) {
            odd++;
            mid = i;
        }
    }

    if (odd > 1)
        return "";

    int halfLen = n / 2;

    // Build counts for the first half
    int halfCnt[26];
    for (int i = 0; i < 26; i++)
        halfCnt[i] = cnt[i] / 2;

    /*
        Construct palindrome from a given half.
    */
    char* makePalindrome(char* half) {
        char* ans = (char*)malloc((n + 1) * sizeof(char));

        for (int i = 0; i < halfLen; i++)
            ans[i] = half[i];

        if (n % 2)
            ans[halfLen] = 'a' + mid;

        for (int i = 0; i < halfLen; i++)
            ans[n - 1 - i] = half[i];

        ans[n] = '\0';
        return ans;
    }

    /*
        Check whether the target's first half can be formed
        using halfCnt.
    */
    int possible = 1;
    int remaining[26];

    for (int i = 0; i < 26; i++)
        remaining[i] = halfCnt[i];

    for (int i = 0; i < halfLen; i++) {
        int c = target[i] - 'a';

        if (remaining[c] == 0) {
            possible = 0;
            break;
        }

        remaining[c]--;
    }

    /*
        Case 1:
        Target's first half can be formed.

        Construct the palindrome using exactly that half.
        If it is already > target, it is the answer.
    */
    if (possible) {
        char* half = (char*)malloc((halfLen + 1) * sizeof(char));

        for (int i = 0; i < halfLen; i++)
            half[i] = target[i];

        half[halfLen] = '\0';

        char* candidate = makePalindrome(half);

        if (strcmp(candidate, target) > 0) {
            free(half);
            return candidate;
        }

        free(candidate);
        free(half);
    }

    /*
        Otherwise, find the smallest half permutation
        that is lexicographically greater than target's half.

        We try to change position i, keeping target[0..i-1]
        equal, and make target[i] slightly larger.

        We try i from right to left, exactly like "next permutation".
    */

    for (int i = halfLen - 1; i >= 0; i--) {

        // Check whether target[0 ... i-1] can be used
        int rem[26];

        for (int j = 0; j < 26; j++)
            rem[j] = halfCnt[j];

        int validPrefix = 1;

        for (int j = 0; j < i; j++) {
            int c = target[j] - 'a';

            if (rem[c] == 0) {
                validPrefix = 0;
                break;
            }

            rem[c]--;
        }

        if (!validPrefix)
            continue;

        // Find the smallest character greater than target[i]
        int targetChar = target[i] - 'a';
        int bigger = -1;

        for (int c = targetChar + 1; c < 26; c++) {
            if (rem[c] > 0) {
                bigger = c;
                break;
            }
        }

        if (bigger == -1)
            continue;

        /*
            We found the first position where we can increase.

            Build:
                target[0 ... i-1]
                bigger
                smallest remaining characters
        */
        char* half = (char*)malloc((halfLen + 1) * sizeof(char));

        for (int j = 0; j < i; j++)
            half[j] = target[j];

        half[i] = 'a' + bigger;
        rem[bigger]--;

        // Fill the remaining positions with smallest characters
        int pos = i + 1;

        for (int c = 0; c < 26; c++) {
            while (rem[c] > 0) {
                half[pos++] = 'a' + c;
                rem[c]--;
            }
        }

        half[halfLen] = '\0';

        char* answer = makePalindrome(half);

        free(half);
        return answer;
    }

    // No palindromic permutation is greater than target
    return "";
}