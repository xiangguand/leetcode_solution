#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

struct Node
{
  int val;
  int numNeighbors;
  struct Node** neighbors;
};

static struct Node* node_map[101];

struct Node* cloneNode(int val)
{
  struct Node* node = malloc(sizeof(struct Node));
  memset(node, 0, sizeof(struct Node));
  node->val = val;

  return node;
}

struct Node* getNodeFromMap(struct Node* node)
{
  if(node == NULL) return NULL;
  if (node_map[node->val])
  {
    return node_map[node->val];
  }
  node_map[node->val] = cloneNode(node->val);

  return node_map[node->val];
}

void help(struct Node* s, bool* visited)
{
  if ((s == NULL) || (visited[s->val]))
  {
    return;
  }
  visited[s->val] = true;

  struct Node* src = getNodeFromMap(s);

  for (int i = 0; i < s->numNeighbors; i++)
  {
    struct Node* next = s->neighbors[i];
    struct Node* dst = getNodeFromMap(next);
    ++src->numNeighbors;
    src->neighbors = realloc(src->neighbors, src->numNeighbors * sizeof(struct Node*));
    src->neighbors[src->numNeighbors - 1] = dst;

    help(next, visited);
  }
}

struct Node* cloneGraph(struct Node* s)
{
  if(s == NULL) return NULL;
  bool* visited = malloc(101 * sizeof(bool));
  memset(visited, 0, 101 * sizeof(bool));
  memset(node_map, 0, sizeof(node_map));

  help(s, visited);

  return node_map[s->val];
}

void test_help(struct Node* n1, struct Node* n2, bool* visited)
{
  assert(n1 != NULL);
  assert(n2 != NULL);
  if (visited[n1->val])
  {
    return;
  }
  visited[n1->val] = true;

  assert(n1->val == n2->val);
  assert(n1 != n2);
  assert(n1->numNeighbors == n2->numNeighbors);

  for (int i = 0; i < n1->numNeighbors; i++)
  {
    assert(n1->neighbors[i] != n2->neighbors[i]);
    assert(n1->neighbors[i]->val == n2->neighbors[i]->val);

    test_help(n1->neighbors[i], n2->neighbors[i], visited);
  }
}
//! test method
int compareTwoGraph(struct Node* n1, struct Node* n2)
{
  bool* visited = malloc(101 * sizeof(bool));
  memset(visited, 0, 101 * sizeof(bool));
  test_help(n1, n2, visited);
  return 0;
}

struct Node* genNode(int neighbor_n)
{
  struct Node* node = malloc(sizeof(struct Node));
  memset(node, 0, sizeof(struct Node));
  node->numNeighbors = neighbor_n;
  node->neighbors = malloc(neighbor_n * sizeof(struct Node*));
  memset(node->neighbors, 0, neighbor_n * sizeof(struct Node*));
  for (int i = 0; i < neighbor_n; i++)
  {
    node->neighbors[i] = malloc(sizeof(struct Node));
    memset(node->neighbors[i], 0, sizeof(struct Node));
  }

  return node;
}

int main(int argc, char* argv[])
{
  struct Node* n1 = genNode(2);
  struct Node* n2 = genNode(2);
  struct Node* n3 = genNode(2);
  struct Node* n4 = genNode(2);

  n1->val = 1;
  n1->neighbors[0] = n2;
  n1->neighbors[1] = n4;

  n2->val = 2;
  n2->neighbors[0] = n1;
  n2->neighbors[1] = n3;

  n3->val = 3;
  n3->neighbors[0] = n2;
  n3->neighbors[1] = n4;

  n4->val = 4;
  n4->neighbors[0] = n1;
  n4->neighbors[1] = n3;

  struct Node* graph = n1;

  struct Node* clone = cloneGraph(graph);
  printf("%d, %d\n", clone->val, clone->numNeighbors);
  struct Node* temp = clone->neighbors[0];
  printf("%d, %d\n", temp->val, temp->numNeighbors);
  temp = clone->neighbors[1];
  printf("%d, %d\n", temp->val, temp->numNeighbors);

  temp = clone->neighbors[0]->neighbors[0];
  printf("%d, %d\n", temp->val, temp->numNeighbors);
  temp = clone->neighbors[0]->neighbors[1];
  printf("%d, %d\n", temp->val, temp->numNeighbors);
  
  temp = clone->neighbors[1]->neighbors[0];
  printf("%d, %d\n", temp->val, temp->numNeighbors);
  temp = clone->neighbors[1]->neighbors[1];
  printf("%d, %d\n", temp->val, temp->numNeighbors);

  assert(0 == compareTwoGraph(graph, clone));

  printf("PASS\n");
  return 0;
}
