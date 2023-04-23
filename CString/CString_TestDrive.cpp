#include <cassert>
#include "cstring.h"

using namespace std;

void StrlenTestDrive() {
  const char *string_1 = "testword";
  const char *string_2 = "";
  const char *string_3 = " ";
  const char *string_4 = "\0";

  assert(Strlen(string_1) == 8);
  assert(Strlen(string_2) == 0);
  assert(Strlen(string_3) == 1);
  assert(Strlen(string_4) == 0);
}

void StrcmpTestDrive() {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  const char *str3 = "World";
  const char *str4 = "hello";
  const char *str5 = "Hello world!";
  const char *str6 = "Hello";
  const char *str7 = "";

  assert(Strcmp(str1, str2) == 0);
  assert(Strcmp(str1, str3) < 0);
  assert(Strcmp(str1, str4) < 0);
  assert(Strcmp(str1, str5) < 0);
  assert(Strcmp(str1, str6) == 0);
  assert(Strcmp(str1, str7) > 0);

  // Strncmp
  assert(Strncmp("abcd", "abce", 3) == 0);
  assert(Strncmp("hello", "help", 3) == 0);
  assert(Strncmp("hello", "help", 4) < 0);
  assert(Strncmp("help", "hello", 4) > 0);
  assert(Strncmp("hello", "hello", 5) == 0);
  assert(Strncmp("hello", "world", 1) < 0);
  assert(Strncmp("world", "hello", 1) > 0);
  assert(Strncmp("hello", "world", 0) == 0);
}

void StrcpyTestDrive() {
  char str1[20] = "Hello";
  char str2[20] = "World";

  assert(Strcmp(Strcpy(str1, str2), "World") == 0);
  assert(Strcmp(Strcpy(str1, "World"), "World") == 0);
  assert(Strcmp(Strcpy(str2, ""), "") == 0);
  assert(Strcmp(Strcpy(str2, ""), "") == 0);
}

void StrncpyTestDrive() {
  char src1[] = "Hello world";
  char dest1[20];
  Strncpy(dest1, src1, 11);
  assert(Strcmp(dest1, "Hello world") == 0);

  char src2[] = "Hello world";
  char dest2[20];
  Strncpy(dest2, src2, 5);
  assert(Strcmp(dest2, "Hello") == 0);

  char src3[] = "";
  char dest3[20];
  Strncpy(dest3, src3, 5);
  assert(Strcmp(dest3, "") == 0);

  char src4[] = "Hello world";
  char dest4[20];
  Strncpy(dest4, src4, 15);
  assert(Strcmp(dest4, "Hello world") == 0);

  char src5[] = "Simon";
  char dest5[] = "Hello world";
  Strncpy(dest5, src5, 8);
  assert(Strcmp(dest5, "Simon") == 0);
}

void StrcatTestDrive() {
  char dest[100] = "Hello";
  const char *src = " world!";

  Strcat(dest, src);
  assert(Strcmp(dest, "Hello world!") == 0);

  Strcat(dest, "");
  assert(Strcmp(dest, "Hello world!") == 0);

  char empty_dest[1] = "";
  assert(Strcmp(Strcat(empty_dest, src), " world!") == 0);
}

void StrncatTestDrive() {
  char str1[20] = "Hello";
  char str2[20] = "World";

  Strncat(str1, str2, 3);
  assert(Strcmp(str1, "HelloWor") == 0);

  Strncat(str1, str2, 10);
  assert(Strcmp(str1, "HelloWorWorld") == 0);

  Strncat(str1, "", 5);
  assert(Strcmp(str1, "HelloWorWorld") == 0);
}

void StrchrTestDrive() {
  char str[20] = "Hello ";
  assert(Strchr(str, 'H') == str);
  assert(Strchr(str, 'e') == str + 1);
  assert(Strchr(str, 'l') == str + 2);
  assert(Strchr(str, 'A') == nullptr);
  assert(Strchr(str, ' ') == str + Strlen(str) - 1);
  assert(Strchr(str, '\0') == str + Strlen(str));
}

void StrrchrTestDrive() {
  char str[20] = "Hello e";
  assert(Strrchr(str, 'H') == str);
  assert(Strrchr(str, 'e') == str + Strlen(str) - 1);
  assert(Strrchr(str, 'l') == str + 3);
  assert(Strrchr(str, 'A') == nullptr);
  assert(Strrchr(str, '\0') == str + Strlen(str));
}

void StrspnTestDrive() {
  char str1[20] = "Hello";
  char str2[20] = "Hllo";

  assert(Strspn(str1, str2) == 1);
  assert(Strspn(str1, "") == 0);
  assert(Strspn("", str2) == 0);
}

void StrcspnTestDrive() {
  char str1[20] = "Hello";
  char str2[20] = "Hllo";

  assert(Strcspn(str1, str2) == 0);
  assert(Strcspn(str1, "") == 5);
  assert(Strcspn("", str2) == 0);
}

void StrpbrkTestDrive() {
  char str1[20] = "Hello";
  char str2[20] = "Hllo";
  char str3[20] = "l";

  assert(Strpbrk(str1, str2) == str1);
  assert(Strpbrk(str1, str3) == str1 + 2);
}

void StrstrTestDrive() {
  char str1[20] = "Hello";
  char str2[20] = "ll";
  char str3[20] = "llo";
  char str4[20] = "ad";

  assert(Strcmp(Strstr(str1, str2), "llo") == 0);
  assert(Strstr(str1, "") == str1);
  assert(Strcmp(Strstr(str1, str3), "llo") == 0);
  assert(Strstr(str1, str4) == nullptr);
}

int main() {
  StrcmpTestDrive();
  StrlenTestDrive();
  StrcpyTestDrive();
  StrncpyTestDrive();
  StrcatTestDrive();
  StrncatTestDrive();
  StrchrTestDrive();
  StrrchrTestDrive();
  StrspnTestDrive();
  StrcspnTestDrive();
  StrpbrkTestDrive();
  StrstrTestDrive();

  return 0;
}
