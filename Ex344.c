#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode *TreePtr;
typedef int ElementType;


struct TreeNode {
    ElementType element;
    TreePtr left;
    TreePtr right;
};
TreePtr create_node(ElementType element) {
    TreePtr new_node = (TreePtr)malloc(sizeof(struct TreeNode));
    new_node->element = element;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
TreePtr constructTree(int* preorder, int* postorder, int preStart, int preEnd, int postStart, int postEnd, int* postorderIndexMap) {
    // Base case: if no elements are left
    if (preStart > preEnd || postStart > postEnd) {
        return NULL;
    }
    TreePtr root = create_node(preorder[preStart]);
    if (preStart == preEnd) {
        return root;
    }
    int leftRootVal = preorder[preStart + 1];
    int leftRootIdx = postorderIndexMap[leftRootVal]; 
    int leftSize = leftRootIdx - postStart + 1;       

   
    root->left = constructTree(preorder, postorder,
                               preStart + 1, preStart + leftSize,
                               postStart, leftRootIdx,
                               postorderIndexMap);

    root->right = constructTree(preorder, postorder,
                                preStart + leftSize + 1, preEnd,
                                leftRootIdx + 1, postEnd - 1,
                                postorderIndexMap);

    return root;
}

void buildPostorderIndexMap(int* postorder, int size, int* postorderIndexMap) {
    for (int i = 0; i < size; i++) {
        postorderIndexMap[postorder[i]] = i;
    }
}
void inorder(TreePtr root, short *count, short total) {
    if (root != NULL) {
        inorder(root->left, count, total); // L
        if (root->element != 0) {
            if ((*count) < total - 1) {
                //printf("n: %hi ", total);
                printf("%hi ", root->element);
                //printf("[%hi]", *count); // V
            } else {
                printf("%hi\n", root->element); // V
            }
            (*count)++;
        }
        inorder(root->right, count, total); // R
    }
}
void destroy_node(TreePtr node) {
    if (node != NULL) {
        destroy_node(node->left); // L
        destroy_node(node->right); // R
        free(node); // V
    }
}

int main(){
    short n, i, j, k, count;
    //freopen("Ex344.txt", "r", stdin);
    scanf("%hi", &n);
    for(i = 0; i < n; i++){
        scanf("%hi", &j);
        int * prearr = (int*)malloc(j * sizeof(int));
        int * postarr = (int*)malloc(j * sizeof(int));
        for(k = 0; k < j; k++){
            scanf("%d", &prearr[k]);
        }
        for(k = 0; k < j; k++){
            scanf("%d", &postarr[k]);
        }
        int postorderIndexMap[1000] = {0}; 
        buildPostorderIndexMap(postarr, j, postorderIndexMap);
        TreePtr root = constructTree(prearr, postarr, 0, j-1, 0, j-1, postorderIndexMap);
        count = 0;
        inorder(root, &count, j);
        destroy_node(root);
    }
}