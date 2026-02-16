#include <stdio.h>
#include <stdlib.h>

int global_var = 23;
int uninit_global_var;

int main() {
  int stack_var = 23;

  int *heap_var = malloc(sizeof(int));

  if (heap_var == NULL) {
    printf("Memory allocation failed\n");
    return 1;
  }

  *heap_var = 200;

  printf("Adress of global_var: %p\n", (void *)&global_var);
  printf("Adress of heap_var: %p\n",
         (void *)heap_var); // we don't need & here as it's already an address
  printf("Value of global_var: %d\n", global_var);
  printf("Value of stack_var: %d\n", stack_var);
  printf("Value of heap_var: %d\n",
         *heap_var); // dereferenced into int (since it store int :D)
  printf("Address of heap_var itself): %p\n\n", (void *)&heap_var);

  free(heap_var);
  heap_var = NULL;

  return 0;
}
