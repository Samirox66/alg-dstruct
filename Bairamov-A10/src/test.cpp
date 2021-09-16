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
	list_node_t* stack = NULL;
	pushList(&stack, 1);
	EXPECT_EQ(topList(stack), 1);
}

TEST(popListTest, newTopOfTheStackAfterPopping_4) {
	list_node_t* stack = NULL;
	pushList(&stack, 4);
	pushList(&stack, 3);
	int pop = popList(&stack);
	EXPECT_EQ(popList(&stack), 4);
}

TEST(popListTest, poppingElement_3) {
	list_node_t* stack = NULL;
	pushList(&stack, 5);
	pushList(&stack, 3);
	EXPECT_EQ(popList(&stack), 3);
}

TEST(createArrayStackTest, checkingSize_10) {
	array_stack_t* stack = createArrayStack();
	EXPECT_EQ(stack->size, 10);
}

TEST(createArrayStackTest, checkingTop_0) {
	array_stack_t* stack = createArrayStack();
	EXPECT_EQ(stack->top, 0);
}

TEST(pushArrayTest, addingElement_5) {
	array_stack_t* stack = createArrayStack();
	pushArray(stack, 5);
	EXPECT_EQ(stack->data[stack->top - 1], 5);
}

TEST(pushArrayTest, checkingTopAfterPushing_1) {
	array_stack_t* stack = createArrayStack();
	pushArray(stack, 5);
	EXPECT_EQ(stack->top, 1);
}

TEST(pushArrayTest, checkingSizeAndTopAfterPushing13Times_20_13) {
	array_stack_t* stack = createArrayStack();
	for (int i = 0; i < 13; i++) {
		pushArray(stack, i);
	}
	EXPECT_EQ(stack->size, 20);
	EXPECT_EQ(stack->top, 13);
}

TEST(topArrayTest, topOfTheStack_4) {
	array_stack_t* stack = createArrayStack();
	pushArray(stack, 4);
	EXPECT_EQ(topArray(stack), 4);
}

TEST(popArrayTest, newTopOfTheStackAfterPoppping_4) {
	array_stack_t* stack = createArrayStack();
	pushArray(stack, 4);
	pushArray(stack, 7);
	int pop = popArray(stack);
	EXPECT_EQ(topArray(stack), 4);
}

TEST(popArrayTest, poppingElement_2) {
	array_stack_t* stack = createArrayStack();
	pushArray(stack, 4);
	pushArray(stack, 2);
	EXPECT_EQ(popArray(stack), 2);
}

TEST(popArrayTest, checkingTopAfterPopping_1) {
	array_stack_t* stack = createArrayStack();
	pushArray(stack, 4);
	pushArray(stack, 7);
	int pop = popArray(stack);
	EXPECT_EQ(stack->top, 1);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}