#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL

typedef struct Node {
    int n;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
} node;

node * create(int n, node *parent) {
    node *new = (node *)malloc(sizeof(node));
    new->n = n;
    new->parent = parent;
    new->left = nullptr;
    new->right = nullptr;
    return new;
}

node * search(node *n, int k) {
    node *cur = n;
    while(cur != nullptr) {
        if(cur->n == k) return cur;
        if(cur->n < k) {
            if(cur->right == nullptr) return cur;
            else cur = cur->right;
        }
        else {
            if(cur->left == nullptr) return cur;
            else cur = cur->left;
        }
    }
    return nullptr;
}

void insert(node *n, int k) {
    node *parent = search(n->left, k);
    if(parent == nullptr) {
        n->left = create(k, nullptr);
    }
    else if(parent->n < k) {
        parent->right = create(k, parent);
    }
    else {
        parent->left = create(k, parent);
    }
}

void find(node *n, int k) {
    node *cur = search(n->left, k);
    if(cur == nullptr) printf("no\n");
    if(cur->n == k) printf("yes\n");
    else printf("no\n");
}

node * getTarget(node *cur) {
    if(cur->right != nullptr) {
        cur = cur->right;
        while(cur->left != nullptr) cur = cur->left;
        return cur;
    }
    else {
        node *parent = cur->parent;
        while(parent != nullptr) {
            if(parent->right != cur) break;
            cur = parent;
            parent = parent->parent;
        }
        return parent;
    }
}

void delete(node *n, int k) {
    node *cur = search(n->left, k);
    if(cur == nullptr) return;
    if(cur->n != k) return;
    node *target = nullptr;
    if(cur->left == nullptr || cur->right == nullptr) {
        target = cur;
    }
    else {
        target = getTarget(cur);
    }
    node *next = nullptr;
    if(target->left != nullptr) next = target->left;
    else next = target->right;
    if(next != nullptr) next->parent = target->parent;
    if(target->parent == nullptr) n->left = next;
    else if(target->parent->right == target) target->parent->right = next;
    else target->parent->left = next;
    if(cur != target) cur->n = target->n;
    free(target);
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
    node *root = create(n, nullptr);
    for(int i = 0; i < n; i++) {
        char com[8];
        scanf("%s", com);
        if(com[0] == 'i') {
            int k = 0;
            scanf("%d", &k);
            insert(root, k);
        }
        else if(com[0] == 'f') {
            int k = 0;
            scanf("%d", &k);
            find(root, k);
        }
        else if(com[0] == 'd') {
            int k = 0;
            scanf("%d", &k);
            delete(root, k);
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