#include <stdio.h>
#include <stdlib.h>

int fibonacci(int *a, int n) {
    if(a[n] != 0) return a[n];
    if(n == 0) return a[n] = 1;
    if(n == 1) return a[n] = 1;
    return a[n] = fibonacci(a, n - 1) + fibonacci(a, n - 2);
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc((n + 1) * sizeof(int));
    for(int i = 0; i < n + 1; i++) {
        a[i] = 0;
    }
    printf("%d\n", fibonacci(a, n));
    free(a);
}

int main() {
    solve();
    return 0;
}