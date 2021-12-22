#pragma once

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable: 4996)
#define NOT_FOUND NULL
#define INCORRECT_INPUT NULL
#define MEMORY_WAS_NOT_ALLOCATED NULL

enum {
	NOT_COMPLETED = 0,
	COMPLETED,
	ERROR
};

typedef struct tree_t {
	int leftBorder;
	int rightBorder;
	struct tree_t* left;
	struct tree_t* right;
	struct tree_t* parent;
} tree_t;

typedef struct {
	int leftBorder;
	int rightBorder;
} interval_t;

typedef struct {
	interval_t* intervals;
	int count;
} answer_t;

tree_t* createNode(tree_t* parent, int left, int right);
int addByLeftBorder(tree_t** tree, int left, int right);
tree_t* findByBorders(tree_t* tree, int left, int right);
void equateNodes(tree_t* deleted, tree_t* newSon);
int deleteByBorders(tree_t** tree, int left, int right);
int destroyTree(tree_t* tree);

int writeAnswer(int left, int right, answer_t* answer);
int intersectionCheck(tree_t* tree, int left, int right, answer_t* answer);
int searchIntersecting(tree_t* tree, int left, int right, answer_t* answer);
void printAnswer(answer_t* answer);
int freeAnswer(answer_t* answer);
void printTree(tree_t* tree);
