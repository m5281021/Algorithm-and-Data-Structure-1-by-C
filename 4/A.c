#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL

int linearSearch(int n, int* s, int v) {
    for(int i = 0; i < n; i++) {
        if(s[i] == v) return 1;
    }
    return 0;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *s = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &s[i]);
    }
    int q = 0;
    scanf("%d", &q);
    int sum = 0;
    for(int i = 0; i < q; i++) {
        int v = 0;
        scanf("%d", &v);
        if(linearSearch(n, s, v)) sum++;
    }
    printf("%d\n", sum);
    free(s);
}

int main() {
    solve();
    return 0;
}