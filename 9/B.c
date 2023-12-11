#include <stdio.h>
#include <stdlib.h>

void in(int *heap, int n) {
    for(int i = 0; i < n; i++) {
        scanf("%d", &heap[i]);
    }
}

void swap(int *heap, int a, int b) {
    int c = heap[a];
    heap[a] = heap[b];
    heap[b] = c;
}

void maxHeapify(int *heap, int i, int n) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = i;
    if(l < n && heap[l] > heap[largest]) largest = l;
    if(r < n && heap[r] > heap[largest]) largest = r;
    if(largest != i) {
        swap(heap, largest, i);
        maxHeapify(heap, largest, n);
    }
}

void buildMaxHeap(int *heap, int n) {
    for(int i = (n + 1) / 2 - 1; i >= 0; i--) {
        maxHeapify(heap, i, n);
    }
}

void print(int *heap, int n) {
    for(int i = 0; i < n; i++) {
        printf(" %d", heap[i]);
    }
    printf("\n");
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *heap = (int *)malloc(n * sizeof(int));
    in(heap, n);
    buildMaxHeap(heap, n);
    print(heap, n);
    free(heap);
}

int main() {
    solve();
    return 0;
}