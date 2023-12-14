#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void search(char **s, int h, int w, char **t, int r, int c) {
    const long b = 10000007;
    if(h < r || w < c) return;
    long pow = 1;
    long *sh = (long *)malloc(r * sizeof(long));
    long *th = (long *)malloc(r * sizeof(long));
    long *sbh = (long *)malloc(h * sizeof(long));
    for(int i = 0; i < h; i++) {
        if(i < r) {
            sh[i] = 0;
            th[i] = 0;
        }
        sbh[i] = 0;
    }
    for(int i = 0; i < c; i++) {
        pow *= b;
        for(int j = 0; j < h; j++) {
            if(j < r) {
                sh[j] = sh[j] * b + s[j][i];
                th[j] = th[j] * b + t[j][i];
            }
            sbh[j] = sbh[j] * b + s[j][i];
        }
    }
    for(int i = 0; i < h - r + 1; i++) {
        for(int j = 0; j < w - c + 1; j++) {
            bool flag = true;
            for(int k = 0; k < r; k++) {
                if(sh[k] != th[k]) flag = false;
                if(j + c < w)sh[k] = sh[k] * b + s[i + k][j + c] - s[i + k][j] * pow;
            }
            if(flag) printf("%d %d\n", i, j);
        }
        if(i + r < h) {
            for(int j = 0; j < r; j++) {
                sh[j] = sbh[1 + i + j];
            }
        }
    }
}

char ** createMatrix(int h, int w) {
    char **s = (char **)malloc(h * sizeof(char *));
    for(int i = 0; i < h; i++) {
        s[i] = (char *)malloc((w + 1) * sizeof(char));
        scanf("%s", s[i]);
    }
    return s;
}

void deleteMatrix(char **s, int h) {
    for(int i = 0; i < h; i++) {
        free(s[i]);
    }
    free(s);
}

void solve() {
    int h = 0;
    int w = 0;
    scanf("%d%d", &h, &w);
    char **s = createMatrix(h, w);
    int r = 0;
    int c = 0;
    scanf("%d%d", &r, &c);
    char **t = createMatrix(r, c);
    search(s, h, w, t, r, c);
    deleteMatrix(s, h);
    deleteMatrix(t, r);
}

int main() {
    solve();
    return 0;
}