# 資料結構之效率比較

## 資工一 409410034 蕭文愷

**Github 連結:** <https://github.com/xwk1246/data-structure-compare>

## 系統環境

**OS:** Manjaro 21.0.2 Ornara

**Kernel:** x86_64 Linux 5.10.30-1-MANJARO

**CPU:** Intel Core i7-4790K @ 8x 4.4GHz

**GPU:** GeForce GTX 1070

**RAM:** 16GB DDR3 1866MHz

## 資料集生成方法

使用 rand 函式生成範圍內整數並寫入檔案

### insert data set

產生指定數量整數，每筆數字是唯一，用來insert進資料結構

```c
int genInsertDataSet(int dataSize) {
    int i;
    int* exist = (int*)malloc(sizeof(int) * MAXDATALEN);　//建立重複檢查表
    memset(exist, 0, MAXDATALEN);　//將檢查表全部值初始化為0
    FILE* fp = fopen("./insertdataset.txt", "w");　//以write模式開啟檔案，如不存在則新增
    for (i = 0; i < dataSize; i++) {　//重複dataSize次
        int tmp;
        do {
            tmp = rand() % 10000000;　//僅隨機取10,000,000以內整數
        }
        while (exist[tmp]);　//當數字已經出現時再執行一次，直到沒出現過
        fprintf(fp, "%d\n", tmp);　//寫入檔案並換行
        exist[tmp] = 1;　//紀錄為已出現過
    }
    free(exist);　//清除空間
    fclose(fp);　//關檔
}
```

### query data set

產生指定數量整數，用來查詢資料結構是否存在該值

```c
int genQueryDataSet(int datasize) {
    int i;
    int tmp;
    FILE* fp = fopen("./querydataset.txt", "w");　//以write模式開啟檔案，如不存在則新增
    for (i = 0; i < datasize; i++) {　//重複dataSize次
        tmp = rand() % MAXDATALEN; //僅隨機取10,000,000以內整數
        fprintf(fp, "%d\n", tmp); //寫入檔案並換行
    }
    fclose(fp); //關檔
}
```



## 資料結構實做

### Linked list

每個node儲存資料並儲存指向下一個或前一個node位置的指標

#### insert

將目標insert進Linked list前方

```c
struct LinkedList* ll_insert(struct LinkedList* node, int target) {
    struct LinkedList* ptr;
    ptr = (struct LinkedList*)malloc(sizeof(struct LinkedList));　//配置空間給節點
    ptr->data = target;　//將資料存入節點
    if (!node) {　//如果傳入資料結構為NULL
        ptr->next = NULL;　//將新增的節點下個節點指向NULL
        return ptr;　//回傳新建的指標，為linked list最前方節點
    }
    ptr->next = node;　//將新建的節點下個位置指向資料結構目前最前方節點
    return ptr;　//回傳新建的指標，為linked list最前方節點
}
```

#### find

用依序尋訪的方式來尋找

```c
struct LinkedList* ll_find(struct LinkedList* node, int target) {
    struct LinkedList* current;
    current = node; //當前節點
    while (current != NULL) {　//當節點存在
        if (current->data == target)　//當節點資料等於目標
            return current;　//回傳符合的節點
        current = current->next;　//不符合時將當前節點設為下一個節點位置
    }
    return NULL;　//到linked list結束時仍未找到則回傳NULL
}
```

### Array

#### insert

將目標insert進該array中

```c
struct Arr* arr_insert(struct Arr* arr, int target) {
    struct Arr* ptr;
    if (!arr) { //當array不存在時
        ptr = (struct Arr*)malloc(sizeof(struct Arr));　//分配空間給array
        ptr->data[0] = target;　//將數字放進第0個位置
        ptr->tail = 1;　//儲存下一筆資料該儲存的位置
        return ptr;　//回傳新建的array struct
    }
    arr->data[arr->tail] = target; //array存在時則在最後面新增值
    arr->tail++;　//把下個開始位置加一
    return arr;　//回傳陣列指標
}
```

#### find with binary search

用二元搜尋法在array中尋找值

