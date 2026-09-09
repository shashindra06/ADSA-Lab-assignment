#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void preorder(struct Node *root)
{
    if (root == NULL)
        return;

    struct Node *stack[MAX];
    int top = -1;

    stack[++top] = root;

    while (top != -1)
    {
        struct Node *current = stack[top--];

        printf("%d ", current->data);

        /* Push right first */
        if (current->right != NULL)
            stack[++top] = current->right;

        /* Push left second */
        if (current->left != NULL)
            stack[++top] = current->left;
    }
}

int main()
{
    struct Node *root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->left->right = createNode(5);

    root->right->left = createNode(6);
    root->right->right = createNode(7);

    printf("Tree: 1(2,3) 2(4,5) 3(6,7)\n");

    printf("Preorder: ");
    preorder(root);

    printf("\n");

    return 0;
}