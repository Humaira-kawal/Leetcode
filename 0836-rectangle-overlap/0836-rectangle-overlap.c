bool isRectangleOverlap(int* rec1, int rec1Size, int* rec2, int rec2Size) {
    // Check if there is a positive overlap in both X and Y directions

    if (rec1[0] >= rec2[2] || rec2[0] >= rec1[2])
        return false;

    if (rec1[1] >= rec2[3] || rec2[1] >= rec1[3])
        return false;

    return true;
}