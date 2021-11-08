#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <inttypes.h>
#include <limits.h>
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
void debugRecursivePrintHelperFunction(int recurseLevel, char* debugString) {
	for (int i = 0; i < recurseLevel; i++) {
		printf("  ");
	}
	printf("%s", debugString);
}
AVLNode *insert_AVLTree(AVLTree *tree, AVLNode *node, const void *data, int recurseCount) {
	const int data_value = *(const int *)data;
	int current_node_value = INT_MIN;
	int current_node_left_value = INT_MIN;
	int current_node_right_value = INT_MIN;
	char* debugString = malloc(sizeof(char) * 1000);
	sprintf(debugString, "Attempting to insert: %d \n", data_value);
	debugRecursivePrintHelperFunction(recurseCount, debugString);

	if (node != NULL) {
		current_node_value = *(const int *)node->data;
	}
	if (node == NULL) {
		sprintf(debugString, "Creating a new node with: %d \n", data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		return (newNode(tree, data));
	}
	if (tree->data_ops.compare(data, node->data) < 0) {
		sprintf(debugString, "Recursing down node->left to insert %d \n", data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		node->left = insert_AVLTree(tree, node->left, data, recurseCount + 1);
	}
	else if (tree->data_ops.compare(data, node->data) > 0) {
		sprintf(debugString, "Recursing down node->right to insert %d \n", data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		node->right = insert_AVLTree(tree, node->right, data, recurseCount + 1);
	}
	else {
		printf("Returning node.. bsts cant have duplicate vals \n");
		return node;
	}
	current_node_value = *(const int *)node->data;
	if (node != NULL && node->left != NULL && node->left->data != NULL) {
		current_node_left_value = *(const int *)node->left->data;
	}
	if (node != NULL && node->right != NULL && node->right->data != NULL)
	{
		current_node_right_value = *(const int *)node->right->data;
	}
	sprintf(debugString, "Setting the height of the node with value %d (inserting %d) \n", current_node_value, data_value);
	debugRecursivePrintHelperFunction(recurseCount, debugString);

	node->height = 1 + max(height(node->left), height(node->right));
	int balance = getBalance(node);

	if (balance > 1 && tree->data_ops.compare(data, node->left->data) < 0)
	{
		sprintf(debugString, "right rotating node with value %d (inserting %d) \n", current_node_value, data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		return rightRotate(node);
	}

	// Right Right Case
	if (balance < -1 && tree->data_ops.compare(data, node->right->data) > 0)
	{
		sprintf(debugString, "left rotating node with value %d (inserting %d) \n", current_node_value,data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		return leftRotate(node);
	}

	// Left Right Case
	if (balance > 1 && tree->data_ops.compare(data, node->left->data) > 0)
	{
		sprintf(debugString, "left rotating node with value %d (inserting %d), then... ", current_node_value, data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		node->left = leftRotate(node->left);
		sprintf(debugString, "right rotating node with value %d (inserting %d) \n", current_node_value, data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		return rightRotate(node);
	}

	// Right Left Case
	if (balance < -1 && tree->data_ops.compare(data, node->right->data) < 0)
	{
		sprintf(debugString, "right rotating node with value %d (inserting %d), then... ", current_node_value, data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		node->right = rightRotate(node->right);
		sprintf(debugString, "right rotating node with value %d (inserting %d), \n", current_node_value, data_value);
		debugRecursivePrintHelperFunction(recurseCount, debugString);
		return leftRotate(node);
	}
	
	sprintf(debugString, "Finally returning node with value %d (inserting %d) \n", current_node_value, data_value);
	debugRecursivePrintHelperFunction(recurseCount, debugString);
	return node;
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

/* Int operations*/

void *int_cp(const void *data)
{
	const int *input = (const int *)data;
	int *result;
	result = malloc(sizeof(*result));
	if (NULL == result)
	{
		fprintf(stderr, "malloc() failed in file %s at line # %d", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	// strcpy(result, input);
	*result = *input; 
	return result;
}
bool int_eq(const void *data1, const void *data2)
{
	const int *int1 = (const int *)data1;
	const int *int2 = (const int *)data2;
	return *int1 == *int2;
}

int int_compare(const void *data1, const void *data2)
{
	const int *int1 = (const int *)data1;
	const int *int2 = (const int *)data2;
	return *int1 - *int2;
}

void int_free(void *data)
{
	free(data);
}
void int_print(const void *data)
{
	printf("%d->", *(const int *)data);
}

AVLNodeDataOps data_ops_string = {string_cp, string_free, string_eq, string_compare, string_print};
AVLNodeDataOps data_ops_int = {int_cp, int_free, int_eq, int_compare, int_print};