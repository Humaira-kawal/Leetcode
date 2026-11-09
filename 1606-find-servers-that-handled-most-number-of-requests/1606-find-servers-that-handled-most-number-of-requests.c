
#include <stdlib.h>

typedef struct {
    int endTime;
    int server;
} Busy;

void swap(Busy *a, Busy *b) {
    Busy temp = *a;
    *a = *b;
    *b = temp;
}

void push(Busy heap[], int *size, Busy val) {
    int i = (*size)++;
    heap[i] = val;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].endTime <= heap[i].endTime)
            break;
        swap(&heap[p], &heap[i]);
        i = p;
    }
}

Busy pop(Busy heap[], int *size) {
    Busy result = heap[0];
    heap[0] = heap[--(*size)];

    int i = 0;

    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < *size &&
            heap[l].endTime < heap[smallest].endTime)
            smallest = l;

        if (r < *size &&
            heap[r].endTime < heap[smallest].endTime)
            smallest = r;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return result;
}

int find(int tree[], int node, int l, int r, int pos) {
    if (l == r)
        return l;

    int mid = (l + r) / 2;

    if (pos <= mid) {
        if (tree[node * 2] > 0)
            return find(tree, node * 2, l, mid, pos);
        return find(tree, node * 2 + 1, mid + 1, r, pos);
    }

    if (tree[node * 2 + 1] > 0)
        return find(tree, node * 2 + 1, mid + 1, r, pos);

    return find(tree, node * 2, l, mid, pos);
}

void update(int tree[], int node, int l, int r, int idx, int val) {
    if (l == r) {
        tree[node] = val;
        return;
    }

    int mid = (l + r) / 2;

    if (idx <= mid)
        update(tree, node * 2, l, mid, idx, val);
    else
        update(tree, node * 2 + 1, mid + 1, r, idx, val);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int* busiestServers(int k, int* arrival, int arrivalSize,
                    int* load, int loadSize, int* returnSize) {

    Busy *heap = malloc(sizeof(Busy) * arrivalSize);
    int heapSize = 0;

    int *tree = calloc(4 * k, sizeof(int));
    int *count = calloc(k, sizeof(int));

    for (int i = 0; i < k; i++)
        update(tree, 1, 0, k - 1, i, 1);

    for (int i = 0; i < arrivalSize; i++) {

        while (heapSize > 0 &&
               heap[0].endTime <= arrival[i]) {

            Busy b = pop(heap, &heapSize);

            update(tree, 1, 0, k - 1, b.server, 1);
        }

        if (tree[1] == 0)
            continue;

        int start = i % k;
        int server;

        if (tree[1] == 0) {
            continue;
        }

        // Find the first available server >= start.
        int leftCount = 0;

        // Check if any available server exists in [start, k-1].
        // The segment tree search is handled below.
        server = -1;

        // Find first available in the right interval.
        int stack[64], L[64], R[64];
        int top = 0;

        stack[top] = 1;
        L[top] = 0;
        R[top++] = k - 1;

        while (top > 0) {
            top--;

            int node = stack[top];
            int l = L[top];
            int r = R[top];

            if (r < start || tree[node] == 0)
                continue;

            if (l == r) {
                server = l;
                break;
            }

            int mid = (l + r) / 2;

            stack[top] = node * 2 + 1;
            L[top] = mid + 1;
            R[top++] = r;

            stack[top] = node * 2;
            L[top] = l;
            R[top++] = mid;
        }

        if (server == -1) {
            server = find(tree, 1, 0, k - 1, 0);
        }

        update(tree, 1, 0, k - 1, server, 0);
        count[server]++;

        Busy b;
        b.endTime = arrival[i] + load[i];
        b.server = server;

        push(heap, &heapSize, b);
    }

    int maxCount = 0;

    for (int i = 0; i < k; i++) {
        if (count[i] > maxCount)
            maxCount = count[i];
    }

    int *ans = malloc(sizeof(int) * k);
    *returnSize = 0;

    for (int i = 0; i < k; i++) {
        if (count[i] == maxCount)
            ans[(*returnSize)++] = i;
    }

    free(heap);
    free(tree);
    free(count);

    return ans;
}
