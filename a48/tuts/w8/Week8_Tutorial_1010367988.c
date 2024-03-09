#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *invertTree(TreeNode *root) {
    if (root == NULL)
        return NULL;

    TreeNode *oldLeft = root->left;
    root->left = root->right;
    root->right = oldLeft;

    invertTree(root->left);
    invertTree(root->right);
    return root;
}

TreeNode *allocate_new_node(int value) {
    TreeNode *node = malloc(sizeof(TreeNode));
    if (node == NULL) {
        return NULL;
    }

    node->val = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void free_tree(TreeNode *root) {
    if (root == NULL)
        return;

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main() {
    TreeNode *root = (TreeNode *)malloc(sizeof(TreeNode));
    root->val = 4;
    root->left = allocate_new_node(2);
    root->right = allocate_new_node(7);
    root->left->left = allocate_new_node(1);
    root->left->right = allocate_new_node(3);
    root->right->left = allocate_new_node(6);
    root->right->right = allocate_new_node(9);

    invertTree(root);
    printf("%d\n", root->val);
    printf("%d\n", root->left->val);
    printf("%d\n", root->right->val);
    printf("%d\n", root->left->left->val);
    printf("%d\n", root->left->right->val);
    printf("%d\n", root->right->left->val);
    printf("%d\n", root->right->right->val);

    free_tree(root);

    return 0;
}