#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

char* test_string[2] = {
  "hello",
  "leetcode",
};

char* test_result[2] = {
  "holle",
  "leotcede",
};

#define TEST_LEN (sizeof(test_string) / sizeof(char*))

#define IS_EQUAL(a, b) (a == b)
static inline bool isVowels(char ch)
{
  if (ch >= 'A' && ch < 'Z')
  {
    ch += 32;
  }
  return (IS_EQUAL(ch, 'a') || IS_EQUAL(ch, 'e') || IS_EQUAL(ch, 'i') || IS_EQUAL(ch, 'o') || IS_EQUAL(ch, 'u'));
}

void swap(char* a, char* b)
{
  char temp = *a;
  *a = *b;
  *b = temp;
}

char* reverseVowels(char* s)
{
  int length = strlen(s);

  int i_left = 0;
  int i_right = length - 1;
  while (i_right > i_left)
  {
    bool fg = false;
    if (isVowels(s[i_left]))
    {
      fg = true;
    }
    else
    {
      i_left++;
    }
    if (isVowels(s[i_right]))
    {
      if (fg)
      {
        swap(&s[i_left], &s[i_right]);
        i_left++;
        i_right--;
      }
    }
    else
    {
      i_right--;
    }
  }

  return s;
}

int main(int argc, char* argv[])
{
  (void)argc;
  (void)argv;
  char *buf = malloc(100);
  for (int i = 0; i < TEST_LEN; i++)
  {
    memset(buf, 0, 100);
    memcpy(buf, test_string[i], strlen(test_string[i]));
    assert(0 == memcmp(test_result[i], reverseVowels(buf), strlen(test_result[i])));
  }
  free(buf);

  return 0;
}
