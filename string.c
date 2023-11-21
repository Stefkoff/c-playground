#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

char toLower(char c);

char toUpper(char c);

char *strToLowerCopy(const char *);

void strToLower(char *);

char *strToUpperCopy(const char *);

void strToUpper(char *);
void strToLower(char *);

int main() {
    char c = 'C';
    char cLower = toLower(c);
    printf("%c to lower case = %c\n", c, cLower);
    printf("%c to upper case = %c\n", cLower, toUpper(cLower));

    const char *str = "Hello World";
    const char *strLower = strToLowerCopy(str);
    printf("%s to lower = %s\n", str, strLower);
    const char *strUpper = strToUpperCopy(strLower);
    printf("%s to upper = %s\n", strLower, strUpper);
    char str2[] = "Hello World!";
    printf("%s to lower(without copy) equals to: ", str2);
    strToLower(str2);
    printf("%s\n", str2);

    char str3[] = "Hello Word!";
    printf("%s to upper(without copy) equals to: ", str3);
    strToUpper(str3);
    printf("%s", str3);
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
    if (c < 0x61 || c > 0x7a) {
        return c;
    }
    return c & (~(1 << 5));
}

char *strToLowerCopy(const char *str) {
    uint8_t index = 0;
    uint8_t size = strlen(str);
    char *result = (char *) malloc(size);
    memset(result, 0, size);

    while (index < size) {
        char c = toLower(str[index]);
        result[index] = toLower(str[index]);
        index++;
    }

    return result;
}


char *strToUpperCopy(const char *str) {
    uint8_t index = 0;
    uint8_t size = strlen(str);
    char *result = (char *) malloc(size);
    memset(result, 0, size);

    while (index < size) {
        result[index] = toUpper(str[index]);
        index++;
    }

    return result;
}

void strToLower(char *str) {
    uint8_t size = strlen(str);
    uint8_t index = 0;

    while (index < size) {
        str[index] = toLower(str[index]);
        index++;
    }
}

void strToUpper(char *str) {
    uint8_t size = strlen(str);
    uint8_t index = 0;

    while(index < size) {
        str[index] = toUpper(str[index]);
        index++;
    }
}