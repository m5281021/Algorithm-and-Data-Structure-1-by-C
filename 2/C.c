#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct card {
    int N;
    char M;
};

typedef struct card Card;

void make(Card *a, int n, char m) {
    a->N = n;
    a->M = m;
}

void swap(Card *a, Card *b) {
    Card c;
    make(&c, a->N, a->M);
    make(a, b->N, b->M);
    make(b, c.N, c.M);
}

int equals(Card *a, Card*b) {
    if(a->N == b->N && a->M == b->M) return 1;
    else return 0;
}

void bubbleSort(int n, Card *set) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = n - 1; j > i; j--) {
            if(set[j].N < set[j - 1].N) {
                swap(&set[j], &set[j - 1]);
            }
        }
    }
}

void selectionSort(int n, Card *set) {
    for(int i = 0; i < n - 1; i++) {
        int minj = i;
        for(int j = i + 1; j < n; j++) {
            if(set[j].N < set[minj].N) minj = j;
        }
        if(minj != i) {
            swap(&set[i], &set[minj]);
        }
    }
}

void judge(int n, Card *base, Card *target) {
    for(int i = 0; i < n; i++) {
        if(equals(&base[i], &target[i])) continue;
        else {
            printf("Not stable\n");
            return;
        }
    }
    printf("Stable\n");
}

void print(int n, Card *base, Card *target) {
    for(int i = 0; i < n; i++) {
        printf("%c%d", target[i].M, target[i].N);
        if(i != n - 1) printf(" ");
    }
    printf("\n");
    judge(n, base, target);
}

int main() {
    int n = 0;
    scanf("%d", &n);
    Card cards1[n];
    Card cards2[n];
    for(int i = 0; i < n; i++) {
        int n;
        char m;
        scanf(" %c%d", &m, &n);
        make(&cards1[i], n, m);
        make(&cards2[i], n, m);
    }
    bubbleSort(n, cards1);
    selectionSort(n, cards2);
    print(n, cards1, cards1);
    print(n, cards1, cards2);
}