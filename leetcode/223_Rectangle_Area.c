#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define HELP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define HELP_MIN(a, b) ((a) < (b) ? (a) : (b))

int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
  int area1 = (ax2 - ax1) * (ay2 - ay1);
  int area2 = (bx2 - bx1) * (by2 - by1);

  int x1 = HELP_MAX(ax1, bx1);
  int y1 = HELP_MAX(ay1, by1);
  int x2 = HELP_MIN(ax2, bx2);
  int y2 = HELP_MIN(ay2, by2);

  int x = x2 - x1;
  int y = y2 - y1;

  int overlap = x * y;

  if (x < 0 || y < 0)
  {
    overlap = 0;
  }

  return (area1 + area2 - overlap);
}

int main(int argc, char* argv[])
{
  assert(45 == computeArea(-3, 0, 3, 4, 0, -1, 9, 2));
  assert(16 == computeArea(-2, -2, 2, 2, -2, -2, 2, 2));
  assert(16 == computeArea(-2, -2, 2, 2, -1, -1, 1, 1));
  assert(19 == computeArea(-2, -2, 2, 2, 1, 1, 3, 3));
  assert(17 == computeArea(-2, -2, 2, 2, -4, -4, -3, -3));

  return 0;
}
