#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void pushList(list_node_t** head, int data) {
	list_node_t* tmp = (list_node_t*)malloc(sizeof(list_node_t));
	if (tmp == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	tmp->next = *head;
	tmp->data = data;
	*head = tmp;
}

int popList(list_node_t** head) {
	int data;
	if ((*head) == NULL) {
		printf("Empty stack\n");
		exit(1);
	}
	data = (*head)->data;
	list_node_t* tmp = *head;
	*head = (*head)->next;
	free(tmp);
	return data;
}

int topList(list_node_t* head) {
	if (head == NULL) {
		printf("Empty stack\n");
		exit(1);
	}
	return head->data;
}

array_stack_t* createArrayStack() {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->data = (int*)malloc(stack->size * sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->top = EMPTY_STACK;
	return stack;
}

void deleteArrayStack(array_stack_t** stack) {
	free((*stack)->data);
	free(*stack);
	*stack = NULL;
}


void pushArray(array_stack_t* array_stack, int data) {
	if (array_stack->top + 1 >= array_stack->size) {
		array_stack->size += ARRAY_STACK_SIZE;
		int* tmp = (int*)realloc(array_stack->data, array_stack->size * sizeof(int));
		if (tmp == NULL) {
			printf("Error allocating memory\n");
			exit(1);
		}
		array_stack->data = tmp;
	}
	array_stack->top++;
	array_stack->data[array_stack->top] = data;
}

int popArray(array_stack_t* array_stack) {
	if (array_stack->top == EMPTY_STACK) {
		printf("Empty stack\n");
		exit(1);
	}
	array_stack->top--;
	return array_stack->data[array_stack->top + 1];
}

int topArray(array_stack_t* array_stack) {
	if (array_stack->top == EMPTY_STACK) {
		printf("Empty stack :(\n");
		exit(1);
	}
	return array_stack->data[array_stack->top];
}