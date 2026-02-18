#include <stdio.h>

int main() {

  int numbers[] = {10, 20, 30, 40, 50};
  int *ptr = numbers;

  int *first = &numbers[0];
  int *last = &numbers[4];
  printf("first , last address: %p , %p \n", first, last);
  printf("Byte difference: %ld\n", (char *)last - (char *)first);
  printf("Element difference: %ld (elements between)\n\n", last - first);

  for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
    printf("value,address of array no%d: %d,%p \n", i, numbers[i],
           (void *)&numbers[i]);
    printf("Before increase : %p,%d;After increase: %p,%d\n", ptr, *ptr,
           ptr + i, *(ptr + i));
  }

  printf("Before manual increase%p\n", ptr);
  for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
    ptr++;
  }

  printf("After manual increase %p\n", ptr);

  return 0;
}
