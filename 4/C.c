#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define nullptr NULL

typedef struct cell {
    char *key;
    int value;
    struct cell *next;
} Cell;

typedef struct {
    int size;
    int count;
    Cell **table;
} HashTable;

Cell * make_cell(const char *key, int val, Cell *next) {
    Cell *cp = (Cell *)malloc(sizeof(Cell));
    if(cp != nullptr) {
        cp->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
        if(cp->key == nullptr) {
            free(cp);
            return nullptr;
        }
        strcpy(cp->key, key);
        cp->value = val;
        cp->next = next;
    }
    return cp;
}

void delete_cell(Cell *cp) {
    while(cp != nullptr) {
        Cell *xs = cp->next;
        free(cp->key);
        free(cp);
        cp = xs;
    } 
}

HashTable * make_hash_table(int size) {
    HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
    if(ht != nullptr) {
        ht->size = size;
        ht->table = (Cell **)malloc(size * sizeof(Cell *));
        if(ht->table == nullptr) {
            free(ht);
            return nullptr;
        }
        for(int i = 0; i < size; i++) {
            ht->table[i] = nullptr;
        }
    }
    return ht;
}

void delete_hash_table(HashTable *ht) {
    for(int i = 0; i < ht->size; i++) {
        delete_cell(ht->table[i]);
    }
    free(ht);
}

int hash_func(HashTable *ht, const char *key) {
    unsigned int value = 0;
    for(; *key != '\0'; key++) {
        value = (value << 3) + *key;
    }
    return value % ht->size;
}

Cell * search_cell(HashTable *ht, const char *key, int hval) {
    Cell *cp = ht->table[hval];
    for(; cp != nullptr; cp = cp->next) {
        if(strcmp(cp->key, key) == 0) return cp;
    }
    return nullptr;
}

int search_hash(HashTable *ht, const char *key, bool *err) {
    Cell *cp = search_cell(ht, key, hash_func(ht, key));
    if(cp != nullptr) {
        *err = true;
        return cp->value;
    }
    *err = false;
    return 0;
}

bool insert_hash(HashTable *ht, const char *key, int val) {
    int hval = hash_func(ht, key);
    Cell *cp = search_cell(ht, key, hval);
    if(cp == nullptr) {
        ht->table[hval] = make_cell(key, val, ht->table[hval]);
        ht->count++;
        return true;
    }
    else {
        cp->value = val;
        return false;
    }
}

bool delete_hash(HashTable *ht, const char *key) {
    int hval = hash_func(ht, key);
    Cell *cp = ht->table[hval];
    if(cp != nullptr) {
        if(strcmp(cp->key, key) == 0) {
            ht->table[hval] = cp->next;
            ht->count--;
            free(cp->key);
            free(cp);
            return true;
        }
        else {
            for(; cp->next != nullptr; cp = cp->next) {
                if(strcmp(cp->next->key, key) == 0) {
                    Cell *del = cp->next;
                    cp->next = cp->next->next;
                    ht->count--;
                    free(del->key);
                    free(del);
                    return true;
                }
            }
        }
    }
    return false;
}

void foreach_hash(void (*func)(const char *, int), HashTable *ht) {
    for(int i = 0; i < ht->size; i++) {
        for(Cell *cp = ht->table[i]; cp != nullptr; cp = cp->next) {
            func(cp->key, cp->value);
        }
    }
}

bool is_empty_hash(HashTable *ht) {
    if(ht->count == 0) return true;
    else return false;
}

int length_hash(HashTable *ht) {
    return ht->count;
}

void clear_hash(HashTable *ht) {
    ht->count = 0;
    for(int i = 0; i < ht->size; i++) {
        delete_cell(ht->table[i]);
        ht->table[i] = nullptr;
    }
}

void solve(int n) {
    HashTable *ht = make_hash_table(9991);
    bool err;
    for(int i = 0; i < n; i++) {
        char com[8];
        char tar[13];
        scanf("%s%s", com, tar);
        if(com[0] == 'i') {
            search_hash(ht, tar, &err);
            if(!err) insert_hash(ht, tar, 1);
        }
        else {
            search_hash(ht, tar, &err);
            if(err) printf("yes\n");
            else printf("no\n");
        }
    }
    delete_hash_table(ht);
}

int main() {
    int n = 0;
    scanf("%d", &n);
    solve(n);
    return 0;
}