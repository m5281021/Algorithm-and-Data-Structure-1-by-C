#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} point;

void print(point *p) {
    printf("%0.8f %0.8f\n", p->x, p->y);
}

point * create(double x, double y) {
    point *p = (point *)malloc(sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

void calculate(point *l, point *r, int n, int max) {
    if(n == max) {
        print(l);
    }
    else {
        double x = r->x - l->x;
        double y = r->y - l->y;
        point *left = create(l->x + x / 3, l->y + y / 3);
        point *mid = create(l->x + x / 2 - y * sqrt(3) / 6, l->y + y / 2 + x * sqrt(3) / 6);
        point *right = create(r->x - x / 3, r->y - y / 3);
        calculate(l, left, n + 1, max);
        calculate(left, mid, n + 1, max);
        calculate(mid, right, n + 1, max);
        calculate(right, r, n + 1, max);
        free(left);
        free(mid);
        free(right);
    }
    if(n == 0) print(r);
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    point *left = create(0, 0);
    point *right = create(100, 0);
    calculate(left, right, 0, n);
    free(left);
    free(right);
}

int main() {
    solve();
    return 0;
}