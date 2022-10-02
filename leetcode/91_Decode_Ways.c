#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

const char *test_string[] = { "2101", "12", "226", "06" };

int test_result[] = { 1, 2, 3, 0 };

int numDecodings(char *s)
{
	if (s[0] == '0')
		return 0;
	int len = strlen(s);
	if (len == 1)
		return 1;

	int n_1 = 1;
	int n_2 = 1;
	for (int i = 1; i < len; ++i) {
		int now = s[i] - '0';
		int pre = s[i - 1] - '0';
		int temp = now + (pre * 10);
		int n_i = 0;
		if (pre == 0 && temp == 0) // invalid
		{
			return 0;
		}
		if (now != 0) // valid
		{
			n_i = n_1;
		}
		if (temp >= 10 && temp <= 26) {
			n_i += n_2;
		}
		n_2 = n_1;
		n_1 = n_i;
	}

	return n_1;
}

int main(int argc, char *argv[])
{
	// for(int i=0;i<argc;i++) {
	//     printf("arg[%d]: %s\n", i, argv[i]);
	// }
	int er = 0;
	for (int i = 0; i < 4; i++) {
		printf("=================\n");
		int res = numDecodings(test_string[i]);
		if (test_result[i] != res) {
			printf("[%s], result: %d, got: %d\n", test_string[i],
			       test_result[i], res);
			er++;
		}
	}

	return er;
}
