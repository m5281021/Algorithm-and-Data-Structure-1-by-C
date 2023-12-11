#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(long *pri, int a, int b) {
    long c = pri[a];
    pri[a] = pri[b];
    pri[b] = c;
}

void UpHeap(long *pri, int i, int n) {
    if(i == 0) return;
    int p = (i - 1) / 2;
    if(pri[i] > pri[p]) {
        swap(pri, i, p);
        UpHeap(pri, p, n);
    }
}

void DownHeap(long *pri, int i, int n) {
    int l = i * 2 + 1;
    int r = i * 2 + 2;
    int largest = i;
    if(l < n && pri[l] > pri[largest]) largest = l;
    if(r < n && pri[r] > pri[largest]) largest = r;
    if(largest != i) {
        swap(pri, i, largest);
        DownHeap(pri, largest, n);
    }
}

void insert(long *pri, int k, int *cnt) {
    pri[(*cnt)++] = k;
    UpHeap(pri, *cnt - 1, *cnt);
}

long extractMax(long *pri, int *cnt) {
    long ans = pri[0];
    (*cnt)--;
    swap(pri, 0, *cnt);
    DownHeap(pri, 0, *cnt);
    return ans;
}

void solve() {
    const int max = 1000000;
    long *pri = (long *)malloc(max * sizeof(long));
    int cnt = 0;
    while(true) {
        char com[8];
        scanf("%s", com);
        if(com[0] == 'i') {
            long k = 0;
            scanf("%ld", &k);
            insert(pri, k, &cnt);
        }
        else if(com[1] == 'x') {
            printf("%ld\n", extractMax(pri, &cnt));
        }
        else if(com[0] == 'e') {
            break;
        }
    }
    free(pri);
}

int main() {
    solve();
    return 0;
}