#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int DT(int *p) {
    const int n = 16;
    const int d = 4;
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(p[i] == n) continue;
        sum += abs(i / d - (p[i] - 1) / d) + abs(i % d - (p[i] - 1) % d);
    }
    return sum;
}

void swap(int *p, int a, int b) {
    int c = p[a];
    p[a] = p[b];
    p[b] = c;
}

bool find(int *p, int pre, int depth, int limit, int s) {
    int dt = DT(p);
    if(dt == 0) return true;
    if(dt + depth > limit) return false;
    if(pre != 2 && s > 3) {
        swap(p, s, s - 4);
        s -= 4;
        if(find(p, 0, depth + 1, limit, s)) return true;
        s += 4;
        swap(p, s, s - 4);
    }
    if(pre != 3 && s % 4 > 0) {
        swap(p, s, s - 1);
        s -= 1;
        if(find(p, 1, depth + 1, limit, s)) return true;
        s += 1;
        swap(p, s, s - 1);
    }
    if(pre != 0 && s < 12) {
        swap(p, s, s + 4);
        s += 4;
        if(find(p, 2, depth + 1, limit, s)) return true;
        s -= 4;
        swap(p, s, s + 4);
    }
    if(pre != 1 && s % 4 < 3) {
        swap(p, s, s + 1);
        s += 1;
        if(find(p, 3, depth + 1, limit, s)) return true;
        s -= 1;
        swap(p, s, s + 1);
    }
    return false;
}

int search(int *p, int s) {
    int init = DT(p);
    for(int limit = init; limit < 100; limit++) {
        if(find(p, -1, 0, limit, s)) {
            return limit;
        }
    }
    return -1;
}

void solve() {
    const int n = 16;
    int *p = (int *)malloc(n * sizeof(int));
    int s = -1;
    for(int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        if(p[i] == 0) {
            p[i] = n;
            s = i;
        }
    }
    printf("%d\n", search(p, s));
    free(p);
}

int main() {
    solve();
    return 0;
}