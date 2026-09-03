bool uniformArray(int* nums1, int nums1Size) {
    int min = nums1[0];
    bool hasOdd = false;

    for (int i = 0; i < nums1Size; i++) {
        if (nums1[i] < min) {
            min = nums1[i];
        }

        if (nums1[i] % 2 != 0) {
            hasOdd = true;
        }
    }

    // If there are no odd numbers, all are already even.
    if (!hasOdd) {
        return true;
    }

    // If the minimum element is odd,
    // every even element can subtract it to become odd.
    if (min % 2 != 0) {
        return true;
    }

    return false;
}
