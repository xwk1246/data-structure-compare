struct Arr {
    int data[10000000];
    int tail;
};
struct Arr* arr_insert(struct Arr* arr, int target);
int* arr_traverse_find(struct Arr* arr, int target);
int* arr_bs_find(struct Arr* arr, int target);
int compare(const void* a, const void* b);
