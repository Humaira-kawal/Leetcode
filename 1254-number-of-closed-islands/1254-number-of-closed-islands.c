
int dfs(int** grid, int gridSize, int* gridColSize, int r, int c) {
    if (r < 0 || r >= gridSize || c < 0 || c >= gridColSize[0])
        return 0;

    if (grid[r][c] == 1)
        return 1;

    grid[r][c] = 1;

    int up = dfs(grid, gridSize, gridColSize, r - 1, c);
    int down = dfs(grid, gridSize, gridColSize, r + 1, c);
    int left = dfs(grid, gridSize, gridColSize, r, c - 1);
    int right = dfs(grid, gridSize, gridColSize, r, c + 1);

    return up & down & left & right;
}

int closedIsland(int** grid, int gridSize, int* gridColSize) {
    int count = 0;

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 0) {
                if (dfs(grid, gridSize, gridColSize, i, j))
                    count++;
            }
        }
    }

    return count;
}
