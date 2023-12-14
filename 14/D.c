#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

/* 
This code used suffix array.
*/

// comparing (rank[i], rank[i + k]) with (rank[j], rank [j + k]).
bool compare_sa(int *rank, int i, int j, int k, int n) {
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    else {
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }
}

// mergesort using compare_sa.
void merge(int *sa, int *rank, int k, int n, int l, int m, int r) {
    int L = m - l;
    int *left = (int *)malloc((L + 1) * sizeof(int));
    for(int i = 0; i < L; i++) {
        left[i] = sa[l + i];
    }
    left[L] = INT_MAX;
    int R = r - m;
    int *right = (int *)malloc((R + 1) * sizeof(int));
    for(int i = 0; i < R; i++) {
        right[i] = sa[m + i];
    }
    right[R] = INT_MAX;
    int x = 0;
    int y = 0;
    for(int i = l; i < r; i++) {
        if(right[y] > n || (left[x] <= n && compare_sa(rank, left[x], right[y], k, n))) {
            sa[i] = left[x++];
        }
        else {
            sa[i] = right[y++];
        }
    }
    free(left);
    free(right);
}

void mergeSort(int *sa, int *rank, int k, int n, int l, int r) {
    if(l + 1 < r) {
        int m = (l + r) / 2;
        mergeSort(sa, rank, k, n, l, m);
        mergeSort(sa, rank, k, n, m, r);
        merge(sa, rank, k, n, l, m, r);
    }
}

// creating suffix array of string s.
void construct_sa(char *s, int *sa, int *rank) {
    int n = strlen(s);
    /*
    First, sa[i] contains one character.
    The rank is ASCII code.
    */
    for(int i = 0; i <= n; i++) {
        sa[i] = i;
        rank[i] = i < n ? s[i] : -1;
    }
    /*
    Second, we sort sa which has sa[i] containing k characters.
    After that, we create sa[i] containing 2 * k characters.
    */
    int *tmp = (int *)malloc((n + 1) * sizeof(int));
    for(int k = 1; k <= n; k *= 2) {
        mergeSort(sa, rank, k, n, 0, n + 1);
        tmp[sa[0]] = 0;
        for(int i = 1; i <= n; i++) {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(rank, sa[i - 1], sa[i], k, n) ? 1 : 0);
        }
        for(int i = 0; i <= n; i++) {
            rank[i] = tmp[i];
        }
    }
    free(tmp);
}

int contain(char *s, int *sa, char *t) {
    int len = strlen(t);
    int l = 0;
    int r = strlen(s);
    while(l + 1 < r) {
        int m = (l + r) / 2;
        // comparing s beginning from sa[c] with t.
        if(strncmp(&s[sa[m]], t, len) < 0) l = m;
        else r = m;
    }
    return strncmp(&s[sa[r]], t, len) == 0 ? 1 : 0;
}

void answer(char *s, int *sa) {
    int q = 0;
    scanf("%d", &q);
    const int length = 1010;
    for(int i = 0; i < q; i++) {
        char *t = (char *)malloc(length * sizeof(char));
        scanf("%s", t);
        printf("%d\n", contain(s, sa, t));
        free(t);
    }
}

void solve() {
    const int length = 1000020;
    char *s = (char *)malloc(length * sizeof(char));
    scanf("%s", s);
    int n = strlen(s);
    int *sa = (int *)malloc((n + 1) * sizeof(int));
    int *rank = (int *)malloc((n + 1) * sizeof(int));
    construct_sa(s, sa, rank);
    free(rank);
    answer(s, sa);
    free(s);
    free(sa);
}

int main() {
    solve();
    return 0;
}