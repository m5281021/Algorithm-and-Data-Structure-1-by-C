#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int bubbleSort(int n, int *list) {
    int cnt = 0;
    for(int i = 0; i < n - 1; i++) {
        for(int j = n - 1; j > i; j--) {
            if(list[j] < list[j - 1]) {
                swap(&list[j], &list[j - 1]);
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int list[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    int cnt = bubbleSort(n, list);
    for(int i = 0; i < n; i++) {
        printf("%d", list[i]);
        if(i != n - 1) printf(" ");
    }
    printf("\n");
    printf("%d\n", cnt);
    return 0;
}