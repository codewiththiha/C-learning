//// This file is pasted from an AI bot
//// Buggy Code (Don't Run Without Sanitizer!)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === BUG 1: Dangling Pointer ===
int *get_dangling_pointer() {
  int local = 42;
  return &local; // BUG: Stack variable dies when function returns!
}

// === BUG 2: Use After Free ===
void use_after_free_bug() {
  int *ptr = malloc(sizeof(int));
  *ptr = 100;
  printf("Before free: %d\n", *ptr);

  free(ptr);

  // BUG: Using memory after free!
  printf("After free: %d\n", *ptr); // UNDEFINED BEHAVIOR!
}

// === BUG 3: Buffer Overflow ===
void buffer_overflow_bug() {
  char buffer[10] = "hello";

  // BUG: Writing 25 chars into 10-byte buffer!
  strcpy(buffer, "This is way too long!"); // OVERFLOW!

  printf("Buffer: %s\n", buffer);
}

int main() {
  printf("=== Exercise 3: Bug Hunt ===\n\n");

  printf("Testing Bug 1 (Dangling Pointer):\n");
  int *dangling = get_dangling_pointer();
  printf("Value: %d\n\n", *dangling); // May work, may crash!

  printf("Testing Bug 2 (Use After Free):\n");
  use_after_free_bug();
  printf("\n");

  printf("Testing Bug 3 (Buffer Overflow):\n");
  buffer_overflow_bug();

  return 0;
}
