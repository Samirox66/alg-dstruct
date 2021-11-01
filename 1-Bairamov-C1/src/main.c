#pragma once
#pragma warning(disable: 4996)
#include "Lab-C-1.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    list_t* lists;
    int n, i, lengthDFS;
    int error;
    int* dfs;
    //vertex_t* vertex;
    if (scanf("%d", &n) < 0) {
        printf("Error reading from stdin\n");
            return 1;
    }
    lists = (list_t*)malloc(sizeof(list_t) * n);
    if (!lists) {
        return 1;
    }
    for (i = 0; i < n; i++) {
        lists[i].begin = NULL;
        lists[i].end = NULL;
    }
    error = readList(lists, n, stdin);
    if (error == 1) {
        free(lists);
        return 1;
    }
    /*printf("\n\n");
    for (i = 0; i < n; i++) {
      vertex = adjLists[i].begin;
      while (vertex != NULL){
        printf("%d ", vertex->number);
        vertex = vertex->vertex;
      }
      printf("\n");
    }*/

    dfs = DFS(lists, n, &lengthDFS);
    for (i = 0; i < lengthDFS; i++) {
        printf("%d ", dfs[i]);
    }
    for (i = 0; i < n; i++) {
        freeList(&lists[i]);
    }
    free(lists);
    return 0;
}