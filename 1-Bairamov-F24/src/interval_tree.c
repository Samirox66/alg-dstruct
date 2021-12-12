#include "interval_tree.h"

tree_t* createNode(tree_t* parent, int left, int right) {
	tree_t* tree = (tree_t*)malloc(sizeof(tree_t));
	if (!tree) {
		return MEMORY_WAS_NOT_ALLOCATED;
	}
	tree->leftBorder = left;
	tree->rightBorder = right;
	tree->left = NULL;
	tree->right = NULL;
	tree->parent = parent;
	return tree;
}

int addByLeftBorder(tree_t** tree, int left, int right) {
	if (left > right) {
		return ERROR;
	}
	if (!(*tree)) {
		(*tree) = createNode((tree_t*)NULL, left, right);
		if (!(*tree))
			return ERROR;

	}
	tree_t* current = (*tree);
	while (current) {
		if (left < current->leftBorder) {
			if (!(current->left)) {
				current->left = createNode(current, left, right);
				if (!current) {
					return ERROR;
				}
			}
			else {
				current = current->left;
			}
		}
		else if (left > current->leftBorder || ((left == current->leftBorder) && (right != current->rightBorder))) {
			if (!(current->right)) {
				current->right = createNode(current, left, right);
				if (!current) {
					return ERROR;
				}
			}
			else {
				current = current->right;
			}
		}
		else if (current->leftBorder == left && current->rightBorder == right)
			return NOT_COMPLETED;
	}
	return COMPLETED;
}

tree_t* findByBorders(tree_t* tree, int left, int right) {
	if (!tree || left > right) {
		return INCORRECT_INPUT;
	}
	tree_t* current = tree;
	while (current) {
		if (left < current->leftBorder) {
			current = current->left;
		}
		else if (left > current->leftBorder) {
			current = current->right;
		}
		else if (right != current->rightBorder) {
			current = current->right;
		}
		else {
			return current;
		}
	}
	return NOT_FOUND;
}

void equateNodes(tree_t* deleted, tree_t* newSon) {
	deleted->leftBorder = newSon->leftBorder;
	deleted->rightBorder = newSon->rightBorder;
	return;
}

int deleteByBorders(tree_t* needed) {
	if (!needed) {
		return ERROR;
	}
	tree_t* temp = needed;
	if (!temp->left && !temp->right) {
		if (temp->parent->left == temp) {
			temp->parent->left = NULL;
		}
		else {
			temp->parent->right = NULL;
		}
	}
	else if (!temp->left && temp->right) {
		equateNodes(temp, temp->right);
		if (temp->parent->left == temp) {
			temp->parent->left = temp->right;
		}
		else {
			temp->parent->right = temp->right;
		}
		temp->right->parent = temp->parent;

	}
	else if (!temp->right && temp->left) {
		equateNodes(temp, temp->left);
		if (temp->parent->left == temp) {
			temp->parent->left = temp->left;
		}
		else {
			temp->parent->right = temp->left;
		}
		temp->left->parent = temp->parent;
	}

	else if (temp->left && temp->right) {
		temp = temp->left;
		while (temp->right) {
			temp = temp->right;
		}
		equateNodes(needed, temp);
		if (!temp->left) {
			if (temp->parent->left == temp) {
				temp->parent->left = NULL;
			}
			else {
				temp->parent->right = NULL;
			}
		}
		else if (temp->left) {
			if (temp->parent->left == temp) {
				temp->parent->left = temp->left;
			}
			else {
				temp->parent->right = temp->left;
			}
			temp->left->parent = temp->parent;
		}
	}
	free(temp);
	return COMPLETED;
}

int destroyTree(tree_t* tree) {
	if (!tree) {
		return ERROR;
	}
	tree->leftBorder = 0;
	tree->rightBorder = 0;
	destroyTree(tree->left);
	destroyTree(tree->right);
	free(tree);
	return COMPLETED;
}

int writeAnswer(int left, int right, answer_t* answer) {
	interval_t* intervals1 = NULL;
	answer->intervals[answer->count].leftBorder = left;
	answer->intervals[answer->count].rightBorder = right;
	answer->count++;
	intervals1 = (interval_t*)realloc(answer->intervals, sizeof(interval_t) * (answer->count + 1));
	if (!intervals1) {
		return ERROR;
	}
	answer->intervals = intervals1;
	intervals1 = NULL;
	return COMPLETED;
}

int intersectionCheck(tree_t* tree, int left, int right, answer_t* answer) {
	if (left <= tree->leftBorder && right >= tree->rightBorder) {
		writeAnswer(tree->leftBorder, tree->rightBorder, answer);
	}
	else if (tree->leftBorder <= left && tree->rightBorder >= right) {
		writeAnswer(tree->leftBorder, tree->rightBorder, answer);
	}
	else if (tree->leftBorder <= left && right >= tree->rightBorder && left <= tree->rightBorder) {
		writeAnswer(tree->leftBorder, tree->rightBorder, answer);
	}
	else if (left <= tree->leftBorder && right <= tree->rightBorder && right >= tree->leftBorder) {
		writeAnswer(tree->leftBorder, tree->rightBorder, answer);
	}
	else {
		return NOT_COMPLETED;
	}
	return COMPLETED;
}

int searchIntersecting(tree_t* tree, int left, int right, answer_t* answer) {
	tree_t* prevNode = NULL;
	int flag = NOT_COMPLETED;
	while (tree) {
		if (prevNode == tree->parent) {
			if (tree->left) {
				prevNode = tree;
				tree = tree->left;
				continue;
			}
			else {
				prevNode = NULL;
			}
		}
		if (prevNode == tree->left) {
			flag += intersectionCheck(tree, left, right, answer);
			if (tree->right) {
				prevNode = tree;
				tree = tree->right;
				continue;
			}
			else {
				prevNode = NULL;
			}
		}
		if (prevNode == tree->right) {
			prevNode = tree;
			tree = tree->parent;
		}
	}
	if (flag == NOT_COMPLETED) {
		return NOT_COMPLETED;
	}
	return COMPLETED;
}

void printAnswer(answer_t* answer) {
	for (int i = 0; i < answer->count; i++) {
		printf("[%d, %d]  ", answer->intervals[i].leftBorder, answer->intervals[i].rightBorder);
	}
	printf("\n");
	return;
}

int freeAnswer(answer_t* answer) {
	if (!answer) {
		return ERROR;
	}
	free(answer->intervals);
	free(answer);
	return COMPLETED;
}

void printTree(tree_t* tree) {
	tree_t* prevNode = NULL;
	while (tree) {
		if (prevNode == tree->parent) {
			if (tree->left) {
				prevNode = tree;
				tree = tree->left;
				continue;
			}
			else {
				prevNode = NULL;
			}
		}
		if (prevNode == tree->left) {
			printf("[%d  %d]\n", tree->leftBorder, tree->rightBorder);
			if (tree->right) {
				prevNode = tree;
				tree = tree->right;
				continue;
			}
			else {
				prevNode = NULL;
			}
		}
		if (prevNode == tree->right) {
			prevNode = tree;
			tree = tree->parent;
		}
	}
	return;
}