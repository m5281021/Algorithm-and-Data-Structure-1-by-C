#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

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

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    bool *v = (bool *)malloc(n * sizeof(bool));
    int min = INT_MAX;
    int max = INT_MIN;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        b[i] = a[i];
        if(min > a[i]) min = a[i];
        if(max < a[i]) max = a[i];
        v[i] = false;
    }
    int *t = (int *)malloc((max + 1) * sizeof(int));
    mergeSort(b, 0, n);
    for(int i = 0; i < n; i++) {
        t[b[i]] = i;
    }
    int answer = 0;
    for(int i = 0; i < n; i++) {
        if(v[i]) continue;
        int cur = i;
        int sum = 0;
        int m = INT_MAX;
        int n = 0;
        while(true) {
            v[cur] = true;
            n++;
            int x = a[cur];
            if(x < m) m = x;
            sum += x;
            cur = t[x];
            if(v[cur]) break;
        }
        int l = sum + (n - 2) * m;
        int r = sum + m + min * (n + 1);
        if(l < r) answer += l;
        else answer += r;
    }
    printf("%d\n", answer);
    free(a);
    free(b);
    free(v);
    free(t);
}

int main() {
    solve();
    return 0;
}