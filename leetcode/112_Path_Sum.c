#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

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

void helper(struct TreeNode *node, int targetSum, int *sum, bool *flag)
{
	if (!node)
		return;
	*sum += node->val;
	helper(node->left, targetSum, sum, flag);
	helper(node->right, targetSum, sum, flag);
	if (!node->left && !node->right && *sum == targetSum)
		if (*sum == targetSum) {
			*flag = true;
		}
	*sum -= node->val;
}

bool hasPathSum(struct TreeNode *root, int targetSum)
{
	int temp = 0;
	bool flag = false;
	helper(root, targetSum, &temp, &flag);

	return flag;
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

	if (!hasPathSum(root, 22)) {
		return 1;
	}

	return 0;
}
