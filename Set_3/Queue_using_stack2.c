#include <stdio.h>

#define SIZE 100

int stack1[SIZE];
int stack2[SIZE];

int top1 = -1;
int top2 = -1;

void push1(int value)
{
    stack1[++top1] = value;
}

void push2(int value)
{
    stack2[++top2] = value;
}

int pop1()
{
    return stack1[top1--];
}

int pop2()
{
    return stack2[top2--];
}

void enqueue(int value)
{
    // Simply push into Stack 1
    push1(value);
}

int dequeue()
{
    if(top1 == -1)
    {
        printf("Queue is empty\n");
        return -1;
    }

    // Move everything from Stack 1 to Stack 2
    while(top1 != -1)
    {
        push2(pop1());
    }

    // Oldest element is now on top of Stack 2
    int value = pop2();

    // Move remaining elements back
    while(top2 != -1)
    {
        push1(pop2());
    }

    return value;
}

void display()
{
    if(top1 == -1)
    {
        printf("Queue is empty\n");
        return;
    }

    printf("Queue: ");

    for(int i = 0; i <= top1; i++)
        printf("%d ", stack1[i]);

    printf("\n");
}

int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);

    display();

    printf("Deleted: %d\n", dequeue());

    display();

    enqueue(40);

    display();

    printf("Deleted: %d\n", dequeue());
    printf("Deleted: %d\n", dequeue());

    display();

    return 0;
}