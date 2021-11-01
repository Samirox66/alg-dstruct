#pragma once

#ifndef DFC
#define DFC
#include <stdlib.h>
#include <stdio.h>

typedef struct node_t {
	int number;
	struct node_t* node;
} node_t;

typedef struct {
	node_t* begin;
	node_t* end;
} list_t;

void freeList(list_t* list);

int readList(list_t lists[], int length);

int* DFS(list_t lists[], int length, int* lengthDFS);

#endif