#pragma once
#pragma warning (disable: 4996)
#include "interval_tree.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	tree_t* tree = NULL;
	while (1) {
		int left = 0;
		int right = 0;
		char operation = getchar();
		if (operation == EOF || operation == '\n') {
			break;
		}
		if (scanf("%d %d", &left, &right) < 0) {
			printf("Error reading from input\n");
			exit(1);
		}
		if (operation == 'a') {
			addByLeftBorder(&tree, left, right);
		}
		else if (operation == 'd') {
			deleteByBorders(&tree, left, right);
		}
		else if (operation == 'f') {
			if (findByBorders(tree, left, right)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
		}
		else if (operation == 'i') {
			answer_t* answer = (answer_t*)malloc(sizeof(answer_t));
			if (!answer) {
				printf("Error allocating memory\n");
				exit(1);
			}
			answer->intervals = (interval_t*)malloc(sizeof(interval_t));
			if (!answer->intervals) {
				printf("Error allocating memory\n");
				exit(1);
			}
			answer->count = 0;
			if (searchIntersecting(tree, left, right, answer)) {
				printAnswer(answer);
			}
			else
				printf("no\n");
			freeAnswer(answer);
		}

		operation = getchar();
	}
	printTree(tree);
	destroyTree(tree);
	return 0;
}