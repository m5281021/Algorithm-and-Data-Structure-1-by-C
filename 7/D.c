#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int id;
    int parent;
    int left;
    int right;
} node;

void initialized(node *nodes, int n) {
    for(int i = 0; i < n; i++) {
        nodes[i].id = i + 1;
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }
}

int createNodes(node *nodes, int n, int cur, int left, int right, int *preorder, int *inorder) {
    if(cur == n) return n;
    int partition = -1;
    for(int i = left; i < right; i++) {
        if(preorder[cur] == inorder[i]) {
            partition = i;
            break;
        }
    }
    bool flag = false;
    int next = cur + 1;
    if(next == n) return n;
    for(int i = left; i < partition; i++) {
        if(preorder[next] == inorder[i]) {
            flag = true;
            break;
        }
    }
    if(flag) {
        nodes[preorder[cur]].left = preorder[next];
        nodes[preorder[next]].parent= preorder[cur];
        next = createNodes(nodes, n, next, left, partition, preorder, inorder);
    }
    if(next == n) return n;
    flag = false;
    for(int i = partition + 1; i < right; i++) {
        if(preorder[next] == inorder[i]) {
            flag = true;
            break;
        }
    }
    if(flag) {
        nodes[preorder[cur]].right = preorder[next];
        nodes[preorder[next]].parent = preorder[cur];
        next = createNodes(nodes, n, next, partition + 1, right, preorder, inorder);
    }
    return next;
}

void postorder(node *nodes, int id) {
    if(nodes[id].left != -1) {
        postorder(nodes, nodes[id].left);
        printf(" ");
    }
    if(nodes[id].right != -1) {
        postorder(nodes, nodes[id].right);
        printf(" ");
    }
    printf("%d", nodes[id].id);
}

void print(node *nodes, int n, int *preorder, int *inorder) {
    initialized(nodes, n);
    createNodes(nodes, n, 0, 0, n, preorder, inorder);
    postorder(nodes, preorder[0]);
    printf("\n");
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    int *preorder = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &preorder[i]);
        preorder[i]--;
    }
    int *inorder = (int *)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &inorder[i]);
        inorder[i]--;
    }
    node *nodes = (node *)malloc(n * sizeof(node));
    print(nodes, n, preorder, inorder);
    free(preorder);
    free(inorder);
    free(nodes);
}

int main() {
    solve();
    return 0;
}