#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

int test_n[] = { 6, 1, 14 };
#define TEST_N (sizeof(test_n) / sizeof(int))
bool test_result[] = { 1, 1, 0 };

bool isUgly(int n)
{
  if (n == 0)
  {
    return false;
  }
  bool ret = false;
  while (true)
  {
    if (1 == n)
    {
      ret = true;
      break;
    }
    else if (0 == (n % 2))
    {
      n /= 2;
    }
    else if (0 == (n % 3))
    {
      n /= 3;
    }
    else if (0 == (n % 5))
    {
      n /= 5;
    }
    else
    {
      break;
    }
  }

  return ret;
}

int main(int argc, char* argv[])
{
  for (int i = 0; i < TEST_N; i++)
  {
    printf("===== Feed %d =====\n", test_n[i]);
    assert(test_result[i] == isUgly(test_n[i]));
  }

  return 0;
}
