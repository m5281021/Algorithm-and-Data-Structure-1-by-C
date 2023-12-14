#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *con;
    int n;
} component;

typedef struct {
    int size;
    int max;
    component *con;
} queue;

queue * createQueue() {
    const int max = 50;
    queue *q = (queue *)malloc(sizeof(queue));
    q->con = (component *)malloc(max * sizeof(component));
    q->size = 0;
    q->max = max;
    return q;
}

void deleteQueue(queue *q) {
    for(int i = 0; i < q->size; i++) {
        free(q->con[i].con);
    }
    free(q->con);
    free(q);
}

void copy(component *c, int n, char* s) {
    c->n = n;
    free(c->con);
    c->con = (char *)malloc((strlen(s) + 1) * sizeof(char));
    strcpy(c->con, s);
}

void swap(queue *q, int x, int y) {
    int n = q->con[x].n;
    int len = strlen(q->con[x].con);
    char *s = (char *)malloc((len + 1) * sizeof(char));
    strcpy(s, q->con[x].con);
    copy(&q->con[x], q->con[y].n, q->con[y].con);
    copy(&q->con[y], n, s);
    free(s);
}

void downHeap(queue *q, int cur) {
    int l = cur * 2 + 1;
    int r = cur * 2 + 2;
    int smallest = cur;
    if(l < q->size && q->con[l].n < q->con[smallest].n) smallest = l;
    if(r < q->size && q->con[r].n < q->con[smallest].n) smallest = r;
    if(smallest != cur) {
        swap(q, smallest, cur);
        downHeap(q, smallest);
    }
}

void upHeap(queue *q, int cur) {
    if(cur == 0) return;
    int parent = (cur - 1) / 2;
    if(q->con[cur].n < q->con[parent].n) {
        swap(q, parent, cur);
        upHeap(q, parent);
    }
}

void enqueue(queue *q, int n, char *s) {
    q->con[q->size].n = n;
    q->con[q->size].con = (char *)malloc((strlen(s) + 1) * sizeof(char));
    strcpy(q->con[q->size].con, s);
    q->size++;
    upHeap(q, q->size - 1);
}

component * dequeue(queue *q) {
    component *c = (component *)malloc(sizeof(component));
    c->con = (char *)malloc((strlen(q->con[0].con) + 1) * sizeof(char));
    strcpy(c->con, q->con[0].con);
    c->n = q->con[0].n;
    q->size--;
    if(q->size != 0) {
        free(q->con[0].con);
        q->con[0].n = q->con[q->size].n;
        q->con[0].con = (char *)malloc((strlen(q->con[q->size].con) + 1) * sizeof(char));
        strcpy(q->con[0].con, q->con[q->size].con);
    }
    free(q->con[q->size].con);
    downHeap(q, 0);
    return c;
}

int calculate(char *s) {
    const int max = 26;
    int len = strlen(s);
    int *count = (int *)malloc(max * sizeof(int));
    for(int i = 0; i < max; i++) {
        count[i] = 0;
    }
    for(int i = 0; i < len; i++) {
        count[s[i] - 'a']++;
    }
    queue *q = createQueue();
    for(int i = 0; i < max; i++) {
        if(count[i] == 0) continue;
        char *t = (char *)malloc(2 * sizeof(int));
        t[0] = i + 'a';
        t[1] = '\0';
        enqueue(q, count[i], t);
    }
    free(count);
    if(q->size == 1) {
        deleteQueue(q);
        return len;
    }
    int *huffman = (int *)malloc(max * sizeof(int));
    for(int i = 0; i < max; i++) {
        huffman[i] = 0;
    }
    while(q->size > 0) {
        component *left = dequeue(q);
        if(q->size == 0) {
            free(left);
            break;
        }
        component *right = dequeue(q);
        int l = strlen(left->con);
        int r = strlen(right->con);
        char *t = (char *)malloc((l + r + 1) * sizeof(char));
        for(int i = 0; i < l; i++) {
            huffman[left->con[i] - 'a']++;
            t[i] = left->con[i];
        }
        for(int i = 0; i < r; i++) {
            huffman[right->con[i] - 'a']++;
            t[i + l] = right->con[i];
        }
        t[l + r] = '\0';
        int pri = left->n + right->n;
        enqueue(q, pri, t);
        free(left);
        free(right);
        free(t);
    }
    deleteQueue(q);
    int sum = 0;
    for(int i = 0; i < len; i++) {
        sum += huffman[s[i] - 'a'];
    }
    free(huffman);
    return sum;
}

void solve() {
    const int length = 100010;
    char *s = (char *)malloc(length * sizeof(char));
    scanf("%s", s);
    printf("%d\n", calculate(s));
    free(s);
}

int main() {
    solve();
    return 0;
}