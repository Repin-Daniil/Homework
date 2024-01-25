#define CATCH_CONFIG_MAIN

#include <catch.hpp>

#include "cstring.h"
#include "cstring.h" // check include guards

TEST_CASE("Strlen", "[CString]") {
  const char *string_1 = "testword";
  const char *string_2 = "";
  const char *string_3 = " ";
  const char *string_4 = "\0";

  CHECK(Strlen(string_1) == 8);
  CHECK(Strlen(string_2) == 0);
  CHECK(Strlen(string_3) == 1);
  CHECK(Strlen(string_4) == 0);
}

TEST_CASE("Strcmp", "[CString]") {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  const char *str3 = "World";
  const char *str4 = "hello";
  const char *str5 = "Hello world!";
  const char *str6 = "Hello";
  const char *str7 = "";

  CHECK(Strcmp(str1, str2) == 0);
  CHECK(Strcmp(str1, str3) < 0);
  CHECK(Strcmp(str1, str4) < 0);
  CHECK(Strcmp(str1, str5) < 0);
  CHECK(Strcmp(str1, str6) == 0);
  CHECK(Strcmp(str1, str7) > 0);
}

TEST_CASE("Strncmp", "[CString]") {
  CHECK(Strncmp("abcd", "abce", 3) == 0);
  CHECK(Strncmp("hello", "help", 3) == 0);
  CHECK(Strncmp("hello", "help", 4) < 0);
  CHECK(Strncmp("help", "hello", 4) > 0);
  CHECK(Strncmp("hello", "hello", 5) == 0);
  CHECK(Strncmp("hello", "world", 1) < 0);
  CHECK(Strncmp("world", "hello", 1) > 0);
  CHECK(Strncmp("hello", "world", 0) == 0);
}

TEST_CASE("Strcpy", "[CString]") {
  char str1[20] = "Hello";
  char str2[20] = "World";

  CHECK(Strcmp(Strcpy(str1, str2), "World") == 0);
  CHECK(Strcmp(Strcpy(str1, "World"), "World") == 0);
  CHECK(Strcmp(Strcpy(str2, ""), "") == 0);
  CHECK(Strcmp(Strcpy(str2, ""), "") == 0);
}

TEST_CASE("Strncpy", "[CString]") {
  char src1[] = "Hello world";
  char dest1[20];
  Strncpy(dest1, src1, 11);
  CHECK_THAT(dest1, Catch::Matchers::Equals("Hello world"));

  char src2[] = "";
  char dest2[20];
  Strncpy(dest2, src2, 5);
  CHECK(Strcmp(dest2, "") == 0);

  char src3[] = "Hello world";
  char dest3[20];
  Strncpy(dest3, src3, 15);
  CHECK(Strcmp(dest3, "Hello world") == 0);

  char src4[] = "Simon";
  char dest4[] = "Hello world";
  Strncpy(dest4, src4, 8);
  CHECK(Strcmp(dest4, "Simon") == 0);
}

TEST_CASE("Strcat", "[CString]") {
  char dest[100] = "Hello";
  const char *src = " world!";

  Strcat(dest, src);
  CHECK(Strcmp(dest, "Hello world!") == 0);

  Strcat(dest, "");
  CHECK(Strcmp(dest, "Hello world!") == 0);

  char empty_dest[1] = "";
  CHECK(Strcmp(Strcat(empty_dest, src), " world!") == 0);
}

TEST_CASE("Strncat", "[CString]") {
  char str1[20] = "Hello";
  char str2[20] = "World";

  Strncat(str1, str2, 3);
  CHECK(Strcmp(str1, "HelloWor") == 0);

  Strncat(str1, str2, 10);
  CHECK(Strcmp(str1, "HelloWorWorld") == 0);

  Strncat(str1, "", 5);
  CHECK(Strcmp(str1, "HelloWorWorld") == 0);
}

TEST_CASE("Strchr", "[CString]") {
  char str[20] = "Hello ";
  CHECK(Strchr(str, 'H') == str);
  CHECK(Strchr(str, 'e') == str + 1);
  CHECK(Strchr(str, 'l') == str + 2);
  CHECK(Strchr(str, 'A') == nullptr);
  CHECK(Strchr(str, ' ') == str + Strlen(str) - 1);
  CHECK(Strchr(str, '\0') == str + Strlen(str));
}

TEST_CASE("Strrchr", "[CString]") {
  char str[20] = "Hello e";
  CHECK(Strrchr(str, 'H') == str);
  CHECK(Strrchr(str, 'e') == str + Strlen(str) - 1);
  CHECK(Strrchr(str, 'l') == str + 3);
  CHECK(Strrchr(str, 'A') == nullptr);
  CHECK(Strrchr(str, '\0') == str + Strlen(str));
}

TEST_CASE("Strspn", "[CString]") {
  char str1[20] = "Hello";
  char str2[20] = "Hllo";

  CHECK(Strspn(str1, str2) == 1);
  CHECK(Strspn(str1, "") == 0);
  CHECK(Strspn("", str2) == 0);
}

TEST_CASE("Strcspn", "[CString]") {
  char str1[20] = "Hello";
  char str2[20] = "Hllo";

  CHECK(Strcspn(str1, str2) == 0);
  CHECK(Strcspn(str1, "") == 5);
  CHECK(Strcspn("", str2) == 0);
}

TEST_CASE("Strpbrk", "[CString]") {
  char str1[20] = "Hello";
  char str2[20] = "Hllo";
  char str3[20] = "l";

  CHECK(Strpbrk(str1, str2) == str1);
  CHECK(Strpbrk(str1, str3) == str1 + 2);
}

TEST_CASE("Strstr", "[CString]") {
  char str1[20] = "Hello";
  char str2[20] = "ll";
  char str3[20] = "llo";
  char str4[20] = "ad";

  CHECK(Strcmp(Strstr(str1, str2), "llo") == 0);
  CHECK(Strstr(str1, "") == str1);
  CHECK(Strcmp(Strstr(str1, str3), "llo") == 0);
  CHECK(Strstr(str1, str4) == nullptr);
}
