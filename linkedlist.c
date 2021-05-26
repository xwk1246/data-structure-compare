#include <stdio.h>
#include <stdlib.h>
struct LinkedList {
    int data;
    struct LinkedList* next;
};

struct LinkedList* ll_insert(struct LinkedList* node, int target) {
    struct LinkedList* ptr;
    ptr = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    ptr->data = target;
    if (!node) {
        ptr->next = NULL;
        return ptr;
    }
    ptr->next = node;
    return ptr;
}

struct LinkedList* ll_find(struct LinkedList* node, int target) {
    struct LinkedList* current;
    current = node;
    while (current != NULL) {
        if (current->data == target)
            return current;
        current = current->next;
    }
    return NULL;
}

