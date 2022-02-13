#pragma once

typedef struct node_t {
    int data;
    struct node_t* left;
    struct node_t* right;
} binaryTree_t;

void runCompare();

void deleteBinaryTree(binaryTree_t** head, int elementToDelete);

void addBinaryTree(binaryTree_t** head, int elementToAdd);

int findBinaryTree(binaryTree_t* head, int elementToFind);

void freeBinaryTree(binaryTree_t* head);