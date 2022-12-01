#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

const char* test_char[] = { "book", "textbook" };
bool test_result[] = { true, false };

const char vowels[] = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };

bool isVowel(char ch)
{
  for (int i = 0; i < sizeof(vowels); i++)
  {
    if (ch == vowels[i])
    {
      return true;
    }
  }

  return false;
}

bool halvesAreAlike(char* s)
{
  int length = strlen(s);
  int count = 0;
  for (int i = 0; i < length / 2; i++)
  {
    if (isVowel(s[i]))
    {
      count++;
    }
  }
  for (int i = length / 2; i < length; i++)
  {
    if (isVowel(s[i]))
    {
      count--;
    }
  }

  return count == 0 ? true : false;
}

int main(int argc, char* argv[])
{
  char buf[20];

  for (int i = 0; i < 2; i++)
  {
    memset(buf, 0, sizeof(buf));
    memcpy(buf, test_char[i], strlen(test_char[i]));
    bool result = halvesAreAlike(buf);
    assert(test_result[i] == result);
  }
}