```c
int* arr_bs_find(struct Arr* arr, int target) {
    int front, back;
    int mid;
    int i;
    front = 0;　//前方設為array開頭
    back = arr->tail - 1; //將後方設為陣列最後一個有存資料的位置
    mid = (front + back) / 2;　//中間等於前後相加除二
    while (front <= back) {　//當前後位置未交換時
        mid = (front + back) / 2;　//取得中間值
        if (target > arr->data[mid]) {　//當值比中間大時
            front = mid + 1; //前等於中間
        }
        else if (target < arr->data[mid]) { //當值比中間小時
            back = mid - 1; //後等於中間
        }
        else if (target == arr->data[mid]) {　//當值等於中間時
            return &(arr->data[mid]);　//表示找到並回傳
        }
    }
    return NULL;　//當前後碰撞仍未找到則回傳NULL
}
```

#### find with traversal

用尋訪的方式來比對值並找到

```c
int* arr_traverse_find(struct Arr* arr, int target) {
    int i;
    for (i = 0; i < arr->tail; i++) {　//從頭到array結尾訪問
        if (arr->data[i] == target) {　//當找到時
            return &arr->data[i]; //回傳
            break;
        }
    }
    return NULL;　//當尋訪完仍未找到，回傳NULL
}
```

### Binary Search Tree

#### insert

將目標insert進該資料結構中

```c
struct Bst* bst_insert(struct Bst* node, int target) {
    struct Bst* ptr;
    if (!node) { //當bst不存在
        ptr = (struct Bst*)malloc(sizeof(struct Bst));　//分配新空間
        ptr->data = target; //將值儲存進節點
        ptr->lchild = NULL; //左child等於NULL
        ptr->rchild = NULL; //右chile等於NULL
        return ptr; //回傳建立的bst
    }
    if (target < node->data)　//當值小於當前node值
        node->lchild = bst_insert(node->lchild, target); //遞迴重複執行
    else if (target > node->data)　//當值大於當前node值
        node->rchild = bst_insert(node->rchild, target);　//遞迴重複執行
    return node;　//回傳root
}
```

#### find

```c
struct Bst* bst_find(struct Bst* node, int target) {
    if (!node) { //當遞迴到樹末端
        return NULL;　//回傳NULL
    }
    if (target < node->data)　//當值小於當前node值
        return bst_find(node->lchild, target);　//遞迴重複執行
    else if (target > node->data)　//當值大於當前node值
        return bst_find(node->rchild, target);　//遞迴重複執行
    else {
        return node;　//回傳找到的node
    }
}
```

### Hash

#### hash function

以原始數字透過hash function產生一組新數

```c
int hash65(int num) {
    long long sum;
    int i;
    char word[8];
    sprintf(word, "%d", num); //將整數轉為字串
    int len = strlen(word);　//取得位數
    sum = 0;　//初始總和為0
    for (i = 0; i < len; i++) {
        sum = word[i] + sum * 65;　//sum為第n位字符編碼*65^n-1相加
    }
    return (int)(sum % 10000000);　回傳保證範圍為10,000,000以內
}
```

#### insert

將目標insert進該資料結構中

```c
struct hash_node** hash_insert(struct hash_node** hashTable, int target) {
    int hv;
    hv = hash65(target); //將值轉為hash後value
    if (!hashTable) { //當hash table不存在
        hashTable = malloc(sizeof(struct hash_node) * MAXHASH);　//配置記憶體空間
        memset(hashTable, 0, MAXHASH);　//初始匯為0
    }
    hashTable[hv] = hash_ll_insert(hashTable[hv], target); //在hash table該value所在位置加入值
    return hashTable;　//回傳hash table位置
}
```

#### handle collision

當遇到hash value衝突，使用linked list insert at front

```c
struct hash_node* hash_ll_insert(struct hash_node* node, int target) {
    struct hash_node* ptr = (struct hash_node*)malloc(sizeof(struct hash_node));　//建立新node
    ptr->key = target;　//在node儲存值
    if (!node) { //當hash table該位置為空
        ptr->next = NULL; //node下個位置設為NULL
        ptr->cnt = 1; //為第一個值
    }
    else {　//當hash table有重複
        ptr->next = node;　//將新node新增在已存在node前
        ptr->cnt = node->cnt + 1;　//重複值數量加一
    }
    return ptr;　//回傳該node
}
```

