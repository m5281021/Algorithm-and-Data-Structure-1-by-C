#include <stdio.h>
#include <stdlib.h>

int binarySearch(int n, int *s, int v) {
    int l = 0;
    int r = n;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        if(v >= s[m]) l = m;
        else r = m;
    }
    if(v == s[l]) return 1;
    else return 0;
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
        if(binarySearch(n, s, v)) sum++;
    }
    printf("%d\n", sum);
    free(s);
}

int main() {
    solve();
    return 0;
}