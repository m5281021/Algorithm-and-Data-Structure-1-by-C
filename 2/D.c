#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int insertionSort(int *list, int n, int g, int cnt) {
    for(int i = g; i < n; i++) {
        int v = list[i];
        int j = i - g;
        while(j >= 0 && list[j] > v) {
            list[j + g] = list[j];
            j -= g;
            cnt++;
        }
        list[j + g] = v;
    }
    return cnt;
}

int shellSort(int *list, int n, int m, int *G) {
    int cnt = 0;
    for(int i = 0; i < m; i++) {
        G[i] = (m - i) * (m - i);
        cnt = insertionSort(list, n, G[i], cnt);
    }
    return cnt;
}

void print(int n, int *list) {
    int m = sqrt(n);
    if(m > 100) m = 100;
    int G[m];
    int cnt = shellSort(list, n, m, G);
    printf("%d\n", m);
    for(int i = 0; i < m; i++) {
        printf("%d", G[i]);
        if(i != m - 1) printf(" ");
    }
    printf("\n");
    printf("%d\n", cnt);
    for(int i = 0; i < n; i++) {
        printf("%d\n", list[i]);
    }
}

int main() {
    int n = 0;
    scanf("%d", &n);
    int list[n];
    for(int i = 0; i < n; i++) {
        scanf("%d", &list[i]);
    }
    print(n, list);
    return 0;
}