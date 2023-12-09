#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int l, int r) {
    int m = a[l];
    a[l] = a[r];
    a[r] = m;
}

int partition(int *a, int p, int r) {
    int x = a[r];
    int i = p - 1;
    for(int j = p; j < r; j++) {
        if(a[j] <= x) {
            i++;
            swap(a, i, j);
        }
    }
    swap(a, i + 1, r);
    return i + 1;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *a = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int j = partition(a, 0, n - 1);
    for(int i = 0; i < n; i++) {
        if(i == j) {
            printf("[%d]", a[i]);
        }
        else printf("%d", a[i]);
        if(i != n - 1) printf(" ");
    }
    printf("\n");
    free(a);
}

int main() {
    solve();
    return 0;
}