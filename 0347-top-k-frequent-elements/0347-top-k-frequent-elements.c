#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

int* topKFrequent(int* nums, int numsSize, int k, int* returnSize) {
    int freq[20001] = {0};

    // Step 1: Count frequencies
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i] + 10000]++;
    }

    // Step 2: Create buckets for frequencies
    Node** bucket = (Node**)calloc(numsSize + 1, sizeof(Node*));

    // Step 3: Put each unique number into its frequency bucket
    for (int value = -10000; value <= 10000; value++) {
        int f = freq[value + 10000];

        if (f > 0) {
            Node* node = (Node*)malloc(sizeof(Node));
            node->value = value;
            node->next = bucket[f];
            bucket[f] = node;
        }
    }

    // Step 4: Collect k most frequent elements
    int* result = (int*)malloc(k * sizeof(int));
    int count = 0;

    for (int f = numsSize; f >= 1 && count < k; f--) {
        Node* current = bucket[f];

        while (current != NULL && count < k) {
            result[count++] = current->value;
            current = current->next;
        }
    }

    *returnSize = k;

    // Step 5: Free memory
    for (int f = 1; f <= numsSize; f++) {
        Node* current = bucket[f];

        while (current != NULL) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(bucket);

    return result;
}