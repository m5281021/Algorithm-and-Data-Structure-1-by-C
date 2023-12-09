#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL

struct Node {
    struct Node *pre;
    struct Node *next;
    int n;
};

typedef struct Node * node;

node create(int n) {
    node new = (node)malloc(sizeof(struct Node));
    new->n = n;
    return new;
}

node insert(int n, node pre, node next) {
    node new = create(n);
    pre->next = new;
    new->pre = pre;
    next->pre = new;
    new->next = next;
    return new;
}

void detach(node n) {
    n->pre->next = n->next;
    n->next->pre = n->pre;
    free(n);
}

void delete(int x, node root) {
    for(node n = root->next; n != root; n = n->next) {
        if(n->n == x) {
            detach(n);
            break;
        }
    }
}

void deleteFirst(node root) {
    node target = root->next;
    detach(target);
}

void deleteLast(node root) {
    node target = root->pre;
    detach(target);
}

void print(node root) {
    node current = root->next;
    root->pre->next = nullptr;
    free(root);
    while(current != nullptr) {
        node next = current->next;
        printf("%d", current->n);
        if(current->next != nullptr) printf(" ");
        free(current);
        current = next;
    }
    printf("\n");
}

void solve(int n) {
    const int length = 11 + 1;
    node root = create(0);
    root->next = root;
    root->pre = root;
    for(int i = 0; i < n; i++) {
        char command[length];
        scanf("%s", command);
        if(command[0] == 'i') {
            int v = 0;
            scanf("%d", &v);
            insert(v, root, root->next);
        }
        else if(command[6] == 'F') {
            deleteFirst(root);
        }
        else if(command[6] == 'L') {
            deleteLast(root);
        }
        else {
            int v = 0;
            scanf("%d", &v);
            delete(v, root);
        }
    }
    print(root);
}

int main() {
    int n = 0;
    scanf("%d", &n);
    solve(n);
    return 0;
}