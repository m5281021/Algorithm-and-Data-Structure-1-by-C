#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int n;
    char m;
} card;

void copy(card *a, int n, char m) {
    a->n = n;
    a->m = m;
}

void swap(card *a, int l, int r) {
    int n = a[l].n;
    char m = a[l].m;
    copy(&a[l], a[r].n, a[r].m);
    copy(&a[r], n, m);
}

int partition(card *a, int p, int r) {
    int x = a[r].n;
    int i = p - 1;
    for(int j = p; j < r; j++) {
        if(a[j].n <= x) {
            i++;
            swap(a, i, j);
        }
    }
    swap(a, i + 1, r);
    return i + 1;
}

void quickSort(card *a, int p, int r) {
    if(p < r) {
        int q = partition(a, p, r);
        quickSort(a, p, q - 1);
        quickSort(a, q + 1, r);
    }
}

void merge(card *a, int l, int m, int r) {
    int L = m - l;
    card *left = (card *)malloc((L + 1) * sizeof(card));
    for(int i = 0; i < L; i++) {
        copy(&left[i], a[i + l].n, a[i + l].m);
    }
    left[L].n = INT_MAX;
    int R = r - m;
    card *right = (card *)malloc((R + 1) * sizeof(card));
    for(int i = 0; i < R; i++) {
        copy(&right[i], a[i + m].n, a[i + m].m);
    }
    right[R].n = INT_MAX;
    int j = 0;
    int k = 0;
    for(int i = l; i < r; i++) {
        if(left[j].n <= right[k].n) {
            copy(&a[i], left[j].n, left[j].m);
            j++;
        }
        else {
            copy(&a[i], right[k].n, right[k].m);
            k++;
        }
    }
    free(left);
    free(right);
}

void mergeSort(card *a, int l, int r) {
    if(l + 1 < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m, r);
        merge(a, l, m, r);
    }
}

bool judge(card *a, card *b, int n) {
    for(int i = 0; i < n; i++) {
        if(a[i].n != b[i].n || a[i].m != b[i].m) return false;
    }
    return true;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    card *a = (card *)malloc(n * sizeof(card));
    card *b = (card *)malloc(n * sizeof(card));
    for(int i = 0; i < n; i++) {
        int num = 0;
        char mark;
        scanf(" %c%d", &mark, &num);
        copy(&a[i], num, mark);
        copy(&b[i], num, mark);
    }
    quickSort(a, 0, n - 1);
    mergeSort(b, 0, n);
    if(judge(a, b, n)) printf("Stable\n");
    else printf("Not stable\n");
    for(int i = 0; i < n; i++) {
        printf("%c %d\n", a[i].m, a[i].n);
    }
    free(a);
    free(b);
}

int main() {
    solve();
    return 0;
}