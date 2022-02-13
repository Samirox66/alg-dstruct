#include "binaryTree.h"
#include <stdlib.h>
#include <stdio.h>

int findBinaryTree(binaryTree_t* head, int elementToFind) {
    binaryTree_t* node = head;

    while (node != NULL) {
        if (node->data > elementToFind) {
            node = node->left;
        }
        else if (node->data == elementToFind) {
            return 1;
        }
        else {
            node = node->right;
        }
    }
    return 0;
}

void deleteBinaryTree(binaryTree_t** head, int elementToDelete) {
    binaryTree_t* node = *head;
    binaryTree_t** parent = NULL;

    while (node != NULL) {
        if (node->data > elementToDelete) {
            parent = &node->left;
            node = node->left;
        }
        else if (node->data == elementToDelete) {
            if (node->right == NULL && node->left == NULL) {
                if (parent == NULL) {
                    *head = NULL;
                }
                else {
                    *parent = NULL;
                }
                free(node);
                return;
            }
            else if (node->right != NULL) {
                binaryTree_t* successor = node->right;
                while (successor->right != NULL) {
                    successor = successor->right;
                }

                int tmp = node->data;
                node->data = successor->data;
                successor->data = tmp;
                deleteBinaryTree(&node->right, successor->data);
                return;
            }
            else {
                binaryTree_t* predecessor = node->left;
                while (predecessor->left != NULL) {
                    predecessor = predecessor->left;
                }

                int tmp = node->data;
                node->data = predecessor->data;
                predecessor->data = tmp;
                deleteBinaryTree(&node->left, predecessor->data);
                return;
            }
        }
        else {
            parent = &node->right;
            node = node->right;
        }
    }
}

void addBinaryTree(binaryTree_t** head, int elementToAdd) {
    binaryTree_t* tmp = NULL;
    binaryTree_t* nodeToAdd = (binaryTree_t*)malloc(sizeof(binaryTree_t));
    if (nodeToAdd == NULL) {
        return;
    }

    nodeToAdd->data = elementToAdd;
    nodeToAdd->left = NULL;
    nodeToAdd->right = NULL;
    if (*head == NULL) {
        *head = nodeToAdd;
        return;
    }

    tmp = *head;
    while (tmp != NULL) {
        if (elementToAdd > tmp->data) {
            if (tmp->right) {
                tmp = tmp->right;
                continue;
            }
            else {
                tmp->right = nodeToAdd;
                return;
            }
        }
        else if (elementToAdd < tmp->data) {
            if (tmp->left) {
                tmp = tmp->left;
                continue;
            }
            else {
                tmp->left = nodeToAdd;
                return;
            }
        }
        else {
            return;
        }
    }
}

void freeBinaryTree(binaryTree_t* head) {
    if (head == NULL) {
        return;
    }

    freeBinaryTree(head->left);
    freeBinaryTree(head->right);
    free(head);
}