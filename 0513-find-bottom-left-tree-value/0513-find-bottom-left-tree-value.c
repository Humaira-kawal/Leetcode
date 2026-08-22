int findBottomLeftValue(struct TreeNode* root) {
    struct TreeNode* queue[10000];
    int front = 0, rear = 0;
    int answer = root->val;

    queue[rear++] = root;

    while (front < rear) {
        int levelSize = rear - front;

        for (int i = 0; i < levelSize; i++) {
            struct TreeNode* node = queue[front++];

            // First node of this level
            if (i == 0) {
                answer = node->val;
            }

            if (node->left != NULL) {
                queue[rear++] = node->left;
            }

            if (node->right != NULL) {
                queue[rear++] = node->right;
            }
        }
    }

    return answer;
}