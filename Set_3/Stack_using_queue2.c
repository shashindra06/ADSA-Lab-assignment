#include <stdio.h>

#define SIZE 100

int queue1[SIZE];
int queue2[SIZE];

int front1 = 0, rear1 = -1;
int front2 = 0, rear2 = -1;

void enqueue1(int value)
{
    queue1[++rear1] = value;
}

void enqueue2(int value)
{
    queue2[++rear2] = value;
}

int dequeue1()
{
    return queue1[front1++];
}

int dequeue2()
{
    return queue2[front2++];
}

void push(int value)
{
    enqueue1(value);
}

int pop()
{
    if(front1 > rear1)
    {
        printf("Stack is empty\n");
        return -1;
    }

    // Move all except the last element
    while(front1 < rear1)
    {
        enqueue2(dequeue1());
    }

    // Last element is the stack top
    int value = dequeue1();

    // Move remaining elements back to Q1
    while(front2 <= rear2)
    {
        enqueue1(dequeue2());
    }

    // Reset Q2
    front2 = 0;
    rear2 = -1;

    return value;
}

void display()
{
    if(front1 > rear1)
    {
        printf("Stack is empty\n");
        return;
    }

    printf("Stack: ");

    // Display from newest to oldest
    for(int i = rear1; i >= front1; i--)
        printf("%d ", queue1[i]);

    printf("\n");
}

int main()
{
    push(10);
    push(20);
    push(30);

    display();

    printf("Popped: %d\n", pop());

    display();

    push(40);

    display();

    printf("Popped: %d\n", pop());
    printf("Popped: %d\n", pop());

    display();

    return 0;
}