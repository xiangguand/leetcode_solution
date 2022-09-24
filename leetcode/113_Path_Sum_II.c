#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_result[2][4] = { { 5, 4, 11, 2 }, { 5, 8, 4, 5 } };

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
};

struct TreeNode *generate_node(int val)
{
	struct TreeNode *node = malloc(sizeof(struct TreeNode));
	node->left = NULL;
	node->right = NULL;
	node->val = val;

	return node;
}

void getMaxRootOfLeaves(struct TreeNode *node, int *count, int depth,
			int *max_depth)
{
	if (!node)
		return;

	if ((!node->left) && (!node->right)) {
		(*count)++;
	}
	getMaxRootOfLeaves(node->left, count, depth + 1, max_depth);
	getMaxRootOfLeaves(node->right, count, depth + 1, max_depth);

	if (depth > *max_depth) {
		*max_depth = depth;
	}
}

void helperPathSum(struct TreeNode *node, int targetSum, int *accum, int **res,
		   int *i_res, int *col_res, int *buf, int *i_buf)
{
	if (!node)
		return;

	buf[(*i_buf)++] = node->val;
	*accum += node->val;
	helperPathSum(node->left, targetSum, accum, res, i_res, col_res, buf,
		      i_buf);
	helperPathSum(node->right, targetSum, accum, res, i_res, col_res, buf,
		      i_buf);

	printf("===== Root of leaf =====\n");
	printf("%d, %d\n", node->val, *accum);
	if ((!node->left) && (!node->right)) {
		if (*accum == targetSum) {
			res[(*i_res)] = malloc((*i_buf) * sizeof(int));
			memcpy(res[(*i_res)], buf, (*i_buf) * sizeof(int));
			col_res[(*i_res)] = (*i_buf);
			(*i_res)++;
		}
	}
	(*i_buf)--;
	*accum -= node->val;
}

int **pathSum(struct TreeNode *root, int targetSum, int *returnSize,
	      int **returnColumnSizes)
{
	int accum = 0;
	int root_of_leaves = 0;
	int max_depth = 0;
	getMaxRootOfLeaves(root, &root_of_leaves, 1, &max_depth);

	int **res = malloc(root_of_leaves * sizeof(int *));
	int i_res = 0;
	int *col_res = malloc(root_of_leaves * sizeof(int));
	int *buf = malloc(max_depth * sizeof(int));
	int i_buf = 0;

	helperPathSum(root, targetSum, &accum, res, &i_res, col_res, buf,
		      &i_buf);
	*returnSize = i_res;
	*returnColumnSizes = col_res;

	free(buf);

	return res;
}

int main(int argc, char *argv[])
{
	struct TreeNode *root = generate_node(5);
	root->left = generate_node(4);
	root->left->left = generate_node(11);
	root->left->left->left = generate_node(7);
	root->left->left->right = generate_node(2);

	root->right = generate_node(8);
	root->right->left = generate_node(13);
	root->right->right = generate_node(4);
	root->right->right->left = generate_node(5);
	root->right->right->right = generate_node(1);

	int return_sz;
	int *col_sz;
	int **result = pathSum(root, 22, &return_sz, &col_sz);

	printf("%d, %p\n", return_sz, col_sz);

	printf("Result:\n");
	for (int i = 0; i < return_sz; i++) {
		for (int j = 0; j < col_sz[i]; j++) {
			printf("%d, ", result[i][j]);
			assert(result[i][j] == test_result[i][j]);
		}
		printf("\n");
	}
}
