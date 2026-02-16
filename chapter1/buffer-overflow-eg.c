#include <stdio.h>
#include <string.h>

int main() {

  char buffer[5] = "test"; // including the /0 at the end

  printf("Before overflow: %s \n", buffer);
  printf("Before overflow buffer addr: %p \n", (void *)&buffer);
  printf("Before overflow buffer addr2: %p \n", (void *)buffer);

  // printf("Let Do Overflow..");
  // strcpy(buffer, "AAAAAAAAAA"); // add more than 5 to mock
  // printf("After overflow: %s \n", buffer);
  // printf("After overflow buffer addr: %p \n", (void *)&buffer);
  // printf("After overflow buffer addr2: %p \n", (void *)buffer);

  return 0;
}
