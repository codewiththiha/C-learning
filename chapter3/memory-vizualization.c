#include <stdio.h>
#include <stdlib.h>

int main() {
  int *single = (int *)malloc(sizeof(int));
  printf("Garbage vale%d\n", *single);
  *single = 22;
  printf("Value assigned %d\n", *single);

  free(single);
  single = NULL;

  int size = 1000;
  int *arr = (int *)malloc(size * sizeof(int));

  for (int i = 0; i < size; i++) {
    printf("Value check for id: %d,Value: %d, Garbage value.\n", i,
           arr[i]); // for single value print out we need * but in indexs we
                    // don't need :))
  }

  printf("\nInitializing\n");
  for (int i = 0; i < size; i++) {
    arr[i] = i * 10;
  }

  for (int i = 0; i < size; i++) {
    printf("Value check for id: %d,Value: %d, Initialized value.\n", i,
           arr[i]); // for single value print out we need * but in indexs we
                    // don't need :))
  }

  free(arr);
  arr = NULL;

  return 0;
}
