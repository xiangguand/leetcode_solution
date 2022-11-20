#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char* test_s[] = { "1 + 1", " 2-1 + 2 ", "(1+(4+5+2)-3)+(6+8)", "1+(50-12+1)-50" };
int test_result[] = { 2, 3, 23, -10 };
#define TEST_LEN (sizeof(test_result) / sizeof(int))

bool isCharADigit(char ch)
{
  return ((ch >= '0') && (ch <= '9'));
}

typedef struct _num_t
{
  int num;
  int sign;
} num_t;

int calculate(char* s)
{
  int length = strlen(s);
  printf("%s, Len: %d\n", s, length);
  long cur = 0;
  long sign = 1;
  long result = 0;
  num_t* temp_result = malloc(length * sizeof(num_t));
  long i_temp = 0;

  for (int i = 0; i < length; i++)
  {
    if (isCharADigit(s[i]))
    {
      cur = cur * 10 + (long)(s[i] - '0');
    }
    else if ('+' == s[i])
    {
      result += sign * cur;
      sign = 1;
      cur = 0;
    }
    else if ('-' == s[i])
    {
      result += sign * cur;
      sign = -1;
      cur = 0;
    }
    else if ('(' == s[i])
    {
      // push and save
      temp_result[i_temp].num = result;
      temp_result[i_temp++].sign = sign;
      result = 0;
      sign = 1;
      cur = 0;
    }
    else if (')' == s[i])
    {
      // pop and restore
      assert(i_temp > 0);
      result += sign * cur;
      cur = 0;
      result *= temp_result[--i_temp].sign;
      result += temp_result[i_temp].num;
    }
    else
    {
      ;
    }
  }
  result += sign * cur;

  return (int)result;
}
int main(int argc, char* argv[])
{
  int ret = 0;
  for (int i = 0; i < TEST_LEN; i++)
  {
    printf("===== calculate: %s =====\n", test_s[i]);
    char* buf = malloc((strlen(test_s[i]) + 1) * sizeof(char));
    memset(buf, 0, strlen((test_s[i]) + 1) * sizeof(char));
    memcpy(buf, test_s[i], strlen(test_s[i]) * sizeof(char));
    int result = calculate(buf);
    if (result != test_result[i])
    {
      printf("FAIL, Get: %d\n", result);
      ret = -1;
    }
    else
    {
      printf("PASS\n");
    }
    free(buf);
  }

  return ret;
}
