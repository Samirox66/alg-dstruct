#pragma once
#include <stdlib.h>
#include <stdio.h>
#define ARRAY_STACK_SIZE 10
#pragma warning(disable : 4996)

typedef struct list_node_t {
	int data;
	struct list_node_t* next;
} list_node_t;

typedef struct {
	int size;
	int top;
	int* data;
} array_stack_t;

void pushList(list_node_t** head, int data);
int popList(list_node_t** head);
int topList(list_node_t* head);
array_stack_t* createArrayStack();
void deleteArrayStack(array_stack_t** stack);
void pushArray(array_stack_t* array_stack, int data);
int popArray(array_stack_t* array_stack);
int topArray(array_stack_t* array_stack);
