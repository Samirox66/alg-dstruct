#pragma warning(disable: 4996)
#include "Lab-C-1.h"

void freeList(list_t* list) {
    node_t* curElement = list->begin;
    while (curElement != NULL) {
        list->begin = list->begin->node;
        free(curElement);
        curElement = list->begin;
    }
}

int readList(list_t lists[], int length) {
    int i, number;
    char ch;
    for (i = 0; i < length; i++) {
        if (scanf("%d%c", &number, &ch) < 0) {
            return 1;
        }
        while (ch == ' ') {
            if (scanf("%d%c", &number, &ch) < 0) {
                return 1;
            }
            if (!lists[i].begin) {
                lists[i].begin = (node_t*)malloc(sizeof(node_t));
                if (lists[i].begin == NULL) {
                    for (i = 0; i < length; i++) {
                        freeList(&lists[i]);
                    }
                    return 1;
                }
                lists[i].end = lists[i].begin;
            }
            else {
                lists[i].end->node = (node_t*)malloc(sizeof(node_t));
                if (lists[i].end->node == NULL) {
                    for (i = 0; i < length; i++) {
                        freeList(&lists[i]);
                    }
                    return 1;
                }
                lists[i].end = lists[i].end->node;
            }
            lists[i].end->number = number;
            lists[i].end->node = NULL;
            if (i < number) {
                if (!lists[number].begin) {
                    lists[number].begin = (node_t*)malloc(sizeof(node_t));
                    if (lists[number].begin == NULL) {
                        for (i = 0; i < length; i++) {
                            freeList(&lists[i]);
                        }
                        return 1;
                    }
                    lists[number].end = lists[number].begin;
                }
                else {
                    lists[number].end->node = (node_t*)malloc(sizeof(node_t));
                    if (lists[number].end->node == NULL) {
                        for (i = 0; i < length; i++) {
                            freeList(&lists[i]);
                        }
                        return 1;
                    }
                    lists[number].end = lists[number].end->node;
                }
                lists[number].end->number = i;
                lists[number].end->node = NULL;
            }
        }
    }
    return 0;
}

int* DFS(list_t adjLists[], int length, int* lengthDFS) {
    int* dfs = (int*)malloc(sizeof(int) * length);
    struct {
        int* elements;
        int  topOfStack;
    } stack;
    int i = 0;
    int j;
    node_t* curNode;

    stack.elements = (int*)malloc(sizeof(int) * length);
    if (!dfs || !stack.elements) {
        free(dfs);
        free(stack.elements);
        return 0;
    }
    dfs[0] = 0;
    *lengthDFS = 1;
    stack.elements[0] = 0;
    stack.topOfStack = 0;

    while (stack.topOfStack != -1) {
        curNode = adjLists[i].begin;
        for (j = 0; j < *lengthDFS; j++) {
            if (curNode != NULL && curNode->number == dfs[j]) {
                curNode = curNode->node;
                j = 0;
            }
        }
        if (curNode == NULL) {
            i = stack.elements[stack.topOfStack - 1];
            stack.topOfStack--;
        }
        else {
            stack.topOfStack++;
            stack.elements[stack.topOfStack] = curNode->number;
            (*lengthDFS)++;
            dfs[*lengthDFS - 1] = curNode->number;
            i = curNode->number;
        }
    }

    return dfs;
}