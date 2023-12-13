#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void print(int *row, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(row[i] == j) printf("Q");
            else printf(".");
        }
        printf("\n");
    }
}

void search(int *row, bool *col, bool *dpos, bool *dneg, int y, int n) {
    if(y == n) {
        print(row, n);
        return;
    }
    if(row[y] != -1) {
        search(row, col, dpos, dneg, y + 1, n);
        return;
    }
    for(int x = 0; x < n; x++) {
        if(col[x] || dpos[x + y] || dneg[x - y + n - 1]) continue;
        row[y] = x;
        col[x] = true;
        dpos[x + y] = true;
        dneg[x - y + n - 1] = true;
        search(row, col, dpos, dneg, y + 1, n);
        row[y] = -1;
        col[x] = false;
        dpos[x + y] = false;
        dneg[x - y + n - 1] = false;
    }
}

void initialized(int *row, bool *col, bool *dpos, bool *dneg, int n) {
    for(int i = 0; i < 2 * n - 1; i++) {
        if(i < n) {
            row[i] = -1;
            col[i] = false;
        }
        dpos[i] = false;
        dneg[i] = false;
    }
}

void solve() {
    const int max = 8;
    int *row = (int *)malloc(max * sizeof(int));
    bool *col = (bool *)malloc(max * sizeof(bool));
    bool *dpos = (bool *)malloc((2 * max - 1) * sizeof(bool));
    bool *dneg = (bool *)malloc((2 * max - 1) * sizeof(bool));
    initialized(row, col, dpos, dneg, max);
    int n = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int x = 0;
        int y = 0;
        scanf("%d%d", &y, &x);
        row[y] = x;
        col[x] = true;
        dpos[x + y] = true;
        dneg[x - y + max - 1] = true;
    }
    search(row, col, dpos, dneg, 0, max);
    free(row);
    free(col);
    free(dpos);
    free(dneg);
}

int main() {
    solve();
    return 0;
}