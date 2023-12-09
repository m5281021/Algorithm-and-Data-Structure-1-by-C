#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL

struct Stack1 {
    int top;
    int *container;
};

typedef struct Stack1 stack1;

struct Stack2 {
    int top;
    int *position;
    int *container;
};

typedef struct Stack2 stack2;

void push1(stack1 *s, int max, int x) {
    if(max == s->top) return;
    s->container[s->top++] = x;
}

void push2(stack2 *s, int max, int p, int x) {
    if(max == s->top) return;
    s->position[s->top] = p;
    s->container[s->top++] = x;
}

int pop1(stack1 *s) {
    if(s->top == 0) return -1;
    s->top--;
    return s->container[s->top];
}

int pop2(stack2 *s) {
    if(s->top == 0) return -1;
    s->top--;
    return s->container[s->top];
}

int front2(stack2 *s) {
    if(s->top == 0) return -1;
    return s->position[s->top - 1];
}

void print(stack2 *s) {
    int sum = 0;
    int n = s->top;
    int *answers = nullptr;
    answers = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        answers[n - 1 - i] = pop2(s);
        sum += answers[n - 1 - i];
    }
    printf("%d\n", sum);
    printf("%d", n);
    for(int i = 0; i < n; i++) {
        printf(" %d", answers[i]);
    }
    printf("\n");
    free(answers);
}

void solve(char *c) {
    const int max = 20000;
    stack1 S1;
    S1.container = (int *)malloc(max * sizeof(int));
    S1.top = 0;
    stack2 S2;
    S2.container = (int *)malloc(max * sizeof(int));
    S2.position = (int *)malloc(max * sizeof(int));
    S2.top = 0;
    int i = 0;
    while(c[i] != '\0') {
        if(c[i] == '\\') {
            push1(&S1, max, i);
        }
        else if(c[i] == '/') {
            int j = pop1(&S1);
            if(j >= 0) {
                int sum = i - j;
                while(front2(&S2) > j) {
                    sum += pop2(&S2);
                }
                push2(&S2, max, j, sum);
            }
        }
        i++;
    }
    print(&S2);
    free(S1.container);
    free(S2.container);
    free(S2.position);
}

int main() {
    const int length = 20000;
    char line[length];
    scanf("%s", line);
    solve(line);
    return 0;
}