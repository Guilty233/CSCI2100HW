#include <stdio.h>
#include <stdlib.h>

// Structure for a tree node
typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to find the index of an element in the array
int search(int* inorder, int value, int left, int right) {
    for (int i = left; i <= right; i++) {
        if (inorder[i] == value) {
            return i;
        }
    }
    return -1; // Not found (shouldn’t happen with valid input)
}

// Recursive function to build the binary tree
Node* buildTreeRecur(int* inorder, int* preorder, int* preIndex, int left, int right) {
    // Base case: if the segment is empty
    if (left > right) {
        return NULL;
    }

    // Get the root value from preorder and increment preIndex
    int rootVal = preorder[*preIndex];
    (*preIndex)++;

    // Create the root node
    Node* root = newNode(rootVal);

    // Find the index of the root value in inorder
    int index = search(inorder, rootVal, left, right);

    // Recursively build left and right subtrees
    root->left = buildTreeRecur(inorder, preorder, preIndex, left, index - 1);
    root->right = buildTreeRecur(inorder, preorder, preIndex, index + 1, right);

    return root;
}

// Function to construct tree from inorder and preorder traversals
Node* buildTree(int* inorder, int* preorder, int size) {
    int preIndex = 0;
    return buildTreeRecur(inorder, preorder, &preIndex, 0, size - 1);
}

// Optional: Function to free the tree (for memory cleanup)
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
void printTree(Node* root) {
    if (root == NULL) return;
    printTree(root->left);
    printTree(root->right);
    printf("%d ", root->val);
}

// Example usage
int main() {
    int N;
    freopen("test332.txt", "r", stdin);
    while(scanf("%d", &N) != EOF) {
        if (N == -1) break;
        int* inorder = (int*)malloc(sizeof(int) * N);
        int* preorder = (int*)malloc(sizeof(int) * N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &preorder[i]);
        }
        for (int i = 0; i < N; i++) {
            printf("%d ", preorder[i]);
        }
        printf("pre\n");
        for (int i = 0; i < N; i++) {
            scanf("%d", &inorder[i]);
        }
        for (int i = 0; i < N; i++) {
            printf("%d ", inorder[i]);
        }
        printf("in\n");
        Node* root = buildTree(inorder, preorder, N);
        printTree(root);
        printf("\n");
        freeTree(root);
        free(inorder);
        free(preorder);
    }
    return 0;
}