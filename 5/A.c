#include <stdio.h>
#include <stdlib.h>

int calculate(int *a, int max, int n, int value) {
    if(value == 0) return 1;
    if(value < 0) return 0;
    if(max == n) return 0;
    if(calculate(a, max, n + 1, value) || calculate(a, max, n + 1, value - a[n])) return 1;
    else return 0;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int q = 0;
    scanf("%d", &q);
    for(int i = 0; i < q; i++) {
        int v = 0;
        scanf("%d", &v);
        if(calculate(a, n, 0, v)) printf("yes\n");
        else printf("no\n");
    }
    free(a);
}

int main() {
    solve();
    return 0;
}