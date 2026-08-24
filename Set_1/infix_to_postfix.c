#include <stdio.h>

int precedence(char s) {
    if (s == '*' || s == '/') {
        return 2;
    }
    else if (s == '+' || s == '-') {
        return 1;
    }
    return 0;
}

void infixtopostfix(char infix[]) {

    char stack[100];
    int top = -1;

    char postfix[100];
    int a = -1;

    int length = 0;

    while (infix[length] != '\0') {
        length++;
    }

    for (int i = 0; i < length; i++) {

        if (infix[i] >= '0' && infix[i] <= '9') {
            a++;
            postfix[a] = infix[i];
        }

        else if (infix[i] == '(') {
            top++;
            stack[top] = infix[i];
        }

        else if (infix[i] == ')') {

            while (top != -1 && stack[top] != '(') {
                a++;
                postfix[a] = stack[top];
                top--;
            }

            if (top != -1) {
                top--;              // remove '('
            }
        }

        else {  // operator

            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(infix[i])) {

                a++;
                postfix[a] = stack[top];
                top--;
            }

            top++;
            stack[top] = infix[i];
        }
    }

    // Pop remaining operators
    while (top != -1) {
        a++;
        postfix[a] = stack[top];
        top--;
    }

    // Print postfix expression
    for (int i = 0; i <= a; i++) {
        printf("%c", postfix[i]);
    }

    printf("\n");
}

int main() {

    char infix[] = {'3', '+', '4', '*', '5', '\0'};

    infixtopostfix(infix);

    return 0;
}