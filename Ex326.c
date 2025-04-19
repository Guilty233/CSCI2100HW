#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Structure for a tree node
typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* newNode(int val) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Find index of a value in inorder array
int findIndex(int arr[], int start, int end, int val) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == val) return i;
    }
    return -1; // Should not happen with valid input
}

// Build tree from inorder and postorder traversals
Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int* postIndex) {
    if (inStart > inEnd) return NULL;

    Node* root = newNode(postorder[*postIndex]);
    (*postIndex)--;

    if (inStart == inEnd) return root;

    int inIndex = findIndex(inorder, inStart, inEnd, root->val);

    root->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex);
    root->left = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex);

    return root;
}

// Find the leaf with the minimum path sum
void minPathLeaf(Node* root, int currSum, int* minSum, int* minLeaf) {
    if (root == NULL) return;

    currSum += root->val;

    if (root->left == NULL && root->right == NULL) {
        if (currSum < *minSum) {
            *minSum = currSum;
            *minLeaf = root->val;
        }
        return;
    }

    minPathLeaf(root->left, currSum, minSum, minLeaf);
    minPathLeaf(root->right, currSum, minSum, minLeaf);
}

// Free the tree memory
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Parse a line into an array and return the count of numbers
int parseLine(char* line, int* arr) {
    int count = 0;
    char* token = strtok(line, " \n");
    while (token != NULL) {
        arr[count++] = atoi(token);
        token = strtok(NULL, " \n");
    }
    return count;
}

int main() {
    char line[1000]; // Buffer for reading lines
    int inorder[1000], postorder[1000]; // Max size assumption
    int pair = 0; // 0 for inorder, 1 for postorder
    freopen("test326.txt", "r", stdin); // Redirect input from file
    while (fgets(line, sizeof(line), stdin)) {
        // Remove trailing newline
        line[strcspn(line, "\n")] = 0;

        // Check for end of input
        if (strcmp(line, "255") == 0) break;

        if (pair == 0) {
            // Parse inorder
            int n = parseLine(line, inorder);
            pair = 1;
        } else {
            // Parse postorder
            int n = parseLine(line, postorder);

            // Build the tree
            int postIndex = n - 1;
            Node* root = buildTree(inorder, postorder, 0, n - 1, &postIndex);

            // Find the minimum path leaf
            int minSum = INT_MAX;
            int minLeaf = 0;
            minPathLeaf(root, 0, &minSum, &minLeaf);

            // Output result
            printf("%d\n", minLeaf);

            // Clean up
            freeTree(root);
            pair = 0; // Reset for next pair
        }
    }
    return 0;
}