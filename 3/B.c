#include <stdio.h>
#include <stdlib.h>

struct Queue {
    char *names;
    int *times;
    int head;
    int tail;
};

typedef struct Queue queue;

void copy(char *target, char *copied) {
    while(*copied != '\0') {
        *target = *copied;
        target++;
        copied++;
    }
    *target = '\0';
}

void enqueue(queue *q, int max, int length, char *inputName, int inputTime) {
    q->tail %= max;
    int now = q->tail;
    copy(&q->names[now * length], inputName);
    q->times[now] = inputTime;
    q->tail++;
}

int dequeue(queue *q, int max, int length, char *target) {
    q->head %= max;
    int now = q->head;
    copy(target, &q->names[now * length]);
    q->head++;
    return q->times[now];
}

int judge(queue *q) {
    if(q->tail == q->head) return 0;
    else return 1;
}

void solve(int n, int q) {
    const int max = n + 1;
    const int length = 10 + 1;
    queue Q;
    Q.head = 0;
    Q.tail = 0;
    Q.names = (char *)malloc(max * length * sizeof(char));
    Q.times = (int *)malloc(max * sizeof(int));
    for(int i = 0; i < n; i++) {
        char pn[length];
        int t;
        scanf("%s%d", pn, &t);
        enqueue(&Q, max, length, pn, t);
    }
    int sum = 0;
    while(judge(&Q)) {
        char target[length];
        int rest = dequeue(&Q, max, length, target);
        if(rest > q) {
            enqueue(&Q, max, length, target, rest - q);
            sum += q;
        }
        else {
            sum += rest;
            printf("%s %d\n", target, sum);
        }
    }
    free(Q.names);
    free(Q.times);
}

int main() {
    int n = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    solve(n, q);
    return 0;
}