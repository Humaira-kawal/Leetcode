struct TreeNode* insertIntoMaxTree(struct TreeNode* root, int val) {
    if (root == NULL) {
        struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if (val > root->val) {
        struct TreeNode* newNode = malloc(sizeof(struct TreeNode));
        newNode->val = val;
        newNode->left = root;
        newNode->right = NULL;
        return newNode;
    }

    root->right = insertIntoMaxTree(root->right, val);

    return root;
}