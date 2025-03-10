#include <stdio.h>
#include <stdlib.h>
typedef struct AVLNode *TreePtr;
typedef int ElementType;
short count;
struct AVLNode {
    ElementType element;
    int height;
    TreePtr left;
    TreePtr right;
};
int height(TreePtr tree) {
    if (tree != NULL) {
        return tree->height;
    } else {
        return -1; // Empty tree
    }
}
int max(int a, int b) {
    return a > b ? a : b;
}
TreePtr create_node(ElementType element) {
    TreePtr new_node = (TreePtr)malloc(sizeof(struct AVLNode));
    new_node->element = element;
    new_node->height = 0; // Leaf node
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
TreePtr left_rotation(TreePtr x) {
    count++;
    // Swap pointers
    TreePtr y = x->right;
    x->right = y->left; // T2
    y->left = x;
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(x->height, height(y->right)) + 1;
    return y;
}
TreePtr right_rotation(TreePtr x) {
    count++;
    // Swap pointers
    TreePtr y = x->left;
    x->left = y->right; // T2
    y->right = x;
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), x->height) + 1;
    return y;
}
TreePtr right_left_rotation(TreePtr x) {
    x->right = right_rotation(x->right); // Step 1
    return left_rotation(x); // Step 2
}
TreePtr left_right_rotation(TreePtr x) {
    x->left = left_rotation(x->left); // Step 1
    return right_rotation(x); // Step 2
}
TreePtr insert_node(ElementType element, TreePtr tree) {
    if (tree == NULL) {
        tree = create_node(element);
    } else if (element < tree->element) {
        tree->left = insert_node(element, tree->left);
        if (height(tree->left) - height(tree->right) == 2) {
            if (element < tree->left->element) { // Right rotation (LL case)
                tree = right_rotation(tree);
            } else { // Left-right rotation (LR case)
                tree = left_right_rotation(tree);
            }
        }
    } else if (element > tree->element) {
        tree->right = insert_node(element, tree->right);
        if (height(tree->right) - height(tree->left) == 2) {
            if (element > tree->right->element) { // Left rotation (RR case)
                tree = left_rotation(tree);
            } else { // Right-left rotation (RL case)
                tree = right_left_rotation(tree);
            }
        }
    }
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}
void destroy_node(TreePtr node) {
    if (node != NULL) {
        destroy_node(node->left); // L
        destroy_node(node->right); // R
        free(node); // V
    }
}
/*void inorder(TreePtr root) {
    if (root != NULL) {
        inorder(root->left); // L
        printf("%d ", root->element); // V
        inorder(root->right); // R
    }
}*/

int main(){
    short n, i, j, k;
    int x;
    //freopen("test341.txt", "r", stdin);
    scanf("%hi", &n);
    for(i = 0; i < n; i++){
        scanf("%hi", &j);
        scanf("%d", &x);
        TreePtr root = create_node(x);
        count = 0;
        for(k = 1; k < j; k++){
            scanf("%d", &x);
            root = insert_node(x, root);
        }
        //inorder(root);
        printf("%d\n", count);
        destroy_node(root);
    }
}