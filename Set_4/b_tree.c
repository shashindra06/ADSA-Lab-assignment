#include <stdio.h>
#include <stdlib.h>

#define T 3

struct Node
{
    int keys[2 * T - 1];
    struct Node *child[2 * T];
    int n;
    int leaf;
};

struct Node *createNode(int leaf)
{
    struct Node *node = malloc(sizeof(struct Node));

    node->n = 0;
    node->leaf = leaf;

    for (int i = 0; i < 2 * T; i++)
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

struct Node *searchItem(struct Node *root, int value)
{
    if (root == NULL)
        return NULL;

    int i = 0;

    while (i < root->n && value > root->keys[i])
        i++;

    if (i < root->n && value == root->keys[i])
        return root;

    if (root->leaf)
        return NULL;

    return searchItem(root->child[i], value);
}

void splitChild(struct Node *parent, int index)
{
    struct Node *full = parent->child[index];
    struct Node *newNode = createNode(full->leaf);

    newNode->n = T - 1;

    for (int i = 0; i < T - 1; i++)
        newNode->keys[i] = full->keys[i + T];

    if (!full->leaf)
    {
        for (int i = 0; i < T; i++)
            newNode->child[i] = full->child[i + T];
    }

    full->n = T - 1;

    for (int i = parent->n; i >= index + 1; i--)
        parent->child[i + 1] = parent->child[i];

    parent->child[index + 1] = newNode;

    for (int i = parent->n - 1; i >= index; i--)
        parent->keys[i + 1] = parent->keys[i];

    parent->keys[index] = full->keys[T - 1];
    parent->n++;
}

void insertNonFull(struct Node *node, int value)
{
    int i = node->n - 1;

    if (node->leaf)
    {
        while (i >= 0 && value < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = value;
        node->n++;
    }
    else
    {
        while (i >= 0 && value < node->keys[i])
            i--;

        i++;

        if (node->child[i]->n == 2 * T - 1)
        {
            splitChild(node, i);

            if (value > node->keys[i])
                i++;
        }

        insertNonFull(node->child[i], value);
    }
}

void insertItem(struct Node **root, int value)
{
    if (searchItem(*root, value) != NULL)
        return;

    struct Node *oldRoot = *root;

    if (oldRoot->n == 2 * T - 1)
    {
        struct Node *newRoot = createNode(0);

        newRoot->child[0] = oldRoot;
        *root = newRoot;

        splitChild(newRoot, 0);

        insertNonFull(newRoot, value);
    }
    else
    {
        insertNonFull(oldRoot, value);
    }
}

int findKey(struct Node *node, int value)
{
    int index = 0;

    while (index < node->n && node->keys[index] < value)
        index++;

    return index;
}

int getPredecessor(struct Node *node)
{
    while (!node->leaf)
        node = node->child[node->n];

    return node->keys[node->n - 1];
}

int getSuccessor(struct Node *node)
{
    while (!node->leaf)
        node = node->child[0];

    return node->keys[0];
}

void removeFromLeaf(struct Node *node, int index)
{
    for (int i = index + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];

    node->n--;
}

void borrowFromPrevious(struct Node *node, int index)
{
    struct Node *child = node->child[index];
    struct Node *sibling = node->child[index - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf)
    {
        for (int i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];

        child->child[0] = sibling->child[sibling->n];
    }

    child->keys[0] = node->keys[index - 1];

    node->keys[index - 1] = sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}

void borrowFromNext(struct Node *node, int index)
{
    struct Node *child = node->child[index];
    struct Node *sibling = node->child[index + 1];

    child->keys[child->n] = node->keys[index];

    if (!child->leaf)
        child->child[child->n + 1] = sibling->child[0];

    node->keys[index] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf)
    {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] = sibling->child[i];
    }

    child->n++;
    sibling->n--;
}

void merge(struct Node *node, int index)
{
    struct Node *child = node->child[index];
    struct Node *sibling = node->child[index + 1];

    child->keys[T - 1] = node->keys[index];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + T] = sibling->keys[i];

    if (!child->leaf)
    {
        for (int i = 0; i <= sibling->n; i++)
            child->child[i + T] = sibling->child[i];
    }

    child->n += sibling->n + 1;

    for (int i = index + 1; i < node->n; i++)
        node->keys[i - 1] = node->keys[i];

    for (int i = index + 2; i <= node->n; i++)
        node->child[i - 1] = node->child[i];

    node->n--;

    free(sibling);
}

void removeFromNode(struct Node *node, int value);

void fillChild(struct Node *node, int index)
{
    if (index != 0 && node->child[index - 1]->n >= T)
        borrowFromPrevious(node, index);

    else if (index != node->n && node->child[index + 1]->n >= T)
        borrowFromNext(node, index);

    else
    {
        if (index != node->n)
            merge(node, index);
        else
            merge(node, index - 1);
    }
}

void removeFromNode(struct Node *node, int value)
{
    int index = findKey(node, value);

    if (index < node->n && node->keys[index] == value)
    {
        if (node->leaf)
        {
            removeFromLeaf(node, index);
        }
        else
        {
            if (node->child[index]->n >= T)
            {
                int predecessor = getPredecessor(node->child[index]);
                node->keys[index] = predecessor;
                removeFromNode(node->child[index], predecessor);
            }
            else if (node->child[index + 1]->n >= T)
            {
                int successor = getSuccessor(node->child[index + 1]);
                node->keys[index] = successor;
                removeFromNode(node->child[index + 1], successor);
            }
            else
            {
                merge(node, index);
                removeFromNode(node->child[index], value);
            }
        }
    }
    else
    {
        if (node->leaf)
            return;

        int lastChild = (index == node->n);

        if (node->child[index]->n < T)
            fillChild(node, index);

        if (lastChild && index > node->n)
            removeFromNode(node->child[index - 1], value);
        else
            removeFromNode(node->child[index], value);
    }
}

void deleteItem(struct Node **root, int value)
{
    if (*root == NULL)
        return;

    removeFromNode(*root, value);

    if ((*root)->n == 0)
    {
        struct Node *oldRoot = *root;

        if (oldRoot->leaf)
        {
            free(oldRoot);
            *root = NULL;
        }
        else
        {
            *root = oldRoot->child[0];
            free(oldRoot);
        }
    }
}

void display(struct Node *root)
{
    if (root == NULL)
        return;

    int i;

    for (i = 0; i < root->n; i++)
    {
        if (!root->leaf)
            display(root->child[i]);

        printf("%d ", root->keys[i]);
    }

    if (!root->leaf)
        display(root->child[i]);
}

int main()
{
    struct Node *root = createTree();

    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};

    for (int i = 0; i < 8; i++)
        insertItem(&root, values[i]);

    printf("B Tree: ");
    display(root);

    if (searchItem(root, 12))
        printf("\n12 found");
    else
        printf("\n12 not found");

    deleteItem(&root, 6);

    printf("\nAfter deleting 6: ");
    display(root);

    deleteTree(root);

    return 0;
}