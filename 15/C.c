#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int begin;
    int end;
} event;

void copy(event *e, event *f) {
    e->begin = f->begin;
    e->end = f->end;
}

void merge(event *e, int l, int m, int r) {
    int L = m - l;
    event *left = (event *)malloc((L + 1) * sizeof(event));
    for(int i = 0; i < L; i++) {
        copy(&left[i], &e[l + i]);
    }
    left[L].end = INT_MAX;
    int R = r - m;
    event *right = (event *)malloc((R + 1) * sizeof(event));
    for(int i = 0; i < R; i++) {
        copy(&right[i], &e[m + i]);
    }
    right[R].end = INT_MAX;
    int j = 0;
    int k = 0;
    for(int i = l; i < r; i++) {
        if(left[j].end == right[k].end) {
            if(left[j].begin < right[k].end) {
                copy(&e[i], &left[j]);
                j++;
            }
            else {
                copy(&e[i], &right[k]);
                k++;
            }
        }
        else if(left[j].end < right[k].end) {
            copy(&e[i], &left[j]);
            j++;
        }
        else {
            copy(&e[i], &right[k]);
            k++;
        }
    }
    free(left);
    free(right);
}

void mergeSort(event *e, int l, int r) {
    if(l + 1 < r) {
        int m = (l + r) / 2;
        mergeSort(e, l, m);
        mergeSort(e, m, r);
        merge(e, l, m, r);
    }
}

int calculate(event *e, int n) {
    int sum = 0;
    int now = 0;
    mergeSort(e, 0, n);
    for(int i = 0; i < n; i++) {
        if(e[i].begin > now) {
            now = e[i].end;
            sum++;
        }
    }
    return sum;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    event *e = (event *)malloc(n * sizeof(event));
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &e[i].begin, &e[i].end);
    }
    printf("%d\n", calculate(e, n));
    free(e);
}

int main() {
    solve();
    return 0;
}