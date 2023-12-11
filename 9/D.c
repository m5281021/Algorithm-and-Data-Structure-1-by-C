#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *a, int l, int m, int r) {
    int L = m - l;
    int *left = (int *)malloc((L + 1) * sizeof(int));
    for(int i = 0; i < L; i++) {
        left[i] = a[i + l];
    }
    left[L] = INT_MAX;
    int R = r - m;
    int *right = (int *)malloc((R + 1) * sizeof(int));
    for(int i = 0; i < R; i++) {
        right[i] = a[i + m];
    }
    right[R] = INT_MAX;
    int j = 0;
    int k = 0;
    for(int i = l; i < r; i++) {
        if(left[j] <= right[k]) {
            a[i] = left[j++];
        }
        else {
            a[i] = right[k++];
        }
    }
    free(left);
    free(right);
}

void mergeSort(int *a, int l, int r) {
    if(l + 1 < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m, r);
        merge(a, l, m, r);
    }
}

void swap(int *a, int i, int j) {
    int k = a[i];
    a[i] = a[j];
    a[j] = k;
}

void upHeap(int *a, int i) {
    if(i == 0) return;
    int parent = (i - 1) / 2;
    if(a[parent] > a[i]) {
        swap(a, i, parent);
        upHeap(a, parent);
    }
}

void buildMaxHeap(int *a, int n) {
    int size = 0;
    while(size < n - 1) {
        upHeap(a, size);
        size++;
        swap(a, 0, size);
    }
}

void print(int *a, int n) {
    for(int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if(i != n - 1) printf(" ");
    }
    printf("\n");
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    mergeSort(a, 0, n);
    buildMaxHeap(a, n);
    print(a, n);
    free(a);
}

int main() {
    solve();
    return 0;
}