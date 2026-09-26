#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 262144

typedef struct Node {
    char *key;
    char *value;
    struct Node *next;
} Node;

unsigned int hash(char *str) {
    unsigned int h = 0;

    while (*str) {
        h = h * 31 + (*str);
        str++;
    }

    return h % TABLE_SIZE;
}

char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {

    Node **table = (Node **)calloc(TABLE_SIZE, sizeof(Node *));

    // Build hash table
    for (int i = 0; i < knowledgeSize; i++) {
        char *key = knowledge[i][0];
        char *value = knowledge[i][1];

        unsigned int index = hash(key);

        Node *node = (Node *)malloc(sizeof(Node));

        node->key = key;
        node->value = value;
        node->next = table[index];

        table[index] = node;
    }

    // Result can be at most 100000 characters
    char *result = (char *)malloc(100001 * sizeof(char));

    int r = 0;
    int i = 0;

    while (s[i] != '\0') {

        // Normal character
        if (s[i] != '(') {
            result[r++] = s[i++];
            continue;
        }

        // Skip '('
        i++;

        int start = i;

        // Find ')'
        while (s[i] != ')') {
            i++;
        }

        int len = i - start;

        // Keys have maximum length 10
        char key[11];

        memcpy(key, s + start, len);
        key[len] = '\0';

        // Search hash table
        unsigned int index = hash(key);

        Node *node = table[index];

        while (node != NULL) {
            if (strcmp(node->key, key) == 0) {
                break;
            }

            node = node->next;
        }

        // Replace bracket pair
        if (node != NULL) {
            char *value = node->value;

            while (*value != '\0') {
                result[r++] = *value;
                value++;
            }
        } else {
            result[r++] = '?';
        }

        // Skip ')'
        i++;
    }

    result[r] = '\0';

    // Free hash table
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *node = table[i];

        while (node != NULL) {
            Node *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(table);

    return result;
}