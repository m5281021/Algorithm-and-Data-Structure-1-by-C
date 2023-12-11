#include <stdio.h>
#include <stdlib.h>

int ** createMap(int n) {
    int **map = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        map[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) {
            map[i][j] = 0;
        }
    }
    return map;
}

void deleteMap(int **map, int n) {
    for(int i = 0; i < n; i++) {
        free(map[i]);
    }
    free(map);
}

void in(int **map, int n) {
    for(int i = 0; i < n; i++) {
        int u = 0;
        int k = 0;
        scanf("%d%d", &u, &k);
        for(int j = 0; j < k; j++) {
            int v = 0;
            scanf("%d", &v);
            map[u - 1][v - 1] = 1;
        }
    }
}

void print(int **map, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%d", map[i][j]);
            if(j != n - 1) printf(" ");
        }
        printf("\n");
    }
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int **map = createMap(n);
    in(map, n);
    print(map, n);
    deleteMap(map, n);
}

int main() {
    solve();
    return 0;
}