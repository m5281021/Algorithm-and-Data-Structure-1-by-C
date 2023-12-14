#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void search(char *s, char *t) {
    const long b = 10000007;
    int n = strlen(s);
    int m = strlen(t);
    if(n < m) return;
    long pow = 1;
    long sh = 0;
    long th = 0;
    for(int i = 0; i < m; i++) {
        pow *= b;
        sh = sh * b + s[i];
        th = th * b + t[i];
    }
    for(int i = 0; i < n - m + 1; i++) {
        if(sh == th) printf("%d\n", i);
        if(1 + m < n) sh = sh * b + s[i + m] - s[i] * pow;
    }
}

void solve() {
    const int length = 1000010;
    char s[length];
    char t[length];
    scanf("%s%s", s, t);
    search(s, t);
}

int main() {
    solve();
    return 0;
}