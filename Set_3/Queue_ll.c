#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *rear = NULL;

void enqueue(int value)
{
    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;

    // Queue is empty
    if(rear == NULL)
    {
        rear = newNode;
        newNode->next = newNode;
    }
    else
    {
        newNode->next = rear->next;
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue()
{
    if(rear == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    struct Node *front = rear->next;

    printf("Deleted: %d\n", front->data);

    // Only one node
    if(front == rear)
    {
        rear = NULL;
    }
    else
    {
        rear->next = front->next;
    }

    free(front);
}

void display()
{
    if(rear == NULL)
    {
        printf("Queue is empty\n");
        return;
    }

    struct Node *front = rear->next;
    struct Node *temp = front;

    printf("Queue: ");

    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    while(temp != front);

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);

    display();

    dequeue();
    dequeue();

    display();

    enqueue(50);
    enqueue(60);

    display();

    return 0;
}