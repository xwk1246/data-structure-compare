#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXHASH 10000000

struct hash_node {
    int key;
    int cnt;
    struct hash_node* next;
};

int hash65(int num) {
    long long sum;
    int i;
    char word[8];
    sprintf(word, "%d", num);
    int len = strlen(word);
    sum = 0;
    for (i = 0; i < len; i++) {
        sum = word[i] + sum * 65;
    }
    return (int)(sum % 10000000);
}
struct hash_node* hash_find(struct hash_node** hashTable, int target) {
    int hv = hash65(target);
    struct hash_node* current = hashTable[hv];
    current = hashTable[hv];
    while (current != NULL) {
        if (current->key == target)
            return current;
        current = current->next;
    }
    return NULL;
}
struct hash_node* hash_ll_insert(struct hash_node* node, int target) {
    struct hash_node* ptr = (struct hash_node*)malloc(sizeof(struct hash_node));
    ptr->key = target;
    if (!node) {
        ptr->next = NULL;
        ptr->cnt = 1;
    }
    else {
        ptr->next = node;
        ptr->cnt = node->cnt + 1;
    }
    return ptr;
}
struct hash_node** hash_insert(struct hash_node** hashTable, int target) {
    int hv;
    hv = hash65(target);
    if (!hashTable) {
        hashTable = malloc(sizeof(struct hash_node) * MAXHASH);
        memset(hashTable, 0, MAXHASH);
    }
    hashTable[hv] = hash_ll_insert(hashTable[hv], target);
    return hashTable;
}