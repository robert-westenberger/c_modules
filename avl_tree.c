#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include "avl_tree.h"
#include "helpers.h"

AVLTree *create_AVLTree(AVLNodeDataOps data_ops) {
    AVLTree *tree;
    tree = malloc(sizeof(*tree));
    if (NULL == tree)
    {
        fprintf(stderr, "malloc() failed in file %s at line # %d", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
    tree->head = NULL;
    tree->data_ops = data_ops;

    return tree;
}
static AVLNode *newNode(AVLTree *tree, const void *data) {
	struct AVLNode *node = (struct AVLNode *)
			malloc(sizeof(struct AVLNode));
	node->data = tree->data_ops.cp(data);
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // new node is initially added at leaf
	return (node);
}

static int height(AVLNode *node) {
	if (node == NULL) {
		return 0;
	}
	return node->height;
}

static int getBalance(AVLNode *N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

// A utility function to right rotate subtree rooted with y
// See the diagram given above.
AVLNode *rightRotate(AVLNode *y)
{
	AVLNode *x = y->left;
	AVLNode *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
AVLNode *leftRotate(AVLNode *x)
{
	AVLNode *y = x->right;
	AVLNode *T2 = y->left;

	// Perform rotation
	y->left = x;
	x->right = T2;

	//  Update heights
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;

	// Return new root
	return y;
}

AVLNode *insert_AVLTree(AVLTree *tree, const void *data) {
	AVLNode** nodePtr = &tree->head;
	if (*nodePtr == NULL) {
		*nodePtr = newNode(tree, data);
		return *nodePtr;
	}
	while (*nodePtr != NULL) {
		if (tree->data_ops.compare(data, (*nodePtr)->data) < 0) {
			*nodePtr = (*nodePtr)->left;
		}
		else if (tree->data_ops.compare(data, (*nodePtr)->data) > 0) {
			*nodePtr = (*nodePtr)->right;
		}
		else {
			return *nodePtr;
		}
	}
	(*nodePtr)->height = 1 + max(height((*nodePtr)->left), height((*nodePtr)->right));
	int balance = getBalance(*nodePtr);

	// tree->data_ops.compare(data, (*nodePtr)->data) > 0

	if (balance > 1 && tree->data_ops.compare(data, (*nodePtr)->left->data) < 0)
	{
		return rightRotate(*nodePtr);
	}
	

	// Right Right Case
	if (balance < -1 && tree->data_ops.compare(data, (*nodePtr)->right->data) > 0) {
		return leftRotate(*nodePtr);
	}
		

	// Left Right Case
	if (balance > 1 && tree->data_ops.compare(data, (*nodePtr)->left->data) > 0)
	{
		(*nodePtr)->left = leftRotate((*nodePtr)->left);
		return rightRotate(*nodePtr);
	}

	// Right Left Case
	if (balance < -1 && tree->data_ops.compare(data, (*nodePtr)->right->data) < 0)
	{
		(*nodePtr)->right = rightRotate((*nodePtr)->right);
		return leftRotate(*nodePtr);
	}
	return *nodePtr;
	
}

/* String operations*/

void *string_cp(const void *data)
{
	const char *input = (const char *)data;
	size_t input_length = strlen(input) + 1;
	char *result;
	result = malloc(sizeof(*result) * input_length);
	if (NULL == result)
	{
		fprintf(stderr, "malloc() failed in file %s at line # %d", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	strcpy(result, input);
	return result;
}
bool string_eq(const void *data1, const void *data2)
{
	const char *str1 = (const char *)data1;
	const char *str2 = (const char *)data2;
	return !(strcmp(str1, str2)) ? true : false;
}

int string_compare(const void *data1, const void *data2)
{
	const char *str1 = (const char *)data1;
	const char *str2 = (const char *)data2;
	int returnVal = strcmp(str1, str2);
	return returnVal;
}

void string_free(void *data)
{
	free(data);
}
void string_print(const void *data)
{
	printf("%s\n", (const char *)data);
}

AVLNodeDataOps data_ops_string = {string_cp, string_free, string_eq, string_compare};