#include <stdio.h>

int sum_by_index() {
  int sum = 0;
  int numbers[] = {1, 2, 3, 4};
  for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
    sum += numbers[i];
  }
  return sum;
}

int sum_by_pointers() {
  int sum = 0;
  int numbers[] = {1, 2, 3, 4};

  for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
    sum = *(&numbers[i]);
  }

  return sum;
}

int main() {
  int result1 = sum_by_index();
  printf("%d\n", result1);
  return 0;
}
