#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define nullptr NULL

typedef struct {
    char *numbers;
    int x;
    int y;
    int step;
} puzzle;

typedef struct {
    puzzle *container;
    int size;
    int head;
    int tail;
} queue;

queue * createQueue() {
    const int max = 100000007;
    queue *q = (queue *)malloc(sizeof(queue));
    q->container = (puzzle *)malloc(max * sizeof(puzzle));
    q->size = max;
    q->head = 0;
    q->tail = 0;
    return q;
}

void swap(char *num, int x, int y, int nx, int ny) {
    char c = num[x * 3 + y];
    num[x * 3 + y] = num[nx * 3 + ny];
    num[nx * 3 + ny] = c;
}

void copy(puzzle *p, puzzle *q) {
    strcpy(p->numbers, q->numbers);
    p->x = q->x;
    p->y = q->y;
    p->step = q->step;
}

puzzle * createPuzzle(char *numbers, int x, int y, int step) {
    const int max = 10;
    puzzle *p = (puzzle *)malloc(sizeof(puzzle));
    p->numbers = (char *)malloc(max * sizeof(char));
    strcpy(p->numbers, numbers);
    p->x = x;
    p->y = y;
    p->step = step;
    return p;
}

void deletePuzzle(puzzle *p) {
    free(p->numbers);
    free(p);
}

void deleteQueue(queue *q) {
    free(q->container);
    free(q);
}

void enqueue(queue *q, puzzle *key) {
    const int max = 10;
    q->container[q->tail].numbers = (char *)malloc(max * sizeof(char));
    copy(&q->container[q->tail], key);
    q->tail++;
    q->tail %= q->size;
}

puzzle * dequeue(queue *q) {
    puzzle *p = createPuzzle(q->container[q->head].numbers, q->container[q->head].x, q->container[q->head].y, q->container[q->head].step);
    free(q->container[q->head].numbers);
    q->head++;
    q->head %= q->size;
    return p;
}

bool isEmpty(queue *q) {
    if(q->tail == q->head) return true;
    else return false;
}

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

int BFS(puzzle *p) {
    const int choiceMax = 4;
    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, -1, 0, 1};
    const int hashsize = 9991;
    const int val = 1;
    queue *q = createQueue();
    HashTable *ht = make_hash_table(hashsize);
    enqueue(q, p);
    insert_hash(ht, p->numbers, val);
    while(!isEmpty(q)) {
        puzzle *cur = dequeue(q);
        if(strcmp(cur->numbers, "123456789") == 0) {
            int step = cur->step;
            deletePuzzle(cur);
            deleteQueue(q);
            delete_hash_table(ht);
            return step;
        }
        int x = cur->x;
        int y = cur->y;
        for(int i = 0; i < choiceMax; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= 3 || ny >= 3) continue;
            puzzle *next = createPuzzle(cur->numbers, nx, ny, cur->step + 1);
            swap(next->numbers, x, y, nx, ny);
            bool err = false;
            search_hash(ht, next->numbers, &err);
            if(!err) {
                insert_hash(ht, next->numbers, val);
                enqueue(q, next);
            }
            deletePuzzle(next);
        }
        deletePuzzle(cur);
    }
    deleteQueue(q);
    delete_hash_table(ht);
    return -1;
}

void solve() {
    const int n = 9;
    char *numbers = (char *)malloc((n + 1) * sizeof(char));
    int x = -1;
    int y = -1;
    for(int i = 0; i < n; i++) {
        int num = 0;
        scanf("%d", &num);
        if(num == 0) {
            x = i / 3;
            y = i % 3;
            numbers[i] = '9';
        }
        else {
            numbers[i] = '0' + num;
        }
    }
    numbers[n] = '\0';
    puzzle *p = createPuzzle(numbers, x, y, 0);
    free(numbers);
    printf("%d\n", BFS(p));
    deletePuzzle(p);
}

int main() {
    solve();
    return 0;
}