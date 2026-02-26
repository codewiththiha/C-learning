#include <stdio.h>
#include <string.h>

int println(
    char *string) { // or use string[] both will get converted to pointers in C
  printf("%s\n", string);
  return 0;
}

int printGarbage(char *string) {
  size_t len = strlen(string);
  for (int i = 0; i < len; i++) {
    printf("Index %d | Address: %p | Char: '%c' | String from here: \"%s\",| "
           "Whole address : %p|\n",
           i,
           (void *)&string[i], // Actual address
           string[i],          // Single character
           &string[i],
           (void *)&string); // String from this position & whole address
  }
  return 0;
}

int main() {
  println("Hello World");
  printGarbage("Hello");
  return 0;
}
