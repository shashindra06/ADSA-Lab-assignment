#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct Node
{
    int data;
    int color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
};

struct Node *NIL;

struct Node *createTree()
{
    NIL = malloc(sizeof(struct Node));

    NIL->color = BLACK;
    NIL->left = NIL;
    NIL->right = NIL;
    NIL->parent = NIL;

    return NIL;
}

struct Node *createNode(int value)
{
    struct Node *newNode = malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->color = RED;
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->parent = NIL;

    return newNode;
}

void deleteTree(struct Node *root)
{
    if (root == NIL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

void leftRotate(struct Node **root, struct Node *x)
{
    struct Node *y = x->right;

    x->right = y->left;

    if (y->left != NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NIL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void rightRotate(struct Node **root, struct Node *y)
{
    struct Node *x = y->left;

    y->left = x->right;

    if (x->right != NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NIL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void insertFix(struct Node **root, struct Node *z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            struct Node *uncle = z->parent->parent->right;

            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    leftRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(root, z->parent->parent);
            }
        }
        else
        {
            struct Node *uncle = z->parent->parent->left;

            if (uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rightRotate(root, z);
                }

                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(root, z->parent->parent);
            }
        }
    }

    (*root)->color = BLACK;
}

void insertItem(struct Node **root, int value)
{
    struct Node *z = createNode(value);
    struct Node *parent = NIL;
    struct Node *current = *root;

    while (current != NIL)
    {
        parent = current;

        if (value < current->data)
            current = current->left;
        else if (value > current->data)
            current = current->right;
        else
        {
            free(z);
            return;
        }
    }

    z->parent = parent;

    if (parent == NIL)
        *root = z;
    else if (value < parent->data)
        parent->left = z;
    else
        parent->right = z;

    insertFix(root, z);
}

struct Node *searchItem(struct Node *root, int value)
{
    while (root != NIL)
    {
        if (value == root->data)
            return root;

        if (value < root->data)
            root = root->left;
        else
            root = root->right;
    }

    return NIL;
}

struct Node *minimum(struct Node *root)
{
    while (root->left != NIL)
        root = root->left;

    return root;
}

void transplant(struct Node **root, struct Node *u, struct Node *v)
{
    if (u->parent == NIL)
        *root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    v->parent = u->parent;
}

void deleteFix(struct Node **root, struct Node *x)
{
    while (x != *root && x->color == BLACK)
    {
        if (x == x->parent->left)
        {
            struct Node *w = x->parent->right;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(root, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK &&
                w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;

                leftRotate(root, x->parent);
                x = *root;
            }
        }
        else
        {
            struct Node *w = x->parent->left;

            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(root, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK &&
                w->left->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;

                rightRotate(root, x->parent);
                x = *root;
            }
        }
    }

    x->color = BLACK;
}

void deleteItem(struct Node **root, int value)
{
    struct Node *z = searchItem(*root, value);

    if (z == NIL)
        return;

    struct Node *y = z;
    struct Node *x;
    int originalColor = y->color;

    if (z->left == NIL)
    {
        x = z->right;
        transplant(root, z, z->right);
    }
    else if (z->right == NIL)
    {
        x = z->left;
        transplant(root, z, z->left);
    }
    else
    {
        y = minimum(z->right);
        originalColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            transplant(root, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);

        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    free(z);

    if (originalColor == BLACK)
        deleteFix(root, x);
}

void inorder(struct Node *root)
{
    if (root == NIL)
        return;

    inorder(root->left);

    printf("%d(%s) ",
           root->data,
           root->color == RED ? "R" : "B");

    inorder(root->right);
}

int main()
{
    struct Node *root = createTree();

    insertItem(&root, 10);
    insertItem(&root, 20);
    insertItem(&root, 30);
    insertItem(&root, 15);
    insertItem(&root, 25);
    insertItem(&root, 5);

    printf("Inorder: ");
    inorder(root);

    if (searchItem(root, 25) != NIL)
        printf("\n25 found");
    else
        printf("\n25 not found");

    deleteItem(&root, 20);

    printf("\nAfter deleting 20: ");
    inorder(root);

    deleteTree(root);
    free(NIL);

    return 0;
}