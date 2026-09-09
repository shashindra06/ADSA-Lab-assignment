#include <stdio.h>
#include <stdlib.h>

#define ORDER 4

struct Node
{
    int keys[ORDER];
    struct Node *child[ORDER + 1];

    int n;
    int leaf;

    struct Node *next;
};

struct Node *createNode(int leaf)
{
    struct Node *node = malloc(sizeof(struct Node));

    node->n = 0;
    node->leaf = leaf;
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

        while (i < root->n && value >= root->keys[i])
            i++;

        root = root->child[i];
    }

    return root;
}

int searchItem(struct Node *root, int value)
{
    if (root == NULL)
        return 0;

    struct Node *leaf = findLeaf(root, value);

    for (int i = 0; i < leaf->n; i++)
    {
        if (leaf->keys[i] == value)
            return 1;
    }

    return 0;
}

void insertLeaf(struct Node *leaf, int value)
{
    int i = leaf->n - 1;

    while (i >= 0 && leaf->keys[i] > value)
    {
        leaf->keys[i + 1] = leaf->keys[i];
        i--;
    }

    leaf->keys[i + 1] = value;
    leaf->n++;
}

void insertItem(struct Node *root, int value)
{
    /*
       Simple lab implementation:
       Insert into the appropriate leaf.
       If the leaf is full, split it.
    */

    if (searchItem(root, value))
        return;

    struct Node *leaf = findLeaf(root, value);

    if (leaf->n < ORDER)
    {
        insertLeaf(leaf, value);
        return;
    }

    int temp[ORDER + 1];

    for (int i = 0; i < ORDER; i++)
        temp[i] = leaf->keys[i];

    int i = ORDER - 1;

    while (i >= 0 && temp[i] > value)
    {
        temp[i + 1] = temp[i];
        i--;
    }

    temp[i + 1] = value;

    int mid = (ORDER + 1) / 2;

    leaf->n = mid;

    for (i = 0; i < mid; i++)
        leaf->keys[i] = temp[i];

    struct Node *newLeaf = createNode(1);

    for (i = mid; i < ORDER + 1; i++)
        newLeaf->keys[i - mid] = temp[i];

    newLeaf->n = ORDER + 1 - mid;

    newLeaf->next = leaf->next;
    leaf->next = newLeaf;

    printf("Leaf split occurred. Separator: %d\n",
           newLeaf->keys[0]);
}

void deleteItem(struct Node *root, int value)
{
    if (!searchItem(root, value))
        return;

    struct Node *leaf = findLeaf(root, value);

    int i = 0;

    while (leaf->keys[i] != value)
        i++;

    for (; i < leaf->n - 1; i++)
        leaf->keys[i] = leaf->keys[i + 1];

    leaf->n--;
}

void displayLeaves(struct Node *root)
{
    if (root == NULL)
        return;

    struct Node *leaf = root;

    while (!leaf->leaf)
        leaf = leaf->child[0];

    printf("Leaves: ");

    while (leaf != NULL)
    {
        printf("[ ");

        for (int i = 0; i < leaf->n; i++)
            printf("%d ", leaf->keys[i]);

        printf("] ");

        leaf = leaf->next;
    }

    printf("\n");
}

int main()
{
    struct Node *root = createTree();

    int values[] =
        {10, 20, 5, 15, 25, 30, 35};

    for (int i = 0; i < 7; i++)
        insertItem(root, values[i]);

    displayLeaves(root);

    if (searchItem(root, 25))
        printf("25 found\n");
    else
        printf("25 not found\n");

    deleteItem(root, 25);

    printf("After deleting 25:\n");
    displayLeaves(root);

    deleteTree(root);

    return 0;
}