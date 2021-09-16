#pragma warning(disable : 4996)
#include "gtest/gtest.h"

extern "C" {
#include "stack.h"
}

TEST(pushListTest, addingNewData) {
	list_node_t* stack = NULL;
	pushList(&stack, 5);
	EXPECT_EQ(5, stack->data);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}