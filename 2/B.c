#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void swap(int *a, int *b) {
    int c = *a;
    *a = *b;
    *b = c;
}

int selectionSort(int n, int *list) {
    int cnt = 0;
    for(int i = 0; i < n - 1; i++) {
        int minj = i;
        for(int j = i + 1; j < n; j++) {
            if(list[j] < list[minj]) minj = j;
        }
        if(minj != i) {
            swap(&list[i], &list[minj]);
            cnt++;
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
    int cnt = selectionSort(n, list);
    for(int i = 0; i < n; i++) {
        printf("%d", list[i]);
        if(i != n - 1) printf(" ");
    }
    printf("\n");
    printf("%d\n", cnt);
    return 0;
}