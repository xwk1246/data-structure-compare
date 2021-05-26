#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "./datagenerator.h"
#include "./array.h"
#include "./bst.h"
#include "./hash.h"
#include "./linkedlist.h"

void generatedata(int insertSize, int querySize) {
    genInsertDataSet(insertSize);
    genQueryDataSet(querySize);
}

void readdata(int* insertDataSet, int* queryDataSet) {
    FILE* fp1;
    FILE* fp2;
    int* ptr;
    fp1 = fopen("./insertdataset.txt", "r");
    fp2 = fopen("./querydataset.txt", "r");
    ptr = insertDataSet;
    while (fscanf(fp1, "%d", ptr++) != EOF)
        ;
    ptr = queryDataSet;
    while (fscanf(fp2, "%d", ptr++) != EOF)
        ;
    fclose(fp1);
    fclose(fp2);
}

double getdiff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
}

int convert(char* note) {
    int tmp;
    int i;
    if (strncmp(note, "1e", 2) == 0) {
        tmp = 1;
        for (i = 0; i < note[2] - '0'; i++) {
            tmp *= 10;
        }
        return tmp;
    }
    return -1;
}

int main(int argc, char** argv) {
    struct timeval start;
    struct timeval end;
    int* insertArr;
    int* queryArr;
    int insertSize = -1;
    int querySize = -1;
    int bst = -1;
    int bs = -1;
    int arr = -1;
    int ll = -1;
    int hash = -1;

    int i;
    for (i = 1; i < argc; i++) {
        if (strcmp("-d", argv[i]) == 0) {
            insertSize = convert(argv[++i]);
        }
        else if (strcmp("-q", argv[i]) == 0) {
            querySize = convert(argv[++i]);
        }
        else if (strcmp("-bst", argv[i]) == 0) {
            bst = 1;
        }
        else if (strcmp("-bs", argv[i]) == 0) {
            bs = 1;
        }
        else if (strcmp("-arr", argv[i]) == 0) {
            arr = 1;
        }
        else if (strcmp("-ll", argv[i]) == 0) {
            ll = 1;
        }
        else if (strcmp("-hash", argv[i]) == 0) {
            hash = 1;
        }
    }

    if (insertSize == -1 || querySize == -1) {
        fprintf(stderr, "-d and -q arguments required\n");
        exit(1);
    }
    srand(time(NULL));
    generatedata(insertSize, querySize);
    genInsertDataSet(insertSize);
    insertArr = (int*)malloc(sizeof(int) * insertSize);
    queryArr = (int*)malloc(sizeof(int) * querySize);
    readdata(insertArr, queryArr);

    if (bst == 1) {
        struct Bst* b = NULL;
        printf("bst: \n");
        gettimeofday(&start, NULL);
        for (i = 0; i < insertSize; i++) {
            b = bst_insert(b, insertArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("building time: %.2f ms\n", getdiff(start, end) / 1000);

        gettimeofday(&start, NULL);
        for (i = 0; i < querySize; i++) {
            bst_find(b, queryArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("query time: %.2f ms\n\n", getdiff(start, end) / 1000);
        free(b);
    }
    if (bs == 1) {
        struct Arr* a = NULL;
        printf("bs: \n");
        gettimeofday(&start, NULL);
        for (i = 0; i < insertSize; i++) {
            a = arr_insert(a, insertArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("building time: %.2f ms\n", getdiff(start, end) / 1000);
        qsort(a->data, a->tail, sizeof(int), compare);

        gettimeofday(&start, NULL);
        for (i = 0; i < querySize; i++) {
            arr_bs_find(a, queryArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("query time: %.2f ms\n\n", getdiff(start, end) / 1000);
        free(a);
    }
    if (arr == 1) {
        struct Arr* a = NULL;
        printf("arr: \n");
        gettimeofday(&start, NULL);
        for (i = 0; i < insertSize; i++) {
            a = arr_insert(a, insertArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("building time: %.2f ms\n", getdiff(start, end) / 1000);

        gettimeofday(&start, NULL);
        for (i = 0; i < querySize; i++) {
            arr_traverse_find(a, queryArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("query time: %.2f ms\n\n", getdiff(start, end) / 1000);
        free(a);
    }
    if (ll == 1) {
        struct LinkedList* ll = NULL;
        printf("ll: \n");
        gettimeofday(&start, NULL);
        for (i = 0; i < insertSize; i++) {
            ll = ll_insert(ll, insertArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("building time: %.2f ms\n", getdiff(start, end) / 1000);

        gettimeofday(&start, NULL);
        for (i = 0; i < querySize; i++) {
            ll_find(ll, queryArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("query time: %.2f ms\n\n", getdiff(start, end) / 1000);
        free(ll);
    }
    if (hash == 1) {
        struct hash_node** h = NULL;
        printf("hash: \n");
        gettimeofday(&start, NULL);
        for (i = 0; i < insertSize; i++) {
            h = hash_insert(h, insertArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("building time: %.2f ms\n", getdiff(start, end) / 1000);

        gettimeofday(&start, NULL);
        for (i = 0; i < querySize; i++) {
            hash_find(h, queryArr[i]);
        }
        gettimeofday(&end, NULL);
        printf("query time: %.2f ms\n\n", getdiff(start, end) / 1000);
        free(h);
    }
}