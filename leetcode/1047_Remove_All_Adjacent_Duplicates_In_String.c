#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

const char* test_string[] = { "abbaca", "azxxzy" };
#define TEST_LEN (sizeof(test_string) / sizeof(char*))

const char* test_result[] = { "ca", "ay" };

void print_buf(char* buf, int len)
{
  for (int i = 0; i < len; i++)
  {
    printf("%c, ", buf[i]);
  }
  printf("\n");
}
char* removeDuplicates(char* s)
{
  int length = strlen(s);
  char* buf = malloc(length * sizeof(char));
  int i_buf = 0;

  buf[i_buf++] = s[0];
  for (int i = 1; i < length; i++)
  {
    buf[i_buf] = s[i];
    if ((i_buf > 0) && (buf[i_buf] == buf[i_buf - 1]))
    {
      // pop
      i_buf--;
    }
    else
    {
      i_buf++;
    }
    // print_buf(buf, i_buf);
  }
  buf[i_buf] = '\0';

  return buf;
}

int main(int argc, char* argv[])
{
  for (int i = 0; i < TEST_LEN; i++)
  {
    char* string = malloc((strlen(test_string[i]) + 1) * sizeof(char));
    memset(string, 0, (strlen(test_string[i]) + 1) * sizeof(char));
    memcpy(string, test_string[i], strlen(test_string[i]));
    char* remove_str = removeDuplicates(string);
    printf("%s, %s\n", remove_str, test_result[i]);
    int check = strcmp(remove_str, test_result[i]);
    assert(0 == check);
  }

  return 0;
}
