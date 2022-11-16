#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_n[] = { 10, 1, 2, 20000 };
#define TEST_LEN (sizeof(test_n) / sizeof(int))
int test_result[] = { 6, 1, 1, 256 };

static int g_i = 0;

int guess(int num)
{
  int ret = 0;
  if (num < test_result[g_i])
  {
    ret = 1;
  }
  else if (num > test_result[g_i])
  {
    ret = -1;
  }
  else
  {
    ret = 0;
  }

  return ret;
}

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

int guessNumber(int n)
{
  // Using binary search algorithm
  int i_left = 0;
  int i_right = n;
  if (0 == guess(i_left))
  {
    return i_left;
  }
  if (0 == guess(i_right))
  {
    return i_right;
  }
  int i_mid = n >> 1;
  int guest_flag;
  while (i_left < i_right)
  {
    guest_flag = guess(i_mid);
    if (1 == guest_flag)
    {
      i_left = i_mid;
    }
    else if (-1 == guest_flag)
    {
      i_right = i_mid + 1;
    }
    else
    {
      break;
    }
    i_mid = (i_left + i_right) >> 1;
  }

  return i_mid;
}

int main(int argc, char* argv[])
{
  for (g_i = 0; g_i < TEST_LEN; g_i++)
  {
		printf("Test: %d\n", test_n[g_i]);
    assert(test_result[g_i] == guessNumber(test_n[g_i]));
		printf("===== Pass =====\n");
  }

  return 0;
}
