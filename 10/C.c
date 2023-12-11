#include <stdio.h>
#include <stdlib.h>

int ** createDP(int ns, int nt) {
    int **dp = (int **)malloc(ns * sizeof(int *));
    for(int i = 0; i < ns; i++) {
        dp[i] = (int *)malloc(nt * sizeof(int));
        for(int j = 0; j < nt; j++) {
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

int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

int LCS(char *s, char *t, int ns, int nt) {
    int **dp = createDP(ns + 1, nt + 1);
    for(int i = 1; i <= ns; i++) {
        for(int j = 1; j <= nt; j++) {
            if(s[i - 1] == t[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
            else{
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int answer = dp[ns][nt];
    deleteDP(dp, ns + 1);
    return answer;
}

int length(char *s) {
    int sum = 0;
    while(s[sum] != '\0') {
        sum++;
    }
    return sum;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        char s[1010];
        char t[1010];
        scanf("%s%s", s, t);
        printf("%d\n", LCS(s, t, length(s), length(t)));
    }
}

int main() {
    solve();
    return 0;
}