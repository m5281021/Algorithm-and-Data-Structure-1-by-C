#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void merge(int *a, int l, int m, int r, long *cnt) {
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
            *cnt += L - j;
        }
    }
    free(left);
    free(right);
}

void mergeSort(int *a, int l, int r, long *cnt) {
    if(l + 1 < r) {
        int m = (l + r) / 2;
        mergeSort(a, l, m, cnt);
        mergeSort(a, m, r, cnt);
        merge(a, l, m, r, cnt);
    }
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    long cnt = 0;
    mergeSort(a, 0, n, &cnt);
    printf("%ld\n", cnt);
    free(a);
}

int main() {
    solve();
    return 0;
}