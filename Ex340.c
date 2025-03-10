#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TreeNode *TreePtr;
typedef short ElementType;


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

TreePtr insert_node(ElementType element, TreePtr parent, int isRight) {
    TreePtr child = create_node(element);
    if (parent != NULL) {
        if (isRight) {
            parent->right = child;
        } else {
            parent->left = child;
        }
    }
    return child;
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

typedef struct {
    int capacity;
    int numofelements;
    int head;
    int tail;
    TreePtr *data;
} queue;

int createqueue(queue *q, int capacity) {
    q->data = (TreePtr*)malloc(sizeof(TreePtr) * capacity); 
    if (q->data == NULL) {
        return 0; 
    }
    q->capacity = capacity;
    q->numofelements = 0;
    q->head = 0;
    q->tail = -1;
    return 1;
}

int enqueue(queue *q, TreePtr element) {
    if (q->numofelements == q->capacity) {
        return 0;
    }
    q->tail = (q->tail + 1) % q->capacity;
    q->data[q->tail] = element;
    q->numofelements++;
    return 1;
}

int dequeue(queue *q) {
    if (q->numofelements == 0) {
        return 0;
    }
    q->head = (q->head + 1) % q->capacity;
    q->numofelements--;
    return 1;
}

void freequeue(queue *q) {
    free(q->data);
    free(q);
}

void destroy_node(TreePtr node) {
    if (node != NULL) {
        destroy_node(node->left); // L
        destroy_node(node->right); // R
        free(node); // V
    }
}

int main() {
    short n, i, j, k, countzero;
    //freopen("test340.txt", "r", stdin); 
    scanf("%hi", &k);
    for(j = 0; j < k; j++){
        countzero = 0;
        scanf("%hi", &n);
        short *arr = (short*)malloc(n * sizeof(short));
        
        for (i = 0; i < n; i++) {
            scanf("%hi", &arr[i]);
            if(arr[i] == 0){
                countzero++;
            }
        }
        TreePtr root = create_node(arr[0]);
        queue *q = malloc(sizeof(queue));
        
        createqueue(q, n);
        enqueue(q, root);
        for (i = 0; i < n; i++) {
            TreePtr parent = q->data[q->head];
            if ((i + 1) * 2 - 1 < n) {
                parent->left = insert_node(arr[(i + 1) * 2 - 1], parent, 0);
                enqueue(q, parent->left);
            }
            if ((i + 1) * 2 < n) {
                parent->right = insert_node(arr[(i + 1) * 2], parent, 1);
                enqueue(q, parent->right);
            }
            dequeue(q);
        }
        short count = 0;
        inorder(root, &count, n - countzero);
        free(arr);
        freequeue(q);
        destroy_node(root);
    }

    return 0;
}