#include <stdio.h>

#define MAX 100

// Returns precedence of an operator
int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;

    if (op == '+' || op == '-')
        return 1;

    return 0;
}


// Converts infix expression to postfix expression
void infixToPostfix(char infix[], char postfix[])
{
    char stack[MAX];
    int top = -1;
    int postIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++)
    {
        char ch = infix[i];

        // Ignore spaces
        if (ch == ' ')
            continue;

        // If it is a number
        if (ch >= '0' && ch <= '9')
        {
            // Copy the complete number
            while (infix[i] >= '0' && infix[i] <= '9')
            {
                postfix[postIndex++] = infix[i];
                i++;
            }

            // Space separates numbers in postfix
            postfix[postIndex++] = ' ';

            i--;
        }

        // Opening parenthesis
        else if (ch == '(')
        {
            stack[++top] = ch;
        }

        // Closing parenthesis
        else if (ch == ')')
        {
            while (top != -1 && stack[top] != '(')
            {
                postfix[postIndex++] = stack[top--];
                postfix[postIndex++] = ' ';
            }

            // Remove '('
            if (top != -1)
                top--;
        }

        // Operator
        else
        {
            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(ch))
            {
                postfix[postIndex++] = stack[top--];
                postfix[postIndex++] = ' ';
            }

            stack[++top] = ch;
        }
    }

    // Pop remaining operators
    while (top != -1)
    {
        postfix[postIndex++] = stack[top--];
        postfix[postIndex++] = ' ';
    }

    postfix[postIndex] = '\0';
}


// Performs an arithmetic operation
int calculate(int left, int right, char op)
{
    if (op == '+')
        return left + right;

    if (op == '-')
        return left - right;

    if (op == '*')
        return left * right;

    if (op == '/')
        return left / right;

    return 0;
}


// Evaluates postfix expression
int evaluatePostfix(char postfix[])
{
    int stack[MAX];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        // Ignore spaces
        if (postfix[i] == ' ')
            continue;

        // If it is a number
        if (postfix[i] >= '0' && postfix[i] <= '9')
        {
            int number = 0;

            // Build complete number
            while (postfix[i] >= '0' && postfix[i] <= '9')
            {
                number = number * 10 + (postfix[i] - '0');
                i++;
            }

            stack[++top] = number;

            i--;
        }

        // If it is an operator
        else
        {
            int right = stack[top--];
            int left = stack[top--];

            int result = calculate(left, right, postfix[i]);

            stack[++top] = result;
        }
    }

    return stack[top];
}


int main(int argc, char *argv[])
{
    // Check whether an expression was provided
    if (argc < 2)
    {
        printf("Usage: ./Expr_eval \"expression\"\n");
        return 1;
    }

    char postfix[MAX];

    // Convert infix to postfix
    infixToPostfix(argv[1], postfix);

    // Evaluate postfix expression
    int result = evaluatePostfix(postfix);

    // Display the computed value
    printf("%d\n", result);

    return 0;
}