#pragma warning(disable : 4996)
#include "gtest/gtest.h"

extern "C" {
#include "stack.h"
}

TEST(pushListTest, addingNewData_5) {
	list_node_t* stack = NULL;
	pushList(&stack, 5);
	EXPECT_EQ(stack->data, 5);
}

TEST(topListTest, topOfTheStack_1) {
	list_node_t* stack = (list_node_t*)malloc(sizeof(list_node_t));
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = 1;
	EXPECT_EQ(topList(stack), 1);
}

TEST(popListTest, newTopOfTheStackAfterPopping_4)
{
	list_node_t* stack = (list_node_t*)malloc(sizeof(list_node_t));
	list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
	if (stack == NULL || node == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = 4;
	node->data = 5;
	node->next = stack;
	stack = node;
	int pop = popList(&stack);
	EXPECT_EQ(stack->data, 4);
}

TEST(popListTest, poppingElement_5) {
	list_node_t* stack = (list_node_t*)malloc(sizeof(list_node_t));;
	list_node_t* node = (list_node_t*)malloc(sizeof(list_node_t));
	if (stack == NULL || node == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = 4;
	node->data = 5;
	node->next = stack;
	stack = node;
	EXPECT_EQ(popList(&stack), 5);
}

TEST(createArrayStackTest, checkingSize_10) {
	array_stack_t* stack = createArrayStack();
	EXPECT_EQ(stack->size, 10);
}

TEST(createArrayStackTest, checkingTop_0) {
	array_stack_t* stack = createArrayStack();
	EXPECT_EQ(stack->top, EMPTY_STACK);
}

TEST(pushArrayTest, addingElement_5) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	pushArray(stack, 5);
	EXPECT_EQ(stack->data[stack->top], 5);
}

TEST(pushArrayTest, checkingTopAfterPushing_0) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	pushArray(stack, 5);
	EXPECT_EQ(stack->top, 0);
}

TEST(pushArrayTest, checkingSizeAndTopAfterAllocatingMoreMemory_20_10) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	for (int i = 0; i < 11; i++) {
		pushArray(stack, i);
	}
	EXPECT_EQ(stack->size, 20);
	EXPECT_EQ(stack->top, 10);
}

TEST(topArrayTest, topOfTheStack_4) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	stack->top++;
	stack->data[stack->top] = 4;
	EXPECT_EQ(topArray(stack), 4);
}

TEST(popArrayTest, newTopOfTheStackAfterPoppping_4) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(2 * sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	stack->top++;
	stack->data[stack->top] = 4;
	stack->top++;
	stack->data[stack->top] = 5;
	int pop = popArray(stack);
	EXPECT_EQ(stack->data[stack->top], 4);
}

TEST(popArrayTest, poppingElement_2) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(2 * sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	stack->top++;
	stack->data[stack->top] = 4;
	stack->top++;
	stack->data[stack->top] = 5;
	EXPECT_EQ(popArray(stack), 5);
}

TEST(popArrayTest, checkingTopAfterPopping_1) {
	array_stack_t* stack = (array_stack_t*)malloc(sizeof(array_stack_t));;
	if (stack == NULL) {
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->data = (int*)malloc(2 * sizeof(int));
	if (stack->data == NULL) {
		free(stack);
		printf("Error allocating memory\n");
		exit(1);
	}
	stack->size = ARRAY_STACK_SIZE;
	stack->top = EMPTY_STACK;
	stack->top++;
	stack->data[stack->top] = 4;
	stack->top++;
	stack->data[stack->top] = 5;
	int pop = popArray(stack);
	EXPECT_EQ(stack->top, 0);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}