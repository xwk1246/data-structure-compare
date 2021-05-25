#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "./datagenerator.h"
#include "./array.h"
#include "./bst.h"
#include "./hash.h"
#include "./linkedlist.h"

void generatedata(int insertSize, int querySize) {
    genInsertDataSet(insertSize);
    genQueryDataSet(querySize);
}

void readdata() {

}

double getdiff(struct timeval start, struct timeval end) {
    return (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
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
            insertSize = atoi(argv[++i]);
        }
        else if (strcmp("-q", argv[i]) == 0) {
            querySize = atoi(argv[++i]);
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
    printf("%d\n", insertSize);
    printf("%d\n", querySize);
    printf("%d\n", bst);
    printf("%d\n", bs);
    printf("%d\n", hash);
    printf("%d\n", ll);
    printf("%d\n", arr);

    if (insertSize == -1 || querySize == -1) {
        fprintf(stderr, "-d and -q arguments required\n");
        exit(1);
    }
    insertArr = (int*)malloc(sizeof(int) * insertSize);
    queryArr = (int*)malloc(sizeof(int) * querySize);

    generatedata(insertSize, querySize);

    if (bst == 1) {
        printf("bst: \n");
        gettimeofday(&start, NULL);
        gettimeofday(&end, NULL);
    }
}