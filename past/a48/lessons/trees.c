#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 1024

typedef struct Restaurant_Score {
    char restaurant_name[MAX_STRING_LENGTH];
    char restaurant_address[MAX_STRING_LENGTH];
    int score;
} Review;

typedef struct BST_Node_Struct {
    Review rev;                    // Stores one review
    struct BST_Node_Struct *left;  // A pointer to its left child
    struct BST_Node_Struct *right; // and a pointer to its right child
} BST_Node;

BST_Node *new_BST_Node(void) {
    BST_Node *new_review = NULL; // Pointer to the new node

    new_review = (BST_Node *)calloc(1, sizeof(BST_Node));
    // Initialize the new node's content (same as with linked list)
    new_review->rev.score = -1;
    strcpy(new_review->rev.restaurant_name, "");
    strcpy(new_review->rev.restaurant_address, "");
    new_review->left = NULL;
    new_review->right = NULL;
    return new_review;
}

BST_Node *BST_insert(BST_Node *root, BST_Node *new_review) {
    if (root == NULL)      // Tree is empty, new node becomes
        return new_review; // the root

    // Determine which subtree the new key should be in
    if (strcmp(new_review->rev.restaurant_name, root->rev.restaurant_name) <=
        0) {
        root->left = BST_insert(root->left, new_review);
    } else {
        root->right = BST_insert(root->right, new_review);
    }

    return root;
}

BST_Node *BST_search(BST_Node *root, char name[1024]) {
    // Look up a restaurant review by restaurant name
    if (root == NULL)
        return NULL; // Tree or sub-tree is empty

    // Check if this node contains the review we want, if so, return
    // a pointer to it
    if (strcmp(root->rev.restaurant_name, name) == 0)
        return root;

    // Not in this node, search the corresponding subtree
    if (strcmp(name, root->rev.restaurant_name) <= 0) {
        return BST_search(root->left, name);
    } else {
        return BST_search(root->right, name);
    }
}

BST_Node *BST_delete(BST_Node *root, char name[1024]) {
    // Remove a review for a restaurant whose name matches the query
    // Assumes unique restaurant names!
    if (root == NULL)
        return NULL; // Tree or sub-tree is empty

    // Check if this node contains the review we want to delete
    if (strcmp(name, root->rev.restaurant_name) == 0) {
        BST_Node *tmp;

        if (root->left == NULL && root->right == NULL) {
            // Case a), no children. The parent will
            // be updated to have NULL instead of this
            // node's address, and we delete this node
            free(root);
            return NULL;
        } else if (root->right == NULL) {
            // Case b), only one child, left subtree
            // The parent has to be linked to the left
            // child of this node, and we free this node
            tmp = root->left;
            free(root);
            return tmp;
        } else if (root->left == NULL) {
            // Case b), only one child, right subtree
            // The parent has to be linked to the right
            // child of this node, and we free this node
            tmp = root->right;
            free(root);
            return tmp;
        } else {
            // Case c), two children.
            BST_Node *succParent = root;
            BST_Node *succ = succParent->right;
            while (succ->left != NULL) {
                succParent = succ;
                succ = succ->left;
            }

            if (succParent != root) {
                succParent->left = succ->right;
            } else {
                root->right = succ->right;
            }

            strcpy(root->rev.restaurant_name, succ->rev.restaurant_name);
            strcpy(root->rev.restaurant_address, succ->rev.restaurant_address);
            root->rev.score = succ->rev.score;

            free(succ);
            return root;
        }
    }

    // Not in this node, delete on the corresponding subtree and
    // update the the corresponding link
    if (strcmp(name, root->rev.restaurant_name) <= 0) {
        root->left = BST_delete(root->left, name);
    } else {
        root->right = BST_delete(root->right, name);
    }
    return root;
}

int main() {}