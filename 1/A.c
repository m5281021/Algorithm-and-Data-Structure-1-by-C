#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *list, int n) {
    for(int i = 0; i < n; i++) {
        int v = list[i];
        int j = i - 1;
        while(j >= 0 && list[j] > v) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = v;
        for(int j = 0; j < n; j++) {
            printf("%d", list[j]);
            if(j != n - 1) printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int list[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    insertionSort(list, n);
    return 0;
}