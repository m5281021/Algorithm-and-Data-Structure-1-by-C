#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define nullptr NULL;

int prime(int n) {
    if(n < 1) return 0;
    for(int i = 2; i <= sqrt(n); i++) {
        if(n % i == 0) return 0;
    }
    return 1;
}

int countPrime(int *list, int n) {
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(prime(list[i])) sum++;
    }
    return sum;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int list[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    printf("%d\n", countPrime(list, n));
    return 0;
}