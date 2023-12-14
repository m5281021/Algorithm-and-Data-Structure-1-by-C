#include <stdio.h>
#include <stdlib.h>
#include <float.h>

typedef struct {
    int v;
    int w;
    double unit;
} item;

void copy(item *a, item *b) {
    a->v = b->v;
    a->w = b->w;
    a->unit = b->unit;
}

void merge(item *items, int l, int m, int r) {
    int L = m - l;
    item *left = (item *)malloc((L + 1) * sizeof(item));
    for(int i = 0; i < L; i++) {
        copy(&left[i], &items[l + i]);
    }
    left[L].unit = DBL_MIN;
    int R = r - m;
    item *right = (item *)malloc((R + 1) * sizeof(item));
    for(int i = 0; i < R; i++) {
        copy(&right[i], &items[m + i]);
    }
    right[R].unit = DBL_MIN;
    int j = 0;
    int k = 0;
    for(int i = l; i < r; i++) {
        if(left[j].unit > right[k].unit) {
            copy(&items[i], &left[j]);
            j++;
        }
        else {
            copy(&items[i], &right[k]);
            k++;
        }
    }
    free(left);
    free(right);
}

void mergeSort(item *items, int l, int r) {
    if(l + 1 < r) {
        int m = (l + r) / 2;
        mergeSort(items, l, m);
        mergeSort(items, m, r);
        merge(items, l, m, r);
    }
}

double calculate(item *items, int n, int w) {
    mergeSort(items, 0, n);
    double sum = 0;
    for(int i = 0; i < n; i++) {
        if(items[i].w < w) {
            sum += items[i].v;
            w -= items[i].w;
        }
        else {
            sum += (double)items[i].v * w / items[i].w;
            break;
        }
    }
    return sum;
}

void solve() {
    int n = 0;
    int w = 0;
    scanf("%d%d", &n, &w);
    item *items = (item *)malloc(n * sizeof(item));
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &items[i].v, &items[i].w);
        items[i].unit = (double)items[i].v / items[i].w;
    }
    printf("%0.8lf\n", calculate(items, n, w));
    free(items);
}

int main() {
    solve();
    return 0;
}