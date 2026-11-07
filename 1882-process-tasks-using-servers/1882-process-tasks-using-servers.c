
#include <stdlib.h>

typedef struct {
    int weight;
    int index;
} Server;

typedef struct {
    long long freeTime;
    int weight;
    int index;
} BusyServer;

// Compare free servers by weight, then index
int compareFree(const void *a, const void *b) {
    Server *s1 = (Server *)a;
    Server *s2 = (Server *)b;

    if (s1->weight != s2->weight)
        return s1->weight - s2->weight;

    return s1->index - s2->index;
}

// Compare busy servers by free time
int compareBusy(const void *a, const void *b) {
    BusyServer *s1 = (BusyServer *)a;
    BusyServer *s2 = (BusyServer *)b;

    if (s1->freeTime < s2->freeTime) return -1;
    if (s1->freeTime > s2->freeTime) return 1;

    return s1->index - s2->index;
}

// Min heap for free servers
void pushFree(Server *heap, int *size, Server val) {
    int i = (*size)++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (compareFree(&heap[p], &val) <= 0) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = val;
}

Server popFree(Server *heap, int *size) {
    Server result = heap[0];
    Server last = heap[--(*size)];
    int i = 0;

    while (2 * i + 1 < *size) {
        int c = 2 * i + 1;
        if (c + 1 < *size &&
            compareFree(&heap[c + 1], &heap[c]) < 0)
            c++;

        if (compareFree(&last, &heap[c]) <= 0) break;

        heap[i] = heap[c];
        i = c;
    }

    if (*size > 0) heap[i] = last;
    return result;
}

// Min heap for busy servers
void pushBusy(BusyServer *heap, int *size, BusyServer val) {
    int i = (*size)++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (compareBusy(&heap[p], &val) <= 0) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = val;
}

BusyServer popBusy(BusyServer *heap, int *size) {
    BusyServer result = heap[0];
    BusyServer last = heap[--(*size)];
    int i = 0;

    while (2 * i + 1 < *size) {
        int c = 2 * i + 1;
        if (c + 1 < *size &&
            compareBusy(&heap[c + 1], &heap[c]) < 0)
            c++;

        if (compareBusy(&last, &heap[c]) <= 0) break;

        heap[i] = heap[c];
        i = c;
    }

    if (*size > 0) heap[i] = last;
    return result;
}

int* assignTasks(int* servers, int serversSize,
                 int* tasks, int tasksSize,
                 int* returnSize) {

    int n = serversSize;
    int m = tasksSize;

    *returnSize = m;

    int *ans = malloc(m * sizeof(int));

    Server *freeHeap = malloc(n * sizeof(Server));
    BusyServer *busyHeap = malloc(n * sizeof(BusyServer));

    int freeSize = 0;
    int busySize = 0;

    // Initially all servers are free
    for (int i = 0; i < n; i++) {
        Server s = {servers[i], i};
        pushFree(freeHeap, &freeSize, s);
    }

    long long time = 0;

    for (int j = 0; j < m; j++) {

        if (time < j)
            time = j;

        // Move all servers that have finished to free heap
        while (busySize > 0 &&
               busyHeap[0].freeTime <= time) {

            BusyServer b = popBusy(busyHeap, &busySize);

            Server s = {b.weight, b.index};
            pushFree(freeHeap, &freeSize, s);
        }

        // If no server is free, jump to earliest finish time
        if (freeSize == 0) {
            time = busyHeap[0].freeTime;

            while (busySize > 0 &&
                   busyHeap[0].freeTime <= time) {

                BusyServer b = popBusy(busyHeap, &busySize);

                Server s = {b.weight, b.index};
                pushFree(freeHeap, &freeSize, s);
            }
        }

        // Assign task to best available server
        Server s = popFree(freeHeap, &freeSize);

        ans[j] = s.index;

        BusyServer b = {
            time + tasks[j],
            s.weight,
            s.index
        };

        pushBusy(busyHeap, &busySize, b);
    }

    free(freeHeap);
    free(busyHeap);

    return ans;
}
