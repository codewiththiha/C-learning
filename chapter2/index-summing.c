#include <stdio.h>

//// we cannot do that since every passed parameters in C will be treated as a
/// pointer
// int sum_by_index(int numbers[]) {
//   int sum = 0;
//
//   for (int i = 0; i < sizeof(numbers) / sizeof(numbers[0]); i++) {
//     sum += numbers[i];
//   }
//   return sum;
// }

int sum_by_index(int numbers[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += numbers[i];
  }

  return sum;
}

// In C function parameters, int ptr[] and int *ptr are exactly the same. The
// compiler ignores the [] and treats both as int *ptr. Even if you write int
// ptr[100], the compiler ignores the 100. It still becomes a pointer.
// so basically whatever you do *ptr or ptr[] on parameter C will treat them as
// pointers
int sum_by_ptr(int ptr[], int size) {
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += *(ptr + i);
  }

  return sum;
}

//// the concept ,in case you confused
// arr + 5  =  arr + (5 × sizeof(int))
//          =  0x100 + (5 × 4 bytes)
//          =  0x100 + 20 bytes
//          =  0x114
int sum_by_increasing_ptr(int *ptr, int size) {
  int sum = 0;
  int *cptr = ptr;
  int *end = ptr + size;

  while (cptr < end) {
    sum += *cptr;
    cptr++;
  }

  return sum;
}

int main() {
  int numbers[] = {1, 2, 3, 4};
  int size = sizeof(numbers) / sizeof(numbers[0]);
  //  int result1 = sum_by_index(numbers, size);
  //  int result2 = sum_by_ptr(numbers, size);
  int result3 = sum_by_increasing_ptr(numbers, size);
  printf("%d\n", result3);
  return 0;
}
