#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "uthash.h"

#define TEST_M (4)
#define TEST_N (4)
char test_board[4][4] = { { 'o', 'a', 'a', 'n' },
                          { 'e', 't', 'a', 'e' },
                          { 'i', 'h', 'k', 'r' },
                          { 'i', 'f', 'l', 'v' } };

char* test_words[4] = { "oath", "pea", "eat", "rain" };
char* test_result[2] = { "oath", "eat" };

/* uthash libraries */
typedef struct _wordHash_t
{
  char* word;
  UT_hash_handle hh;
} wordHash_t;

wordHash_t* head = NULL;

void addToWordHash(char* word)
{
  wordHash_t* word_hash = malloc(sizeof(wordHash_t));
  word_hash->word = word;
  HASH_ADD_STR(head, word, word_hash);
}

wordHash_t* searchWordHash(char* word)
{
  wordHash_t* hash_word = NULL;

  HASH_FIND_STR(head, word, hash_word); /* s: output pointer */
  return hash_word;
}

/* Using tries data structure */
typedef struct _trieNode_t
{
  struct _trieNode_t* children[26];  // a~z
  char* word;
} trieNode_t;

trieNode_t* generateTrieNode(void)
{
  trieNode_t* node = malloc(sizeof(trieNode_t));
  memset(node, 0, sizeof(trieNode_t));

  return node;
}

void insertTrieNode(trieNode_t* node, char* word)
{
  int index;

  int length = strlen(word);
  for (int i = 0; i < length; i++)
  {
    assert((word[i] >= 'a') && (word[i] <= 'z'));
    index = word[i] - 'a';
    if (NULL == node->children[index])
    {
      node->children[index] = generateTrieNode();
    }
    node = node->children[index];
  }
  node->word = malloc((length + 1) * sizeof(char));
  memcpy(node->word, word, (length + 1) * sizeof(char));
}

void dfsSearchBoard(char** board, int r, int c, const int m, const int n, bool** visited, trieNode_t* node,
                    char** result, int* i_result)
{
  /**
   * up:    1 0
   * down:  -1 0
   * left:  0 -1
   * right: 0 1
   */
  static const int DIR[] = { 0, 1, 0, -1, 0 };

  /* Return condition */
  if ((r < 0) || (r >= m) || (c < 0) || (c >= n) || visited[r][c])
  {
    return;
  }

  int index = board[r][c] - 'a';
  if (NULL == node->children[index])
  {
    return;
  }
  else if (NULL != node->children[index]->word)
  {
    // printf("%s\n", node->children[index]->word);

    if (searchWordHash(node->children[index]->word) == NULL)
    {
      addToWordHash(node->children[index]->word);
      int length = strlen(node->children[index]->word);
      result[(*i_result)] = malloc((length + 1) * sizeof(char));
      memset(result[*i_result], 0, (length + 1) * sizeof(char));
      memcpy(result[(*i_result)], node->children[index]->word, length * sizeof(char));
      (*i_result)++;
    }
  }

  visited[r][c] = true;

  for (int i = 0; i < 4; i++)
  {
    // printf("=>> %d, %c, %d\n", index, board[r][c], node->is_leaf);
    // printf("dir: %d, %d\n", DIR[i], DIR[i+1]);
    dfsSearchBoard(board, r + DIR[i], c + DIR[i + 1], m, n, visited, node->children[index], result, i_result);
  }

  visited[r][c] = false;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findWords(char** board, int boardSize, int* boardColSize, char** words, int wordsSize, int* returnSize)
{
  head = NULL;
  *returnSize = 0;
  trieNode_t* root = generateTrieNode();
  for (int i = 0; i < wordsSize; i++)
  {
    // printf("insert trie: %s\n", words[i]);
    insertTrieNode(root, words[i]);
  }

  bool** visited = malloc(boardSize * sizeof(bool*));

  /* malloc visited mem */
  for (int i = 0; i < boardSize; i++)
  {
    visited[i] = malloc(boardColSize[i] * sizeof(bool));
    memset(visited[i], 0, boardColSize[i] * sizeof(bool));
  }

  /* malloc result */
  char** result = malloc(wordsSize * sizeof(char*));
  memset(result, 0, wordsSize * sizeof(char*));

  for (int i = 0; i < boardSize; i++)
  {
    for (int j = 0; j < boardColSize[i]; j++)
    {
      memset(visited[i], 0, boardColSize[i] * sizeof(bool));
      dfsSearchBoard(board, i, j, boardSize, boardColSize[i], visited, root, result, returnSize);
    }
  }

  return result;
}

int main(int argc, char* argv[])
{
  int* board_col = malloc(TEST_M * sizeof(int));
  for (int i = 0; i < TEST_M; i++)
  {
    board_col[i] = TEST_N;
  }
  int ret_size = 0;
  char** test_board_ = malloc(4 * sizeof(char*));
  for (int i = 0; i < 4; i++)
  {
    test_board_[i] = malloc(4);
    memset(test_board_[i], 0, 4);
    memcpy(test_board_[i], &test_board[i][0], sizeof(&test_board[i]));
  }
  char** result = findWords(test_board_, TEST_M, board_col, test_words, 4, &ret_size);

  assert(2 == ret_size);
  for (int i = 0; i < 2; i++)
  {
    assert(result != NULL);
    assert(result[i] != NULL);
    assert(0 == strcmp(test_result[i], result[i]));
  }
}
