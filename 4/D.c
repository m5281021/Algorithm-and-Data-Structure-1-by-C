#include <stdio.h>
#include <stdlib.h>

int check(int p, int n, int *weight, int k) {
    int i = 0;
    for(int j = 0; j < k; j++) {
        int sum = 0;
        while(sum + weight[i] <= p) {
            sum += weight[i];
            i++;
            if(i == n) return n;
        }
    }
    return i;
}

int search(int min, int max, int n, int *weight, int k) {
    int l = min;
    int r = max;
    while(l + 1 < r) {
        int m = (l + r) / 2;
        int v = check(m, n, weight, k);
        if(v >= n) r = m;
        else l = m;
    }
    return r;
}

void solve() {
    const int min = 0;
    const int max = 1000000000;
    int n = 0;
    int k = 0;
    scanf("%d%d", &n, &k);
    int *weight = (int *)malloc(n * sizeof(n));
    for(int i = 0; i < n; i++) {
        scanf("%d", &weight[i]);
    }
    printf("%d\n", search(min, max, n, weight, k));
    free(weight);
}

int main() {
    solve();
    return 0;
}