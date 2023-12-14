#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void search(char *s, char *t) {
    int n = strlen(s);
    int m = strlen(t);
    for(int i = 0; i < n - m + 1; i++) {
        bool flag = true;
        for(int j = 0; j < m; j++) {
            if(s[i + j] != t[j]) {
                flag = false;
                break;
            }
        }
        if(flag) printf("%d\n", i);
    }
}

void solve() {
    const int length = 2000;
    char s[length];
    char t[length];
    scanf("%s%s", s, t);
    search(s, t);
}

int main() {
    solve();
    return 0;
}