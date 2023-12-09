#include <stdio.h>
#include <stdlib.h>

void push(int max, int *top, int *stack, int input) {
    if(*top == max) return;
    stack[*top] = input;
    *top += 1;
}

int pop(int *top, int *stack) {
    if(*top == 0) return 0;
    *top -= 1;
    return stack[*top];
}

int main() {
    const int max = 100;
    int stack[max];
    int top = 0;
    char in[7];
    while(scanf("%s", in) != EOF) {
        if(in[0] == '+') {
            int a = pop(&top, stack);
            int b = pop(&top, stack);
            push(max, &top, stack, a + b);
        }
        else if(in[0] == '-') {
            int a = pop(&top, stack);
            int b = pop(&top, stack);
            push(max, &top, stack, b - a);
        }
        else if(in[0] == '*') {
            int a = pop(&top, stack);
            int b = pop(&top, stack);
            push(max, &top, stack, a * b);
        }
        else {
            push(max, &top, stack, atoi(in));
        }
    }
    printf("%d\n", pop(&top, stack));
    return 0;
}