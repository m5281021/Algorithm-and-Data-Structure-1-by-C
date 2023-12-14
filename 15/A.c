#include <stdio.h>
#include <stdlib.h>

int makeChange(int n) {
    const int max = 4;
    const int money[4] = {25, 10, 5, 1};
    int sum = 0;
    for(int i = 0; i < 4; i++) {
        sum += n / money[i];
        n %= money[i];
        if(n == 0) break;
    }
    return sum;
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    printf("%d\n", makeChange(n));
}

int main() {
    solve();
    return 0;
}