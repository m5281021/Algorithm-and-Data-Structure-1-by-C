#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int ** createDP(int n) {
    int **dp = (int **)malloc(n * sizeof(int *));
    for(int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    return dp;
}

void deleteDP(int **dp, int n) {
    for(int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);
}

int min(int a, int b) {
    if(a < b) return a;
    else return b;
}

int calculate(int *matrix, int n) {
    int **dp = createDP(n + 1);
    for(int i = 2; i <= n; i++) {
        for(int j = 1; j <= n - i + 1; j++) {
            int k = i + j - 1;
            dp[j][k] = INT_MAX;
            for(int l = j; l < k; l++) {
                dp[j][k] = min(dp[j][k], dp[j][l] + dp[l + 1][k] + matrix[j - 1] * matrix[l] * matrix[k]);
            }
        }
    }
    int answer = dp[1][n];
    deleteDP(dp, n + 1);
    return answer;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *matrix = (int *)malloc((n + 1) * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d%d", &matrix[i], &matrix[i + 1]);
    }
    printf("%d\n", calculate(matrix, n));
    free(matrix);
}

int main() {
    solve();
    return 0;
}