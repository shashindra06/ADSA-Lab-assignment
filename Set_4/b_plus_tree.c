#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

struct Node
{
    int leaf;
    int n;
    int key[ORDER];

    struct Node *child[ORDER + 1];
    struct Node *parent;
    struct Node *next;
};

struct Node *createNode(int leaf)
{
    struct Node *node = malloc(sizeof(struct Node));

    node->leaf = leaf;
    node->n = 0;
    node->parent = NULL;
    node->next = NULL;

    for (int i = 0; i <= ORDER; i++)
        node->child[i] = NULL;

    return node;
}

struct Node *createTree()
{
    return createNode(1);
}

void deleteTree(struct Node *root)
{
    if (root == NULL)
        return;

    if (!root->leaf)
    {
        for (int i = 0; i <= root->n; i++)
            deleteTree(root->child[i]);
    }

    free(root);
}

struct Node *findLeaf(struct Node *root, int value)
{
    while (!root->leaf)
    {
        int i = 0;

        while (i < root->n && value >= root->key[i])
            i++;

        root = root->child[i];
    }

    return root;
}

int searchItem(struct Node *root, int value)
{
    struct Node *leaf = findLeaf(root, value);

    for (int i = 0; i < leaf->n; i++)
    {
        if (leaf->key[i] == value)
            return 1;
    }

    return 0;
}

void insertParent(struct Node **root,
                  struct Node *left,
                  int value,
                  struct Node *right)
{
    struct Node *parent = left->parent;

    /* Root has to be created */
    if (parent == NULL)
    {
        parent = createNode(0);

        parent->key[0] = value;
        parent->child[0] = left;
        parent->child[1] = right;
        parent->n = 1;

        left->parent = parent;
        right->parent = parent;

        *root = parent;
        return;
    }

    int i = 0;

    while (parent->child[i] != left)
        i++;

    for (int j = parent->n; j > i; j--)
    {
        parent->key[j] = parent->key[j - 1];
        parent->child[j + 1] = parent->child[j];
    }

    parent->key[i] = value;
    parent->child[i + 1] = right;
    parent->n++;

    right->parent = parent;
}

void splitInternal(struct Node **root, struct Node *node)
{
    int mid = node->n / 2;
    int separator = node->key[mid];

    struct Node *right = createNode(0);

    right->n = node->n - mid - 1;

    for (int i = 0; i < right->n; i++)
        right->key[i] = node->key[mid + 1 + i];

    for (int i = 0; i <= right->n; i++)
    {
        right->child[i] = node->child[mid + 1 + i];
        right->child[i]->parent = right;
    }

    node->n = mid;

    right->parent = node->parent;

    insertParent(root, node, separator, right);

    if (node->parent != NULL &&
        node->parent->n == ORDER)
    {
        splitInternal(root, node->parent);
    }
}

void insertItem(struct Node **root, int value)
{
    if (searchItem(*root, value))
        return;

    struct Node *leaf = findLeaf(*root, value);

    int i = leaf->n - 1;

    while (i >= 0 && leaf->key[i] > value)
    {
        leaf->key[i + 1] = leaf->key[i];
        i--;
    }

    leaf->key[i + 1] = value;
    leaf->n++;

    /* Leaf is not full */
    if (leaf->n < ORDER)
        return;

    /* Split leaf */
    struct Node *right = createNode(1);

    int mid = ORDER / 2;

    right->n = ORDER - mid;

    for (i = 0; i < right->n; i++)
        right->key[i] = leaf->key[mid + i];

    leaf->n = mid;

    right->next = leaf->next;
    leaf->next = right;

    right->parent = leaf->parent;

    /* First key of right leaf becomes separator */
    insertParent(root, leaf, right->key[0], right);

    if (right->parent != NULL &&
        right->parent->n == ORDER)
    {
        splitInternal(root, right->parent);
    }
}

/*
   Collect all keys except the value to be deleted.
*/
void collectKeys(struct Node *root,
                 int values[],
                 int *count,
                 int deletedValue)
{
    struct Node *leaf = root;

    while (!leaf->leaf)
        leaf = leaf->child[0];

    while (leaf != NULL)
    {
        for (int i = 0; i < leaf->n; i++)
        {
            if (leaf->key[i] != deletedValue)
                values[(*count)++] = leaf->key[i];
        }

        leaf = leaf->next;
    }
}

void deleteItem(struct Node **root, int value)
{
    if (!searchItem(*root, value))
        return;

    int values[1000];
    int count = 0;

    collectKeys(*root, values, &count, value);

    deleteTree(*root);

    *root = createTree();

    for (int i = 0; i < count; i++)
        insertItem(root, values[i]);
}

void display(struct Node *root)
{
    struct Node *leaf = root;

    while (!leaf->leaf)
        leaf = leaf->child[0];

    printf("Leaves: ");

    while (leaf != NULL)
    {
        printf("[ ");

        for (int i = 0; i < leaf->n; i++)
            printf("%d ", leaf->key[i]);

        printf("] ");

        leaf = leaf->next;
    }

    printf("\n");
}

int main()
{
    struct Node *root = createTree();

    int values[] =
    {
        10, 20, 5, 15,
        25, 30, 35, 40,
        45, 50, 55, 60
    };

    for (int i = 0; i < 12; i++)
        insertItem(&root, values[i]);

    printf("B+ Tree:\n");
    display(root);

    if (searchItem(root, 25))
        printf("25 found\n");
    else
        printf("25 not found\n");

    deleteItem(&root, 25);

    printf("After deleting 25:\n");
    display(root);

    deleteTree(root);

    return 0;
}