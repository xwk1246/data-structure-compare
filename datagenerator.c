#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAXDATALEN 10000000

int genInsertDataSet(int dataSize) {
    int i;
    int* exist = (int*)malloc(sizeof(int) * MAXDATALEN);
    memset(exist, 0, MAXDATALEN);
    srand(time(NULL));
    FILE* fp = fopen("./insertdataset.txt", "w");
    for (i = 0; i < dataSize; i++) {
        int tmp;
        do {
            tmp = rand() % 10000000;
        }
        while (exist[tmp]);
        fprintf(fp, "%d\n", tmp);
        exist[tmp] = 1;
    }
    fclose(fp);
}

int genQueryDataSet(int datasize) {
    int i;
    int tmp;
    FILE* fp = fopen("./querydataset.txt", "w");
    srand(time(NULL));
    for (i = 0; i < datasize; i++) {
        tmp = rand() % MAXDATALEN;
        fprintf(fp, "%d\n", tmp);
    }
    fclose(fp);
}