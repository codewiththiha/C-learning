#include <stdio.h>

int main() {

  int number = 20;
  int *ptr1 = &number;
  int **ptr2 = &ptr1; // in this example ** mean address's address pointer
  int ***ptr3 = &ptr2;

  printf("%d\n",
         ***ptr3); // in this example mean we are dereferencing pointer's
                   // pointer's address's value that why we need ***

  return 0;
}
