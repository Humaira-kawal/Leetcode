#include <stdbool.h>
#include <stdlib.h>

bool validateBinaryTreeNodes(int n, int* leftChild, int leftChildSize,
                             int* rightChild, int rightChildSize) {
    
    int* parent = (int*)calloc(n, sizeof(int));
    
    // Count parents of every node
    for (int i = 0; i < n; i++) {
        if (leftChild[i] != -1) {
            parent[leftChild[i]]++;
        }
        
        if (rightChild[i] != -1) {
            parent[rightChild[i]]++;
        }
    }

    // Every node must have at most one parent
    for (int i = 0; i < n; i++) {
        if (parent[i] > 1) {
            free(parent);
            return false;
        }
    }

    // Find the root (node with no parent)
    int root = -1;
    for (int i = 0; i < n; i++) {
        if (parent[i] == 0) {
            if (root != -1) {
                free(parent);
                return false;   // More than one root
            }
            root = i;
        }
    }

    // No root
    if (root == -1) {
        free(parent);
        return false;
    }

    // BFS
    int* queue = (int*)malloc(n * sizeof(int));
    bool* visited = (bool*)calloc(n, sizeof(bool));

    int front = 0, rear = 0;
    queue[rear++] = root;
    visited[root] = true;

    int count = 0;

    while (front < rear) {
        int node = queue[front++];
        count++;

        int children[2] = {leftChild[node], rightChild[node]};

        for (int i = 0; i < 2; i++) {
            int child = children[i];

            if (child != -1) {
                // Already visited means cycle
                if (visited[child]) {
                    free(parent);
                    free(queue);
                    free(visited);
                    return false;
                }

                visited[child] = true;
                queue[rear++] = child;
            }
        }
    }

    free(parent);
    free(queue);
    free(visited);

    // All nodes must belong to the same tree
    return count == n;
}