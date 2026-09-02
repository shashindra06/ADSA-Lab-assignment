#include <stdio.h>

#define MAX 100

int precedence(char operator) {
    if (operator == '*' || operator == '/') {
        return 2;
    }

    if (operator == '+' || operator == '-') {
        return 1;
    }

    return 0;
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

void infixToPostfix(char infix[], char postfix[]) {

    char stack[MAX];
    int top = -1;
    int postfixIndex = 0;

    for (int i = 0; infix[i] != '\0'; i++) {

        char ch = infix[i];

        // Operand
        if (ch >= '0' && ch <= '9') {
            postfix[postfixIndex++] = ch;
        }

        // Opening parenthesis
        else if (ch == '(') {
            stack[++top] = ch;
        }

        // Closing parenthesis
        else if (ch == ')') {

            while (top != -1 && stack[top] != '(') {
                postfix[postfixIndex++] = stack[top--];
            }

            if (top != -1) {
                top--;       // Remove '('
            }
        }

        // Operator
        else if (isOperator(ch)) {

            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(ch)) {

                postfix[postfixIndex++] = stack[top--];
            }

            stack[++top] = ch;
        }
    }

    // Pop remaining operators
    while (top != -1) {
        postfix[postfixIndex++] = stack[top--];
    }

    // Terminate the C string
    postfix[postfixIndex] = '\0';
}

int main()
{
    char infix[MAX];
    char postfix[MAX];

    printf("Enter an infix expression: ");
    fgets(infix, MAX, stdin);

    // Remove the newline added by fgets()
    for (int i = 0; infix[i] != '\0'; i++)
    {
        if (infix[i] == '\n')
        {
            infix[i] = '\0';
            break;
        }
    }

    infixToPostfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}