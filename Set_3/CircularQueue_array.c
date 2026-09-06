#include <stdio.h>

#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

void enqueue(int value)
{
    // Queue is full
    if((rear + 1) % SIZE == front)
    {
        printf("Queue is full\n");
        return;
    }

    // First element
    if(front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % SIZE;
    }

    queue[rear] = value;
}

void dequeue()
{
    // Queue is empty
    if(front == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Deleted: %d\n", queue[front]);

    // Only one element was present
    if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % SIZE;
    }
}

void display()
{
    if(front == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    int i = front;

    while(1)
    {
        printf("%d ", queue[i]);

        if(i == rear)
            break;

        i = (i + 1) % SIZE;
    }

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    enqueue(40);
    enqueue(50);

    display();

    dequeue();
    dequeue();

    display();

    enqueue(60);
    enqueue(70);

    display();

    return 0;
}