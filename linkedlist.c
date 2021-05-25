#include <stdio.h>
#include <stdlib.h>
struct LinkedList {
    int data;
    struct LinkedList* next;
};

struct LinkedList* ll_insert(struct LinkedList* node, int target) {
    struct LinkedList* ptr;
    if (!node) {
        ptr = (struct LinkedList*)malloc(sizeof(struct LinkedList));
        ptr->data = target;
        ptr->next = NULL;
        return ptr;
    }
    node->next = ll_insert(node->next, target);
    return node;
}

struct LinkedList* ll_find(struct LinkedList* node, int target) {
    if (node->data == target)
        return node;
    return ll_find(node->next, target);
}

