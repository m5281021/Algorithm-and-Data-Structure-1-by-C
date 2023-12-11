#include <stdio.h>
#include <stdlib.h>
#include <float.h>

double ** createDP(int n) {
    double **dp = (double **)malloc(n * sizeof(double *));
    for(int i = 0; i < n; i++) {
        dp[i] = (double *)malloc(n * sizeof(double));
        for(int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    return dp;
}

void deleteDP(double **dp, int n) {
    for(int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
}

double min(double a, double b) {
    if(a < b) return a;
    else return b;
}

double calculate(double **dp, double *p, double *tp, double *tq, int l, int r) {
    if(dp[l][r] != 0) return dp[l][r];
    if(l == r) return dp[l][r] = 0;
    dp[l][r] = DBL_MAX;
    double total = tq[r] - tq[l - 1] + tp[r] - tp[l];
    for(int i = l + 1; i <= r; i++) {
        double left = tq[i - 1] - tq[l - 1] + tp[i - 1] - tp[l];
        double right = total - left - p[i];
        double under = (calculate(dp, p, tp, tq, l, i - 1) + 1) * left / total + (calculate(dp, p, tp, tq, i, r) + 1) * right / total;
        dp[l][r] = min(dp[l][r], under);
    }
    return dp[l][r];
}

void in(double *a, double *ta, int n, int j) {
    for(int i = 0; i < n; i++) {
        if(i < j) {
            a[i] = 0;
            ta[i] = 0;
        }
        else {
            scanf("%lf", &a[i]);
            ta[i] = ta[i - 1] + a[i];
        }
    }
}

int solve() {
    int n = 0;
    scanf("%d", &n);
    double **dp = createDP(n + 2);
    double *p = (double *)malloc((n + 2) * sizeof(double));
    double *tp = (double *)malloc((n + 2) * sizeof(double));
    in(p, tp, n + 2, 2);
    double *q = (double *)malloc((n + 2) * sizeof(double));
    double *tq = (double *)malloc((n + 2) * sizeof(double));
    in(q, tq, n + 2, 1);
    printf("%0.8f\n", 1 + calculate(dp, p, tp, tq, 1, n + 1));
    deleteDP(dp, n + 2);
    free(p);
    free(tp);
    free(q);
    free(tq);
}

int main() {
    solve();
    return 0;
}