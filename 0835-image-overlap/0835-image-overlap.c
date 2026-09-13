int largestOverlap(int** img1, int img1Size, int* img1ColSize,
                   int** img2, int img2Size, int* img2ColSize) {

    int n = img1Size;

    // Maximum possible number of 1s is n*n
    int count1[n * n][2];
    int count2[n * n][2];

    int size1 = 0, size2 = 0;

    // Store coordinates of 1s in img1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (img1[i][j] == 1) {
                count1[size1][0] = i;
                count1[size1][1] = j;
                size1++;
            }
        }
    }

    // Store coordinates of 1s in img2
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (img2[i][j] == 1) {
                count2[size2][0] = i;
                count2[size2][1] = j;
                size2++;
            }
        }
    }

    // Possible translation range:
    // -(n-1) to +(n-1)
    int offset = n - 1;
    int freq[2 * n - 1][2 * n - 1];

    // Initialize frequency array
    for (int i = 0; i < 2 * n - 1; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            freq[i][j] = 0;
        }
    }

    int ans = 0;

    // Compare every 1 in img1 with every 1 in img2
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {

            int dr = count2[j][0] - count1[i][0];
            int dc = count2[j][1] - count1[i][1];

            // Shift to positive index
            int r = dr + offset;
            int c = dc + offset;

            freq[r][c]++;

            if (freq[r][c] > ans) {
                ans = freq[r][c];
            }
        }
    }

    return ans;
}