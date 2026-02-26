#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} Point;

// STACK VERSION
Point create_point_stack(int x, int y) {
  Point p = {x, y};
  return p;
}

// HEAP VERSION
Point *create_point_heap(int x, int y) {
  Point *p = malloc(sizeof(Point));
  p->x = x;
  p->y = y;
  return p;
}

// Function that modifies point
void modify_stack(Point p) { // Gets COPY
  p.x = 999;
  p.y = 999;
}

void modify_heap(Point *p) { // Gets ORIGINAL
  p->x = 999;
  p->y = 999;
}

int main() {
  // STACK
  Point p1 = create_point_stack(10, 20);
  printf("Stack before: (%d, %d)\n", p1.x, p1.y); // (10, 20)
  modify_stack(p1);
  printf("Stack after:  (%d, %d)\n", p1.x, p1.y); // (10, 20) - UNCHANGED!

  // HEAP
  Point *p2 = create_point_heap(10, 20);
  printf("Heap before:  (%d, %d)\n", p2->x, p2->y); // (10, 20)
  modify_heap(p2);
  printf("Heap after:   (%d, %d)\n", p2->x, p2->y); // (999, 999) - CHANGED!

  free(p2); // Must free heap!

  return 0;
}
