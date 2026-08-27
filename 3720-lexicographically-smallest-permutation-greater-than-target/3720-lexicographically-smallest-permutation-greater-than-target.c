#include <stdlib.h>
#include <string.h>

char* lexGreaterPermutation(char* s, char* target) {
    int n = strlen(s);

    int cnt[26] = {0};

    for (int i = 0; i < n; i++)
        cnt[s[i] - 'a']++;

    char *ans = (char *)malloc((n + 1) * sizeof(char));
    ans[n] = '\0';

    /*
        We try to keep ans equal to target.
        If that becomes impossible, we backtrack.
    */

    for (int i = 0; i < n; i++) {

        // First try to put target[i] itself.
        if (cnt[target[i] - 'a'] > 0) {
            ans[i] = target[i];
            cnt[target[i] - 'a']--;
            continue;
        }

        /*
            target[i] is unavailable.
            We need the smallest character > target[i]
            at this position.
        */
        int found = -1;

        for (int c = target[i] - 'a' + 1; c < 26; c++) {
            if (cnt[c] > 0) {
                found = c;
                break;
            }
        }

        if (found != -1) {
            ans[i] = 'a' + found;

            // Put all remaining characters in sorted order.
            cnt[found]--;

            int pos = i + 1;
            for (int c = 0; c < 26; c++) {
                while (cnt[c] > 0) {
                    ans[pos++] = 'a' + c;
                    cnt[c]--;
                }
            }

            return ans;
        }

        /*
            No character greater than target[i].
            We must backtrack.
        */
        for (int j = i - 1; j >= 0; j--) {

            // Return target[j] to the available characters.
            cnt[ans[j] - 'a']++;

            /*
                Try to replace ans[j] with the smallest
                available character greater than target[j].
            */
            for (int c = target[j] - 'a' + 1; c < 26; c++) {
                if (cnt[c] > 0) {

                    ans[j] = 'a' + c;
                    cnt[c]--;

                    // Fill the rest with smallest characters.
                    int pos = j + 1;

                    for (int k = 0; k < 26; k++) {
                        while (cnt[k] > 0) {
                            ans[pos++] = 'a' + k;
                            cnt[k]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }

    /*
        We matched target completely.
        Therefore, target itself is a permutation of s,
        but we need something STRICTLY greater.

        Find the next lexicographical permutation.
    */

    for (int i = n - 2; i >= 0; i--) {
        if (ans[i] < ans[i + 1]) {

            int j = n - 1;

            while (ans[j] <= ans[i])
                j--;

            char temp = ans[i];
            ans[i] = ans[j];
            ans[j] = temp;

            // Reverse suffix.
            int l = i + 1, r = n - 1;

            while (l < r) {
                temp = ans[l];
                ans[l] = ans[r];
                ans[r] = temp;
                l++;
                r--;
            }

            return ans;
        }
    }

    // No permutation is greater than target.
    free(ans);
    return "";
}