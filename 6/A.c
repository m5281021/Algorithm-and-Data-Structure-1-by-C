#include <stdio.h>
#include <stdlib.h>

void countingSort(int *a, int *b, int n, int k) {
    int *c = (int *)malloc((k + 1) * sizeof(int));
    for(int i = 0; i < k + 1; i++) {
        c[i] = 0;
    }
    for(int i = 0; i < n; i++) {
        c[a[i]]++;
    }
    for(int i = 1; i < k + 1; i++) {
        c[i] += c[i - 1];
    }
    for(int i = n - 1; i >= 0; i--) {
        b[--c[a[i]]] = a[i];
    }
    free(c);
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int k = 0;
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        if(k < a[i]) k = a[i];
    }
    countingSort(a, b, n, k);
    for(int i = 0; i < n; i++) {
        printf("%d", b[i]);
        if(i != n - 1) printf(" ");
    }
    printf("\n");
    free(a);
    free(b);
}

int main() {
    solve();
    return 0;
}