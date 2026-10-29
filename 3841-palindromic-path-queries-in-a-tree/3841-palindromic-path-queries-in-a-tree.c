#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define LOG 17

static int *head, *to, *nextEdge;
static int edgePtr;

static int *tin, *tout, *depth;
static int **up;
static int timer;
static int *bit;
static int N;

static void addEdge(int u, int v) {
    to[edgePtr] = v;
    nextEdge[edgePtr] = head[u];
    head[u] = edgePtr++;
}

static void dfs(int u, int p) {
    tin[u] = ++timer;
    up[0][u] = p;

    for (int k = 1; k < LOG; k++)
        up[k][u] = up[k - 1][up[k - 1][u]];

    for (int e = head[u]; e != -1; e = nextEdge[e]) {
        int v = to[e];
        if (v == p) continue;

        depth[v] = depth[u] + 1;
        dfs(v, u);
    }

    tout[u] = timer;
}

static void bitAdd(int i, int val) {
    for (; i <= N; i += i & -i)
        bit[i] ^= val;
}

static int bitQuery(int i) {
    int res = 0;
    for (; i > 0; i -= i & -i)
        res ^= bit[i];
    return res;
}

static int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int t = u;
        u = v;
        v = t;
    }

    int diff = depth[u] - depth[v];

    for (int k = 0; k < LOG; k++)
        if (diff & (1 << k))
            u = up[k][u];

    if (u == v) return u;

    for (int k = LOG - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }

    return up[0][u];
}

bool* palindromePath(int n, int** edges, int edgesSize,
                     int* edgesColSize, char* s,
                     char** queries, int queriesSize,
                     int* returnSize) {

    N = n;
    *returnSize = 0;

    bool *answer = malloc(sizeof(bool) * queriesSize);
    if (!answer) return NULL;

    head = malloc(sizeof(int) * n);
    to = malloc(sizeof(int) * (2 * edgesSize));
    nextEdge = malloc(sizeof(int) * (2 * edgesSize));
    tin = malloc(sizeof(int) * n);
    tout = malloc(sizeof(int) * n);
    depth = calloc(n, sizeof(int));
    bit = calloc(n + 1, sizeof(int));

    up = malloc(sizeof(int*) * LOG);
    for (int k = 0; k < LOG; k++)
        up[k] = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++)
        head[i] = -1;

    edgePtr = 0;
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(u, v);
        addEdge(v, u);
    }

    timer = 0;
    dfs(0, 0);

    int *mask = calloc(n, sizeof(int));

    for (int u = 0; u < n; u++) {
        mask[u] = 1 << (s[u] - 'a');
        bitAdd(tin[u], mask[u]);
        bitAdd(tout[u] + 1, mask[u]);
    }

    for (int i = 0; i < queriesSize; i++) {
        char type[16], c;
        int u, v;

        if (sscanf(queries[i], "%15s", type) != 1)
            continue;

        if (strcmp(type, "update") == 0) {
            sscanf(queries[i], "%*s %d %c", &u, &c);

            int newMask = 1 << (c - 'a');
            int delta = mask[u] ^ newMask;

            bitAdd(tin[u], delta);
            bitAdd(tout[u] + 1, delta);
            mask[u] = newMask;
        } else {
            sscanf(queries[i], "%*s %d %d", &u, &v);

            int w = lca(u, v);

            int pathMask =
                bitQuery(tin[u]) ^
                bitQuery(tin[v]) ^
                mask[w];

            answer[(*returnSize)++] =
                (pathMask & (pathMask - 1)) == 0;
        }
    }

    for (int k = 0; k < LOG; k++)
        free(up[k]);

    free(up);
    free(head);
    free(to);
    free(nextEdge);
    free(tin);
    free(tout);
    free(depth);
    free(bit);
    free(mask);

    return answer;
}