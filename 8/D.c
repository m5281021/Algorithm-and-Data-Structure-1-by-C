#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define nullptr NULL

typedef struct Node {
    int n;
    int pri;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} node;

node * create(int n, int pri) {
    node *new = (node *)malloc(sizeof(node));
    new->n = n;
    new->pri = pri;
    new->parent = nullptr;
    new->left = nullptr;
    new->right = nullptr;
    return new;
}

node * rightRotate(node *n) {
    node *m = n->left;
    n->left = m->right;
    m->right = n;
    m->parent = n->parent;
    n->parent = m;
    return m;
}

node * leftRotate(node *n) {
    node *m = n->right;
    n->right = m->left;
    m->left = n;
    m->parent = n->parent;
    n->parent = m;
    return m;
}

node * insert(node *n, int k, int pri) {
    if(n == nullptr) return create(k, pri);
    if(k == n->n) return n;
    if(k < n->n) {
        n->left = insert(n->left, k, pri);
        n->left->parent = n;
        if(n->pri < n->left->pri) n = rightRotate(n);
    }
    else {
        n->right = insert(n->right, k, pri);
        n->right->parent = n;
        if(n->pri < n->right->pri) n = leftRotate(n);
    }
    return n;
}

void find(node *n, int k) {
    node *cur = n;
    while(cur != nullptr) {
        if(cur->n == k) {
            printf("yes\n");
            return;
        }
        if(cur->n < k) cur = cur->right;
        else cur = cur->left;
    }
    printf("no\n");
}

node * delete(node *n, int k);

node * _delete(node *n, int k) {
    if(n->left == nullptr && n->right == nullptr) {
        free(n);
        return nullptr;
    }
    else if(n->left == nullptr) n = leftRotate(n);
    else if(n->right == nullptr) n = rightRotate(n);
    else {
        if(n->left->pri > n->right->pri) n = rightRotate(n);
        else n = leftRotate(n);
    }
    return delete(n, k);
}

node * delete(node *n, int k) {
    if(n == nullptr) return nullptr;
    if(k < n->n) {
        n->left = delete(n->left, k);
    }
    else if(k > n->n) {
        n->right = delete(n->right, k);
    }
    else return _delete(n, k);
    return n;
}

void preorder(node *n) {
    printf(" %d", n->n);
    if(n->left != nullptr) preorder(n->left);
    if(n->right != nullptr) preorder(n->right);
}

void inorder(node *n) {
    if(n->left != nullptr) inorder(n->left);
    printf(" %d", n->n);
    if(n->right != nullptr) inorder(n->right);
}

void print(node *n) {
    inorder(n->left);
    printf("\n");
    preorder(n->left);
    printf("\n");
}

void release(node *n) {
    if(n->left != nullptr) release(n->left);
    if(n->right != nullptr) release(n->right);
    free(n);
}

void solve() {
    int n = 0;
    scanf("%d", &n);
    node *root = create(n, INT_MAX);
    for(int i = 0; i < n; i++) {
        char com[8];
        scanf("%s", com);
        if(com[0] == 'i') {
            int k = 0;
            int pri = 0;
            scanf("%d%d", &k, &pri);
            root->left = insert(root->left, k, pri);
        }
        else if(com[0] == 'f') {
            int k = 0;
            scanf("%d", &k);
            find(root->left, k);
        }
        else if(com[0] == 'd') {
            int k = 0;
            scanf("%d", &k);
            root->left = delete(root->left, k);
        }
        else if(com[0] == 'p') {
            print(root);
        }
    }
    release(root);
}

int main() {
    solve();
    return 0;
}