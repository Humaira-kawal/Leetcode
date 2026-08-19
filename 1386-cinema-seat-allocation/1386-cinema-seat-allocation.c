#include <stdlib.h>

int compare(const void *a, const void *b) {
    int **x = (int **)a;
    int **y = (int **)b;

    if (x[0][0] != y[0][0])
        return x[0][0] - y[0][0];

    return x[0][1] - y[0][1];
}

int maxNumberOfFamilies(int n, int** reservedSeats,
                        int reservedSeatsSize,
                        int* reservedSeatsColSize) {

    // Sort reservations by row
    qsort(reservedSeats, reservedSeatsSize,
          sizeof(int *), compare);

    // Seat groups
    int left = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
    int middle = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
    int right = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

    int answer = 0;
    int reservedRows = 0;

    int i = 0;

    while (i < reservedSeatsSize) {

        // Current row
        int row = reservedSeats[i][0];

        // This row has at least one reservation
        reservedRows++;

        // Bitmask of reserved seats
        int mask = 0;

        // Process all seats in this row
        while (i < reservedSeatsSize &&
               reservedSeats[i][0] == row) {

            int seat = reservedSeats[i][1];

            if (seat >= 2 && seat <= 9) {
                mask |= (1 << seat);
            }

            i++;
        }

        // Can place both left and right groups
        if ((mask & left) == 0 &&
            (mask & right) == 0) {

            answer += 2;
        }

        // Otherwise, can place at least one group
        else if ((mask & left) == 0 ||
                 (mask & middle) == 0 ||
                 (mask & right) == 0) {

            answer += 1;
        }
    }

    // Rows with NO reservations can always fit 2 families
    int emptyRows = n - reservedRows;

    answer += emptyRows * 2;

    return answer;
}