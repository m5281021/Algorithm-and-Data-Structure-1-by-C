#include <stdio.h>
#include <stdlib.h>

void getNodes(int *heap, int n) {
    for(int i = 0; i < n; i++) {
        scanf("%d", &heap[i]);
    }
}

void print(int *heap, int n) {
    for(int i = 0; i < n; i++) {
        printf("node %d: key = %d, ", i + 1, heap[i]);
        if(i != 0) printf("parent key = %d, ", heap[(i - 1) / 2]);
        if(i * 2 + 1 < n) printf("left key = %d, ", heap[i * 2 + 1]);
        if(i * 2 + 2 < n) printf("right key = %d, ", heap[i * 2 + 2]);
        printf("\n");
    }
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *heap = (int *)malloc(n * sizeof(int));
    getNodes(heap, n);
    print(heap, n);
    free(heap);
}

int main() {
    solve();
    return 0;
}