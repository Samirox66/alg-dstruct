#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TEST_SYSTEM
#ifndef TEST_SYSTEM
#include "binaryTree.h"
#include <Windows.h>
#include <time.h>
#endif


typedef struct aatree_t {
	int data;
	int level;
	struct aatree_t* right;
	struct aatree_t* left;
} aatree_t;

void runTestSystem();

void runCompare();

void freeAaTree(aatree_t* head);

void addAaTree(aatree_t** head, int elementToAdd);

int findAaTree(aatree_t* head, int elementToFind);

void deleteAaTree(aatree_t** head, int elementToDelete);

int main(int argc, char* argv[]) {
#ifdef TEST_SYSTEM
	runTestSystem();
#else
	runCompare();
#endif

	return 0;
}
#ifndef TEST_SYSTEM
void runCompare() {
	srand((unsigned)time(NULL));
	FILE* f = fopen("compare.csv", "w");
	if (f == NULL) {
		printf("Error opening file\n");
		exit(1);
	}

	LARGE_INTEGER frequency;
	LARGE_INTEGER start;
	LARGE_INTEGER end;
	double interval[2];
	const int maxOperations = 1000;
	const int maxData = 100;
	QueryPerformanceFrequency(&frequency);
	fprintf(f, "Operations;Binary adding;AA adding;Binary searching;AA searching;Binary deleting;AA deleting\n");
	for (int operations = 100; operations <= maxOperations; operations += 100) {
		//adding
		binaryTree_t* binaryTree = NULL;
		aatree_t* aaTree = NULL;
		QueryPerformanceCounter(&start);
		for (int i = 0; i < operations; i++) {
			addBinaryTree(&binaryTree, rand() % maxData);
			QueryPerformanceCounter(&end);
		}
		QueryPerformanceCounter(&end);
		printf("Adding binary is finished\n");
		interval[0] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		QueryPerformanceCounter(&start);
		for (int i = 0; i < operations; i++) {
			addAaTree(&aaTree, rand() % maxData);
		}
		QueryPerformanceCounter(&end);
		printf("Adding aa is finished\n");
		interval[1] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		fprintf(f, "%d;%lf;%lf;", operations, interval[0], interval[1]);
		printf("Adding is finished\n");
		//searching
		QueryPerformanceCounter(&start);
		for (int i = 0; i < operations; i++) {
			findBinaryTree(binaryTree, rand() % maxData);
			QueryPerformanceCounter(&end);
		}
		QueryPerformanceCounter(&end);
		printf("Searching binary is finished\n");
		interval[0] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		QueryPerformanceCounter(&start);
		for (int i = 0; i < operations; i++) {
			findAaTree(aaTree, rand() % maxData);
			QueryPerformanceCounter(&end);
		}
		QueryPerformanceCounter(&end);
		printf("Searching aa is finished\n");
		interval[1] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		fprintf(f, "%lf;%lf;", interval[0], interval[1]);
		printf("Searching is finished\n");
		//deleting
		QueryPerformanceCounter(&start);
		for (int i = 0; i < operations; i++) {
			deleteBinaryTree(&binaryTree, rand() % maxData);
			QueryPerformanceCounter(&end);
		}
		QueryPerformanceCounter(&end);
		printf("Deleting binary is finished\n");
		interval[0] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		QueryPerformanceCounter(&start);
		for (int i = 0; i < operations; i++) {
			deleteAaTree(&aaTree, rand() % maxData);
		}
		QueryPerformanceCounter(&end);
		printf("Deleting aa is finished\n");
		interval[1] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
		fprintf(f, "%lf;%lf\n", interval[0], interval[1]);
		printf("Deleting is finished\n");
		freeAaTree(aaTree);
		freeBinaryTree(binaryTree);
	}
	fclose(f);
}
#endif

void runTestSystem() {
	aatree_t* aaTree = NULL;
	char buffer[1000];
	char symbol = 0;
	char command = 0;
	int num = 0;
	int i = 0;
	symbol = getchar();
	while (symbol != EOF) {
		command = symbol;
		symbol = getchar();
		while (isspace(symbol)) {
			symbol = getchar();
		}

		while (isdigit(symbol)) {
			buffer[i] = symbol;
			i++;
			symbol = getchar();
		}

		buffer[i] = '\0';
		num = atoi(buffer);
		i = 0;

		switch (command) {
		case 'a': {
			addAaTree(&aaTree, num);
			break;
		}
		case 'f': {
			if (findAaTree(aaTree, num)) {
				printf("yes\n");
			}
			else {
				printf("no\n");
			}
			break;
		}
		case 'r': {
			deleteAaTree(&aaTree, num);
			break;
		}
		}

		if (symbol == '\n') {
			symbol = getchar();
		}
	}

	freeAaTree(aaTree);
}

