#pragma once
#pragma warning(disable: 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {
	FALSE, TRUE
} bool_t;

typedef struct {
	int* field;
	int n;
	bool_t isSolved;
} sudoku_t;

bool_t checkCell(sudoku_t sudoku, int value, int cell);
void solveSudoku(sudoku_t* sudoku, int value, int cell);
void readField(sudoku_t* sudoku);
void writeField(sudoku_t sudoku);

int main(int argc, char* argv[]) {
	sudoku_t sudoku;
	readField(&sudoku);
	solveSudoku(&sudoku, 1, 0);
	if (sudoku.isSolved == TRUE) {
		writeField(sudoku);
	}
	else {
		FILE* f = fopen("output.txt", "w");
		if (!f) {
			printf("Error opening output file\n");
			exit(1);
		}
		fprintf(f, "0");
		fclose(f);
	}
	return 0;
}

bool_t checkCell(sudoku_t sudoku, int value, int cell) {
	int row = cell / sudoku.n;
	int column = cell % sudoku.n;
	int smallSquare = (int)sqrt(sudoku.n);
	for (int i = 0; i < sudoku.n; i++) {
		if (value == sudoku.field[row * sudoku.n + i] || value == sudoku.field[i * sudoku.n + column]) {
			return FALSE;
		}
	}
	for (int i = 0; i < sudoku.n; i += smallSquare) {
		if (i + smallSquare > row) {
			row = i;
			break;
		}
	}
	for (int i = 0; i < sudoku.n; i += smallSquare) {
		if (i + smallSquare > column) {
			column = i;
			break;
		}
	}
	for (int i = 0; i < smallSquare; i++) {
		for (int j = 0; j < smallSquare; j++) {
			if (value == sudoku.field[(row + i) * sudoku.n + column + j]) {
				return FALSE;
			}
		}
	}
	return TRUE;
}

void solveSudoku(sudoku_t* sudoku, int value, int cell) {
	while (sudoku->field[cell] != 0 && cell + 1 < sudoku->n * sudoku->n) {
		cell++;
	}
	if (sudoku->field[cell] != 0) {
		sudoku->isSolved = TRUE;
		return;
	}
	while (sudoku->isSolved != TRUE && value <= sudoku->n) {
		if (checkCell(*sudoku, value, cell) == TRUE) {
			sudoku->field[cell] = value;
			if (cell + 1 == sudoku->n * sudoku->n) {
				sudoku->isSolved = TRUE;
			}
			else {
				solveSudoku(sudoku, 1, cell + 1);
				if (sudoku->isSolved != TRUE) {
					sudoku->field[cell] = 0;
				}
			}
		}
		value++;
	}
}

void readField(sudoku_t* sudoku) {
	FILE* f = fopen("input.txt", "r");
	if (!f) {
		printf("Error opening input file\n");
		exit(1);
	}
	char bufer;
	if (fscanf(f, "%d%c", &sudoku->n, &bufer) < 0) {
		printf("Error reading file\n");
		exit(1);
	}
	sudoku->n = sudoku->n * sudoku->n;
	sudoku->field = (int*)malloc(sudoku->n * sudoku->n * sizeof(int));
	if (!sudoku->field) {
		printf("Error allocating memory\n");
		exit(1);
	}
	for (int i = 0; i < sudoku->n * sudoku->n; i++) {
		if (fscanf(f, "%d%c", &sudoku->field[i], &bufer) < 0) {
			printf("Error reading file\n");
			exit(1);
		}
	}
	fclose(f);
}

void writeField(sudoku_t sudoku) {
	FILE* f = fopen("output.txt", "w");
	if (!f) {
		printf("Error opening file\n");
		exit(1);
	}
	fprintf(f, "%d\n", (int)sqrt(sudoku.n));
	for (int i = 0; i < sudoku.n * sudoku.n; i++) {
		if ((i + 1) % sudoku.n == 0) {
			fprintf(f, "%d\n", sudoku.field[i]);
		}
		else {
			fprintf(f, "%d ", sudoku.field[i]);
		}
	}
	fclose(f);
}
