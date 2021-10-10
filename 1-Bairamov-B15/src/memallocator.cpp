#include "memallocator.h"
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct node {
    int size;
    struct node* next;
    struct node* prev;
    int isFree;
} descriptor_t;

static struct {
    descriptor_t* list;
    int totalSize;
} s_memStruct = { (descriptor_t*)NULL, 0 };

int meminit(void* pMemory, int size) {
    int minSize = memgetminimumsize();
    int blockSize = memgetblocksize();
    if (pMemory == NULL || size < minSize + 1)
        return 0;
    else {
        s_memStruct.list = (descriptor_t*)pMemory;
        s_memStruct.list->isFree = TRUE;
        s_memStruct.list->next = NULL;
        s_memStruct.list->prev = NULL;
        s_memStruct.list->size = size - blockSize;
        s_memStruct.totalSize = size;
        return 1;
    }
}

void* memalloc(int size) {
    descriptor_t* cur;
    descriptor_t* newB;
    descriptor_t* pointerBestFit = NULL;
    int blockSize = memgetblocksize();
    void* res = NULL;
    if (size <= 0 || s_memStruct.list == NULL) {
        return NULL;
    }
    if (s_memStruct.list) {
        cur = s_memStruct.list;

        do {
            if ((cur->size >= size) && (pointerBestFit == NULL || (cur->size < pointerBestFit->size)) && (cur->isFree == TRUE)) {
                pointerBestFit = cur;
            }
            cur = cur->next;
        } while (cur);

        if (pointerBestFit) {
            if (pointerBestFit->size <= size + memgetminimumsize()) {
                pointerBestFit->isFree = FALSE;
            }
            else {
                newB = (descriptor_t*)((char*)pointerBestFit + size + blockSize);
                newB->prev = pointerBestFit;
                newB->next = pointerBestFit->next;
                if (pointerBestFit->next) {
                    pointerBestFit->next->prev = newB;
                }
                pointerBestFit->next = newB;
                pointerBestFit->isFree = FALSE;
                newB->isFree = TRUE;
                newB->size = pointerBestFit->size - size - blockSize;
                pointerBestFit->size = size;
            }
            res = (void*)((char*)pointerBestFit + blockSize);
        }
        else {
            res = NULL;
        }
    }
    return res;
}

void memfree(void* p) {
    descriptor_t* firstFree = NULL;
    descriptor_t* newFree = NULL;
    int blockSize = memgetblocksize();
    if (p && s_memStruct.list) {
        newFree = (descriptor_t*)((char*)p - blockSize);
        if (newFree >= s_memStruct.list && newFree <= s_memStruct.list + s_memStruct.totalSize && (newFree->isFree == FALSE)) {
            newFree->isFree = TRUE;
            if (newFree->next) {
                if (newFree->next->isFree) {
                    firstFree = newFree;
                    firstFree->size += firstFree->next->size + blockSize;
                    if (firstFree->next->next) {
                        firstFree->next->next->prev = firstFree;
                        firstFree->next = firstFree->next->next;
                    }
                    else {
                        firstFree->next = NULL;
                    }
                    if (firstFree->prev) {
                        firstFree->prev->next = firstFree;
                    }
                    else {
                        firstFree->prev = NULL;
                    }
                }
            }
            if (newFree->prev) {
                if (newFree->prev->isFree) {
                    firstFree = newFree->prev;
                    if (firstFree->next)
                        firstFree->size += firstFree->next->size + blockSize;
                    if (firstFree->next) {
                        if (firstFree->next->next) {
                            firstFree->next->next->prev = firstFree;
                            firstFree->next = firstFree->next->next;
                        }
                        else {
                            firstFree->next = NULL;
                        }
                    }
                }
            }
        }
    }
}

void memdone() {
    s_memStruct.list = NULL;
    s_memStruct.totalSize = 0;
}

int memgetminimumsize() {
    return sizeof(descriptor_t);
}

int memgetblocksize() {
    return sizeof(descriptor_t);
}