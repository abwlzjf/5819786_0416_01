#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct Stack {
    int top;
    int* stackArray;
} Stack;

void init(Stack* s) {
    s->top = -1;
    s->stackArray = (int*)malloc(sizeof(int) * MAX_STACK_SIZE);
}

void push(Stack* s, element item) {
    if (s->top == MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    s->stackArray[++(s->top)] = item;
}

element pop(Stack* s) {
    if (s->top == -1) {
        fprintf(stderr, "Stack is empty\n");
        return -1;
    }
    return s->stackArray[(s->top)--];
}

int eval(char* expr) {
    int value;
    Stack s;
    init(&s);

    int len = strlen(expr); //길이받기
    for (int i = 0; i < len; i++) { //길이만큼 반복
        char ch = expr[i];
        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            int op2 = pop(&s);
            int op1 = pop(&s);
            switch (ch) {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
        else if ((ch >= '0') && (ch <= '9')) {
            value = ch - '0';
            push(&s, value);
        }

    }
    return pop(&s);
}

int main() {
    char expression[MAX_STACK_SIZE];
    int result;

    printf("postfix Expression: ");
    fgets(expression, sizeof(expression), stdin);

    result = eval(expression);
    printf("Result: %d\n", result);

    return 0;
}