#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Bst {
    int data;
    struct Bst* lchild;
    struct Bst* rchild;
};

struct Bst* bst_find(struct Bst* node, int target) {
    if (!node) {
        return NULL;
    }
    if (target < node->data)
        return bst_find(node->lchild, target);
    else if (target > node->data)
        return bst_find(node->rchild, target);
    else {
        return node;
    }
}

struct Bst* bst_insert(struct Bst* node, int target) {
    struct Bst* ptr;
    if (!node) {
        ptr = (struct Bst*)malloc(sizeof(struct Bst));
        ptr->data = target;
        ptr->lchild = NULL;
        ptr->rchild = NULL;
        return ptr;
    }
    if (target < node->data)
        node->lchild = bst_insert(node->lchild, target);
    else if (target > node->data)
        node->rchild = bst_insert(node->rchild, target);
    return node;
}
