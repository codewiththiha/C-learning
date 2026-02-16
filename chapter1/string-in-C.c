#include <stdio.h>

char str[] = "Hello";

// Demostrating there is no string in C and everyting is just char or ASCII
int main() {
  for (int i = 0; str[i] != '\0'; i++) {
    printf("Character: %c,Integer: %d\n", str[i], (int)str[i]);
  }
  return 0;
}
