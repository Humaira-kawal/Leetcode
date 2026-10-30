
#include <stdlib.h>
#include <limits.h>

#define INF LLONG_MAX

typedef struct {
    int to, weight, next;
} Edge;

typedef struct {
    long long dist;
    int node, count;
} State;

typedef struct {
    State *a;
    int size, capacity;
} Heap;

void push(Heap *h, State s) {
    if (h->size == h->capacity) {
        h->capacity = h->capacity ? h->capacity * 2 : 1024;
        h->a = realloc(h->a, (size_t)h->capacity * sizeof(State));
    }

    int i = h->size++;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->a[p].dist <= s.dist)
            break;

        h->a[i] = h->a[p];
        i = p;
    }

    h->a[i] = s;
}

State pop(Heap *h) {
    State result = h->a[0];
    State last = h->a[--h->size];

    int i = 0;

    while (2 * i + 1 < h->size) {
        int child = 2 * i + 1;

        if (child + 1 < h->size &&
            h->a[child + 1].dist < h->a[child].dist)
            child++;

        if (last.dist <= h->a[child].dist)
            break;

        h->a[i] = h->a[child];
        i = child;
    }

    if (h->size > 0)
        h->a[i] = last;

    return result;
}

int shortestPath(int n, int** edges, int edgesSize,
                 int* edgesColSize, char* labels, int k) {

    int *head = malloc((size_t)n * sizeof(int));
    Edge *adj = malloc((size_t)(edgesSize > 0 ? edgesSize : 1) * sizeof(Edge));

    for (int i = 0; i < n; i++)
        head[i] = -1;

    int ec = 0;

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        adj[ec] = (Edge){v, w, head[u]};
        head[u] = ec++;
    }

    long long *dist = malloc((size_t)n * (k + 1) * sizeof(long long));

    for (long long i = 0; i < (long long)n * (k + 1); i++)
        dist[i] = INF;

    #define ID(u,c) ((long long)(u) * (k + 1) + (c))

    Heap heap = {NULL, 0, 0};

    dist[ID(0, 1)] = 0;
    push(&heap, (State){0, 0, 1});

    int answer = -1;

    while (heap.size > 0) {
        State cur = pop(&heap);

        int u = cur.node;
        int cnt = cur.count;
        long long d = cur.dist;

        if (d != dist[ID(u, cnt)])
            continue;

        if (u == n - 1) {
            answer = (int)d;
            break;
        }

        for (int e = head[u]; e != -1; e = adj[e].next) {
            int v = adj[e].to;
            int w = adj[e].weight;

            int nc = (labels[u] == labels[v]) ? cnt + 1 : 1;

            if (nc > k)
                continue;

            long long nd = d + w;
            long long idx = ID(v, nc);

            if (nd < dist[idx]) {
                dist[idx] = nd;
                push(&heap, (State){nd, v, nc});
            }
        }
    }

    free(head);
    free(adj);
    free(dist);
    free(heap.a);

    return answer;
}
