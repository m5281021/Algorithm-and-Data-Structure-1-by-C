#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int GCD(int x, int y) {
    if(y > x) {
        int z = x;
        x = y;
        y = z;
    }
    while(x % y != 0) {
        int z = x % y;
        x = y;
        y = z;
    }
    return y;
}

int main() {
    int x = 0;
    int y = 0;
    scanf("%d%d", &x, &y);
    printf("%d\n", GCD(x, y));
    return 0;
}