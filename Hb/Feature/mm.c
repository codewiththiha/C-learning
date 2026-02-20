#include <stdio.h>

// Function to get byte length of UTF-8 character from leading byte
int get_utf8_char_length(unsigned char byte) {
  if ((byte & 0x80) == 0x00)
    return 1; // 0xxxxxxx
  if ((byte & 0xE0) == 0xC0)
    return 2; // 110xxxxx
  if ((byte & 0xF0) == 0xE0)
    return 3; // 1110xxxx
  if ((byte & 0xF8) == 0xF0)
    return 4; // 11110xxx
  return 1;   // Continuation byte or invalid
}

int main() {
  char burmese[] = "အေးပါကွာ";
  char english[] = "Hello";

  printf("Burmese string:\n");
  int i = 0;
  printf("%lu\n", sizeof(burmese));
  while (i < sizeof(burmese) - 1) { // -1 to exclude null terminator
    int char_bytes = get_utf8_char_length((unsigned char)burmese[i]);
    printf("  Character at byte %d: %d bytes\n", i, char_bytes);
    i += char_bytes; // Skip to next character
  }

  printf("\nEnglish string:\n");
  i = 0;
  while (i < sizeof(english) - 1) {
    int char_bytes = get_utf8_char_length((unsigned char)english[i]);
    printf("  Character '%c' at byte %d: %d bytes\n", english[i], i,
           char_bytes);
    i += char_bytes;
  }

  return 0;
}
