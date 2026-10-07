#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LEN 26
#define HASH_SIZE 10007

typedef struct Node {
 char* str;
 struct Node* next;
} Node;

Node* hashTable[HASH_SIZE];

unsigned int hash(char* s) {
 unsigned int h = 0;
 for (int i = 0; s[i]; i++) h = h * 31 + s[i];
 return h % HASH_SIZE;
}

bool hashInsert(char* s) {
 unsigned int h = hash(s);
 Node* p = hashTable[h];
 while (p) {
 if (strcmp(p->str, s) == 0) return false;
 p = p->next;
 }
 Node* node = malloc(sizeof(Node));
 node->str = strdup(s);
 node->next = hashTable[h];
 hashTable[h] = node;
 return true;
}

bool isValid(char* s) {
 int count = 0;
 for (int i = 0; s[i]; i++) {
 if (s[i] == '(') count++;
 else if (s[i] == ')') {
 if (count == 0) return false;
 count--;
 }
 }
 return count == 0;
}

/**
 * Return an array of strings, malloced, with minimum invalid parentheses removed
 */
char** removeInvalidParentheses(char* s, int* returnSize) {
 *returnSize = 0;
 char** res = malloc(sizeof(char*) * 10000);
 int front = 0, back = 0;
 char queue[10000][MAX_LEN+1];

 memset(hashTable, 0, sizeof(hashTable));

 strcpy(queue[back++], s);
 hashInsert(s);

 bool found = false;

 while (front < back) {
 int levelSize = back - front;
 for (int i = 0; i < levelSize; i++) {
 char* cur = queue[front++];

 if (isValid(cur)) {
 res[(*returnSize)++] = strdup(cur);
 found = true;
 }

 if (found) continue; // stop generating next level

 for (int j = 0; cur[j]; j++) {
 if (cur[j] != '(' && cur[j] != ')') continue;

 char next[MAX_LEN+1];
 int k = 0;
 for (int l = 0; cur[l]; l++)
 if (l != j) next[k++] = cur[l];
 next[k] = '\0';

 if (hashInsert(next)) {
 strcpy(queue[back++], next);
 }
 }
 }
 if (found) break;
 }

 return res;
}