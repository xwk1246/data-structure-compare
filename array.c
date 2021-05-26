#include <stdlib.h>
#include <stdio.h>
struct Arr {
    int data[10000000];
    int tail;
};
struct Arr* arr_insert(struct Arr* arr, int target) {
    struct Arr* ptr;
    if (!arr) {
        ptr = (struct Arr*)malloc(sizeof(struct Arr));
        ptr->data[0] = target;
        ptr->tail = 1;
        return ptr;
    }
    arr->data[arr->tail] = target;
    arr->tail++;
    return arr;
}
int* arr_traverse_find(struct Arr* arr, int target) {
    int i;
    for (i = 0; i < arr->tail; i++) {
        if (arr->data[i] == target) {
            return &arr->data[i];
            break;
        }
    }
    return NULL;
}
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;

}
int* arr_bs_find(struct Arr* arr, int target) {
    int front, back;
    int mid;
    int i;
    front = 0;
    back = arr->tail - 1;
    mid = (front + back) / 2;
    while (front <= back) {
        mid = (front + back) / 2;
        if (target > arr->data[mid]) {
            front = mid + 1;
        }
        else if (target < arr->data[mid]) {
            back = mid - 1;
        }
        else if (target == arr->data[mid]) {
            return &(arr->data[mid]);
        }
    }
    return NULL;
}