#### find

```c
struct hash_node* hash_find(struct hash_node** hashTable, int target) {
    int hv = hash65(target); //將值轉為hash後value
    struct hash_node* current = hashTable[hv]; //儲存當前node
    current = hashTable[hv]; //當前node為hash table該hv位置
    while (current != NULL) {　//traverse直到結尾
        if (current->key == target) //當找到時
            return current;　//回傳節點
        current = current->next; //未找到則繼續尋找
    }
    return NULL; //仍未找到回傳NULL
}
```



## 執行時間

##### (取三次結果，同一次 test 使用相同測資，使用參數-d 1e5 -q 1e4，單位為毫秒)

#### 第一次結果

```
bst: 
building time: 32.90 ms
query time: 3.56 ms

bs: 
building time: 0.56 ms
query time: 1.54 ms

arr: 
building time: 0.51 ms
query time: 1432.03 ms

ll: 
building time: 2.47 ms
query time: 2622.17 ms

hash: 
building time: 53.86 ms
query time: 1.64 ms
```

#### 第二次結果

```
bst: 
building time: 30.80 ms
query time: 3.52 ms

bs: 
building time: 0.68 ms
query time: 1.70 ms

arr: 
building time: 0.52 ms
query time: 1422.75 ms

ll: 
building time: 2.49 ms
query time: 2549.99 ms

hash: 
building time: 53.55 ms
query time: 1.52 ms
```

#### 第三次結果

```
bst: 
building time: 31.70 ms
query time: 2.99 ms

bs: 
building time: 0.57 ms
query time: 1.81 ms

arr: 
building time: 0.59 ms
query time: 1409.55 ms

ll: 
building time: 2.31 ms
query time: 2596.34 ms

hash: 
building time: 53.41 ms
query time: 1.57 ms
```



####　花費時間

##### build

Hash > Binary Search Tree > Linked List > Array with binary search = Array with traversal search

##### query

Linked List > Array with traversal search > Array with binary search > Binary Search Tree > Hash



#### 速度

##### build

Array with traversal search = Array with binary search > Linked List > Binary Search Tree > Hash

##### query

Hash > Binary Search Tree > Array with binary search > Array with traversal search > Linked List



## 時間複雜度

### build

#### Linked list: O(n)

#### Array: O(n)

#### Binary Search Tree: Best case O(nlogn), Worst case O(n^2)

#### Hash: O(n)

### query

#### Linked list: O(n)

#### Array with binary search: O(log(n))

#### Array with traversal search: O(n)

#### Binary Search Tree: O(log(n))

#### Hash: O(1)



## 空間複雜度

### build

#### Linked list: O(n)

#### Array: O(n)

#### Binary Search Tree: O(n)

#### Hash: O(1)

### query

#### Linked list: O(n)

#### Array with binary search: O(n)

#### Array with traversal search: O(n)

#### Binary Search Tree: O(n)

#### Hash: O(1)

## 總結

結構建立上hash花費時間較多其次為Binary Search Tree，其餘linked list與array時間相近。

查詢上Hash最快其次有運用到Binary search的查詢速度較快，最慢為依序尋訪。

在建立或查詢資料較多時，花費時間根據不同資料結構差異相當大，尤其是一般的尋訪搜尋常常會遇到搜尋不完的情形。

## 心得

透過實做這些資料結構可以提昇指標和結構的熟練度，也對遞迴更加熟悉。

## Reference

https://gateoverflow.in/50681/time-complexity-of-binary-tree-and-bst

https://medium.com/appworks-school/%E5%88%9D%E5%AD%B8%E8%80%85%E5%AD%B8%E6%BC%94%E7%AE%97%E6%B3%95-%E5%BE%9E%E6%99%82%E9%96%93%E8%A4%87%E9%9B%9C%E5%BA%A6%E8%AA%8D%E8%AD%98%E5%B8%B8%E8%A6%8B%E6%BC%94%E7%AE%97%E6%B3%95-%E4%B8%80-b46fece65ba5
