#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};

int height(struct Node *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

struct Node *createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->height = 1;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node *createTree()
{
    return NULL;
}

void deleteTree(struct Node *root)
{
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int getBalance(struct Node *root)
{
    if (root == NULL)
        return 0;

    return height(root->left) - height(root->right);
}

struct Node *insertItem(struct Node *root, int value)
{
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insertItem(root->left, value);
    else if (value > root->data)
        root->right = insertItem(root->right, value);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // RR
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // LR
    if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL
    if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node *minValueNode(struct Node *root)
{
    struct Node *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}

struct Node *deleteItem(struct Node *root, int value)
{
    if (root == NULL)
        return root;

    if (value < root->data)
        root->left = deleteItem(root->left, value);

    else if (value > root->data)
        root->right = deleteItem(root->right, value);

    else
    {
        if (root->left == NULL || root->right == NULL)
        {
            struct Node *temp;

            if (root->left != NULL)
                temp = root->left;
            else
                temp = root->right;

            if (temp == NULL)
            {
                free(root);
                return NULL;
            }
            else
            {
                *root = *temp;
                free(temp);
            }
        }
        else
        {
            struct Node *temp = minValueNode(root->right);

            root->data = temp->data;
            root->right = deleteItem(root->right, temp->data);
        }
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    // LL
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node *searchItem(struct Node *root, int value)
{
    while (root != NULL)
    {
        if (value == root->data)
            return root;

        if (value < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return NULL;
}

void inorder(struct Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main()
{
    struct Node *root = createTree();

    root = insertItem(root, 30);
    root = insertItem(root, 20);
    root = insertItem(root, 10);
    root = insertItem(root, 25);
    root = insertItem(root, 40);
    root = insertItem(root, 50);

    printf("Inorder: ");
    inorder(root);

    if (searchItem(root, 25))
        printf("\n25 found");
    else
        printf("\n25 not found");

    root = deleteItem(root, 20);

    printf("\nAfter deleting 20: ");
    inorder(root);

    deleteTree(root);

    return 0;
}