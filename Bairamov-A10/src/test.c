#include "stack.h"

int main(void) {
	list_node_t* stack = NULL;
	for (int i = 0; i < 5; i++) {
		pushList(&stack, i);
		printf("Push %d\n", stack->data);
	}
	while (stack) {
		printf("Top %d\n", topList(stack));
		printf("Pop %d\n", popList(&stack));
	}
	array_stack_t* stackA = createArrayStack();
	for (int i = 0; i < 5; i++) {
		pushArray(stackA, i);
		printf("Push %d\n", stackA->data[stackA->top - 1]);
	}
	while (stackA) {
		printf("Top %d\n", topArray(stackA));
		printf("Pop %d\n", popArray(stackA));
	}
	return 0;
}