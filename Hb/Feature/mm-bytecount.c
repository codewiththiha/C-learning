#include <stdio.h>
int main() {
  char sen[] = "အေးပါကွာ";
  printf("whole byte of mm:%d\n", (int)sizeof(sen));
  for (int i = 0; i < sizeof(sen) / sizeof(sen[0]); i++) {
    printf("Size of %c:%d\n", sen[i], (char)sizeof(sen[i]));
  }
  char eng[] = "Hello";
  printf("Whole byte of eng:%d\n", (int)sizeof(eng));
  for (int i = 0; i < sizeof(eng) / sizeof(eng[0]); i++) {
    printf("Size of %c:%d\n", eng[i], (char)sizeof(eng[i]));
  }
  return 0;
}
