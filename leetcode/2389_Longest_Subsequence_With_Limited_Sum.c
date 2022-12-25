#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/*
You are given an integer array nums of length n, and an integer array queries of length m.

Return an array answer of length m where answer[i] is the maximum size of a subsequence that you can take from nums such
that the sum of its elements is less than or equal to queries[i].

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the
order of the remaining elements.
*/

int test_nums[][4] = { { 4, 5, 2, 1 }, { 2, 3, 4, 5 } };

int query1[] = { 3, 10, 21 };
int query2[] = { 1 };
int* test_queries[] = { query1, query2 };
int query_size[] = { sizeof(query1) / sizeof(int), sizeof(query2) / sizeof(query2) };

#define TEST_N (sizeof(test_nums) / sizeof(test_nums[0]))

int result1[] = { 2, 3, 4 };
int result2[] = { 0 };
int* test_results[] = { result1, result2 };

int cmp(const void* a, const void* b)
{
  return (*(int*) a) - (*(int*) b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* answerQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize)
{
  qsort(nums, numsSize, sizeof(int), cmp);

  int *result = malloc(queriesSize*sizeof(int));
  memset(result, 0, queriesSize*sizeof(int));
  *returnSize = queriesSize;

  for(int i=0;i<queriesSize;i++)
  {
    int count = 0;
    int temp = 0;
    for(int k=0;k<numsSize;k++)
    {
      if(temp + nums[k] <= queries[i])
      {
        temp += nums[k];
        count ++;
      }
      else
      {
        break;
      }
    }
    result[i] = count;
  }

  printf("=> ");
  for(int i=0;i<queriesSize;i++)
  {
    printf("%d, ", result[i]);
  }
  printf("\n");

  return result;
}

int main(int argc, char* argv[])
{
  for (int i = 0; i < TEST_N; i++)
  {
    int return_sz = 0;
    int* result = answerQueries(&test_nums[i][0], 4, test_queries[i], query_size[i], &return_sz);

    if (result == NULL || return_sz <= 0 || memcmp(result, test_results[i], return_sz * sizeof(int)) != 0)
    {
      printf("Fail\n");
      // assert(0);
    }
  }
}
