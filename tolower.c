#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char toLower(char c);
char toUpper(char c);
char* strToLower(const char*, uint8_t);
char* strToUpper(const char*, uint8_t);

int main() {
  char c = 'C';
  char cLower = toLower(c);
  printf("%c to lower case = %c\n", c, cLower);
  printf("%c to upper case = %c\n", cLower, toUpper(cLower));

  const char* str = "Hello World";
  const char* strLower = strToLower(str, 11);
  printf("%s to lower = %s\n", str,strLower); 
  const char* strUpper = strToUpper(strLower, 11);
  printf("%s to upper = %s\n", strLower, strUpper);

  return 0;
}

char toLower(char c) {
  // check if the character is not less than `A` or greater than 'Z'
  if (c < 0x41 || c > 0x5a) {
    return c;
  }
  return (c | 0x60);
}

char toUpper(char c) {
  // check if the character is not less than `a` or greater than 'z'
  if(c < 0x61 || c > 0x7a) {
    return c;
  }
  return c & (~(1 << 5));
}

 char* strToLower(const char* str, uint8_t size) {
  uint8_t index = 0;
  char* result = (char *) malloc(size);
  memset(result, 0, size);

  while(index < size) {
    char c = toLower(str[index]);
    result[index] = toLower(str[index]);
    index++;
  }

  return result;
}


char* strToUpper(const char* str, uint8_t size) {
  uint8_t index = 0;
  char* result = (char *) malloc(size);
  memset(result, 0, size);

  while(index < size) {
    result[index] = toUpper(str[index]);
    index++;
  }

  return result;
}
