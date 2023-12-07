#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int max(int a, int b) {
    if(a > b) return a;
    else return b;
}

int min(int a, int b) {
    if(a < b) return a;
    else return b;
}

int maxProfit(int n) {
    int Max = INT_MIN;
    int Min = 0;
    scanf("%d", &Min);
    for(int i = 0; i < n - 1; i++) {
        int a = 0;
        scanf("%d", &a);
        Max = max(Max, a - Min);
        Min = min(Min, a);
    }
    return Max;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    printf("%d\n", maxProfit(n));
    return 0;
}