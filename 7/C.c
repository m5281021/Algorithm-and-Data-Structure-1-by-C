#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int parent;
    int left;
    int right;
} node;

void initialized(node *nodes, int n) {
    for(int i = 0; i < n; i++) {
        nodes[i].id = i;
        nodes[i].parent = -1;
        nodes[i].left = -1;
        nodes[i].right = -1;
    }
}

void getNodes(node *nodes, int n) {
    initialized(nodes, n);
    for(int i = 0; i < n; i++) {
        int id = 0;
        int left = 0;
        int right = 0;
        scanf("%d%d%d", &id, &left, &right);
        nodes[id].left = left;
        if(left != -1) nodes[left].parent = id;
        nodes[id].right = right;
        if(right != -1) nodes[right].parent = id;
    }
}

int getRoot(node *nodes) {
    int id = 0;
    while(nodes[id].parent != -1) {
        id = nodes[id].parent;
    }
    return id;
}

void preorder(node *nodes, int id) {
    printf(" %d", id);
    if(nodes[id].left != -1) preorder(nodes, nodes[id].left);
    if(nodes[id].right != -1) preorder(nodes, nodes[id].right);
}

void inorder(node* nodes, int id) {
    if(nodes[id].left != -1) inorder(nodes, nodes[id].left);
    printf(" %d", id);
    if(nodes[id].right != -1) inorder(nodes, nodes[id].right);
}

void postorder(node *nodes, int id) {
    if(nodes[id].left != -1) postorder(nodes, nodes[id].left);
    if(nodes[id].right != -1) postorder(nodes, nodes[id].right);
    printf(" %d", id);
}

void print(node *nodes) {
    int root = getRoot(nodes);
    printf("Preorder\n");
    preorder(nodes, root);
    printf("\n");
    printf("Inorder\n");
    inorder(nodes, root);
    printf("\n");
    printf("Postorder\n");
    postorder(nodes, root);
    printf("\n");
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    node *nodes = (node *)malloc(n * sizeof(node));
    getNodes(nodes, n);
    print(nodes);
    free(nodes);
}

int main() {
    solve();
    return 0;
}