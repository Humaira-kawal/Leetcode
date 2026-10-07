#include <stdlib.h>

typedef struct {
    long long sum;
    int i;
    int j;
} HeapNode;

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(HeapNode* heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap[parent].sum <= heap[index].sum)
            break;

        swap(&heap[parent], &heap[index]);
        index = parent;
    }
}

void heapifyDown(HeapNode* heap, int size, int index) {
    while (1) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left].sum < heap[smallest].sum)
            smallest = left;

        if (right < size && heap[right].sum < heap[smallest].sum)
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap[index], &heap[smallest]);
        index = smallest;
    }
}

void push(HeapNode* heap, int* size, HeapNode node) {
    heap[*size] = node;
    (*size)++;
    heapifyUp(heap, *size - 1);
}

HeapNode pop(HeapNode* heap, int* size) {
    HeapNode result = heap[0];

    (*size)--;

    if (*size > 0) {
        heap[0] = heap[*size];
        heapifyDown(heap, *size, 0);
    }

    return result;
}

int** kSmallestPairs(
    int* nums1,
    int nums1Size,
    int* nums2,
    int nums2Size,
    int k,
    int* returnSize,
    int** returnColumnSizes
) {
    int** result = (int**)malloc(k * sizeof(int*));
    *returnColumnSizes = (int*)malloc(k * sizeof(int));

    int heapCapacity = nums1Size < k ? nums1Size : k;
    HeapNode* heap = (HeapNode*)malloc(heapCapacity * sizeof(HeapNode));

    int heapSize = 0;

    // Start with (nums1[i], nums2[0])
    for (int i = 0; i < heapCapacity; i++) {
        HeapNode node;
        node.sum = (long long)nums1[i] + nums2[0];
        node.i = i;
        node.j = 0;

        push(heap, &heapSize, node);
    }

    int count = 0;

    while (count < k && heapSize > 0) {
        HeapNode current = pop(heap, &heapSize);

        result[count] = (int*)malloc(2 * sizeof(int));
        result[count][0] = nums1[current.i];
        result[count][1] = nums2[current.j];

        (*returnColumnSizes)[count] = 2;
        count++;

        // Move to the next element in nums2
        if (current.j + 1 < nums2Size) {
            HeapNode next;

            next.i = current.i;
            next.j = current.j + 1;
            next.sum = (long long)nums1[next.i] + nums2[next.j];

            push(heap, &heapSize, next);
        }
    }

    *returnSize = count;

    free(heap);

    return result;
}