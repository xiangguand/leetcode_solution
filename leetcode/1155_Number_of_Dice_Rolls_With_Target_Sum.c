#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

const int test_n[] = { 1, 2, 30 };
const int test_k[] = { 6, 6, 30 };
const int test_target[] = { 3, 7, 500 };
const int test_ans[] = { 1, 6, 222616187 };

#define TEST_NUM (sizeof(test_ans) / sizeof(int))

#define MODULO (1000000007U)
int MIN(int a, int b)
{
	if (a > b)
		return b;
	return a;
}
int numRollsToTarget(int n, int k, int target)
{
	int **dp = (int **)malloc((n + 1) * sizeof(int *));
	for (int i = 0; i < n + 1; i++) {
		dp[i] = (int *)malloc((target + 1) * sizeof(int));
		memset(dp[i], 0, (target + 1) * sizeof(int));
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++) {
		for (int t = target; t >= 0; t--) {
			for (int j = 1; j <= MIN(k, t); j++) {
				dp[i][t] =
					(dp[i][t] + dp[i - 1][t - j]) % MODULO;
			}
		}
	}

	return dp[n][target];
}

int main(int argc, char *argv[])
{
	int er = 0;
	for (int i = 0; i < TEST_NUM; i++) {
		int res =
			numRollsToTarget(test_n[i], test_k[i], test_target[i]);
		if (res != test_ans[i]) {
			er++;
		}
	}

	return er;
}
