#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minMoves(char** classroom, int classroomSize, int energy) {
    int m = classroomSize;
    int n = strlen(classroom[0]);

    // Find start position and count litter
    int sr = 0, sc = 0;
    int litterCount = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (classroom[i][j] == 'S') {
                sr = i;
                sc = j;
            }
            if (classroom[i][j] == 'L') {
                litterCount++;
            }
        }
    }

    // No litter
    if (litterCount == 0)
        return 0;

    int totalMasks = 1 << litterCount;

    // Give every litter cell a bit number
    int **litterId = malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        litterId[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            litterId[i][j] = -1;
        }
    }

    int id = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (classroom[i][j] == 'L') {
                litterId[i][j] = id++;
            }
        }
    }

    /*
        visited[r][c][energy][mask]

        We need to remember whether this exact state
        has already been visited.
    */

    int totalStates = m * n * (energy + 1) * totalMasks;

    char *visited = calloc(totalStates, sizeof(char));

    /*
        Queue stores:
        r, c, remaining energy, mask
    */

    typedef struct {
        int r;
        int c;
        int e;
        int mask;
        int dist;
    } State;

    State *queue = malloc(totalStates * sizeof(State));

    int front = 0;
    int back = 0;

    // Initial state
    int startIndex =
        (((sr * n + sc) * (energy + 1) + energy) * totalMasks);

    visited[startIndex] = 1;

    queue[back++] = (State){sr, sc, energy, 0, 0};

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    int finalMask = totalMasks - 1;

    while (front < back) {

        State cur = queue[front++];

        // All litter collected
        if (cur.mask == finalMask) {
            free(queue);
            free(visited);

            for (int i = 0; i < m; i++)
                free(litterId[i]);
            free(litterId);

            return cur.dist;
        }

        // If no energy remains, we cannot move
        // unless we are on R (which would already
        // have reset our energy).
        if (cur.e == 0)
            continue;

        for (int d = 0; d < 4; d++) {

            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];

            // Outside grid
            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;

            // Obstacle
            if (classroom[nr][nc] == 'X')
                continue;

            // Spend one energy for the move
            int ne = cur.e - 1;

            // Collect litter if present
            int nmask = cur.mask;

            if (classroom[nr][nc] == 'L') {
                int bit = litterId[nr][nc];
                nmask |= (1 << bit);
            }

            // Reset energy on R
            if (classroom[nr][nc] == 'R') {
                ne = energy;
            }

            int index =
                (((nr * n + nc) * (energy + 1) + ne)
                 * totalMasks + nmask);

            if (!visited[index]) {

                visited[index] = 1;

                queue[back++] =
                    (State){nr, nc, ne, nmask, cur.dist + 1};
            }
        }
    }

    free(queue);
    free(visited);

    for (int i = 0; i < m; i++)
        free(litterId[i]);
    free(litterId);

    return -1;
}