void skew(aatree_t** head) {
	aatree_t* tmpNode1;
	aatree_t* tmpNode2;
	if ((*head) == NULL || (*head)->left == NULL) {
		return;
	}

	if ((*head)->left->level == (*head)->level) {
		tmpNode1 = (*head);
		tmpNode2 = (*head)->left->right;
		(*head) = (*head)->left;
		(*head)->right = tmpNode1;
		(*head)->right->left = tmpNode2;
	}
}

void split(aatree_t** head) {
	aatree_t* tmpNode1;
	aatree_t* tmpNode2;
	if ((*head) == NULL || (*head)->right == NULL || (*head)->right->right == NULL) {
		return;
	}

	if ((*head)->level == (*head)->right->right->level) {
		tmpNode1 = (*head);
		(*head)->right->level += 1;
		(*head) = (*head)->right;
		tmpNode2 = (*head)->left;
		(*head)->left = tmpNode1;
		(*head)->left->right = tmpNode2;
	}
}

void addAaTree(aatree_t** head, int elemToInsert) {
	if ((*head) == NULL) {
		aatree_t* newNode = (aatree_t*)malloc(sizeof(aatree_t));
		if (newNode == NULL) {
			printf("Error allocating memory to new node\n");
			exit(1);
		}

		newNode->data = elemToInsert;
		newNode->level = 1;
		newNode->left = NULL;
		newNode->right = NULL;
		(*head) = newNode;
		return;
	}

	if (elemToInsert < (*head)->data) {
		addAaTree(&((*head)->left), elemToInsert);
	}
	else if (elemToInsert > (*head)->data) {
		addAaTree(&((*head)->right), elemToInsert);
	}

	skew(head);
	split(head);
}

int findAaTree(aatree_t* head, int elemToFind) {
	int ifExists = 0;
	if (head == NULL) {
		return ifExists;
	}

	if (elemToFind < head->data) {
		ifExists = findAaTree(head->left, elemToFind);
	}
	else if (elemToFind > head->data) {
		ifExists = findAaTree(head->right, elemToFind);
	}
	else {
		ifExists = 1;
	}

	return ifExists;
}

void deleteAaTree(aatree_t** head, int elemToDelete) {
	aatree_t** tmpNode1;
	aatree_t* tmpNode2;
	int tmpData;
	if ((*head) == NULL) {
		return;
	}

	if ((*head)->data < elemToDelete) {
		deleteAaTree(&((*head)->right), elemToDelete);
	}
	else if ((*head)->data > elemToDelete) {
		deleteAaTree(&((*head)->left), elemToDelete);
	}
	else if ((*head)->left == NULL && (*head)->right == NULL) {
		free((*head));
		(*head) = NULL;
		return;
	}
	else if ((*head)->left == NULL) {
		tmpNode2 = (*head);
		(*head) = (*head)->right;
		free(tmpNode2);
		return;
	}
	else if ((*head)->right == NULL) {
		tmpNode2 = (*head);
		(*head) = (*head)->left;
		free(tmpNode2);
		return;
	}
	else {
		tmpNode1 = &((*head)->left);
		while ((*tmpNode1)->right != NULL) {
			tmpNode1 = &(*tmpNode1)->right;
		}

		tmpData = (*tmpNode1)->data;
		(*tmpNode1)->data = (*head)->data;
		(*head)->data = tmpData;
		deleteAaTree(&((*head)->left), elemToDelete);
	}

	int leftNodeLevel = 0;
	int rightNodeLevel = 0;
	int newLevel = 1;
	if ((*head)->left) {
		leftNodeLevel = (*head)->left->level;
	}

	if ((*head)->right) {
		rightNodeLevel = (*head)->right->level;
	}

	if (leftNodeLevel < rightNodeLevel) {
		newLevel += leftNodeLevel;
	}
	else {
		newLevel += rightNodeLevel;
	}

	if (newLevel < (*head)->level) {
		(*head)->level = newLevel;
		if (newLevel < rightNodeLevel) {
			(*head)->right->level = newLevel;
		}
	}

	skew(head);
	skew(&((*head)->right));
	if ((*head)->right) {
		skew(&((*head)->right->right));
	}

	split(head);
	split(&((*head)->right));
}

void freeAaTree(aatree_t* head) {
	if (head == NULL) {
		return;
	}

	freeAaTree(head->left);
	freeAaTree(head->right);
	free(head);
}
