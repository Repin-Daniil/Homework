#include "cstring.h"

size_t Strlen(const char *str) {
  size_t i = 0;

  while (str[i]) {
    ++i;
  }

  return i;
}

int Strcmp(const char *first, const char *second) {
  while (*first && *second && (*first == *second)) {
    ++first;
    ++second;
  }

  return *first - *second;
}

int Strncmp(const char *first, const char *second, size_t count) {
  while (count > 0 && *first && *second && (*first == *second)) {
    ++first;
    ++second;
    --count;
  }

  return ((count == 0) ? 0 : (*first - *second));
}

char *Strcpy(char *dest, const char *src) {
  char *str = dest;

  while (*src) {
    *str = *src;
    ++src;
    ++str;
  }

  *str = *src;
  return dest;
}

char *Strncpy(char *dest, const char *src, size_t count) {
  char *str = dest;

  while (*src && (count > 0)) {
    *str = *src;
    ++src;
    ++str;
    --count;
  }

  while (count > 0) {
    *str = *src;
    ++str;
    --count;
  }

  return dest;
}

char *Strcat(char *dest, const char *src) {
  Strcpy(dest + Strlen(dest), src);
  return dest;
}

char *Strncat(char *dest, const char *src, size_t count) {
  if (count > Strlen(src)) {
    return Strcat(dest, src);
  }

  if (*src && count != 0) {
    Strncpy(dest + Strlen(dest), src, count);
  }
  return dest;
}

const char *Strchr(const char *str, char symbol) {
  while (*str != symbol && *str) {
    ++str;
  }

  return (*str == symbol ? str : nullptr);
}

const char *Strrchr(const char *str, char symbol) {
  const char *last_occurrence = nullptr;

  while (*str) {
    if (*str == symbol) {
      last_occurrence = str;
    }

    ++str;
  }

  return ((symbol == '\0') ? str : last_occurrence);
}

size_t Strspn(const char *dest, const char *src) {
  size_t counter = 0;

  while (*dest) {
    const char *result = Strchr(src, *dest);

    if (result == nullptr) {
      return counter;
    }

    ++counter;
    ++dest;
  }

  return counter;
}

size_t Strcspn(const char *dest, const char *src) {
  size_t counter = 0;

  while (*dest) {
    if (Strchr(src, *dest) != nullptr) {
      return counter;
    }

    ++counter;
    ++dest;
  }

  return counter;
}

const char *Strpbrk(const char *dest, const char *breakset) {
  while (*dest) {
    if (Strchr(breakset, *dest) != nullptr) {
      return dest;
    }

    ++dest;
  }

  return nullptr;
}

const char *Strstr(const char *str, const char *pattern) {
  if (*pattern == 0) {
    return str;
  }

  while (*str) {
    if (*str == *pattern && Strncmp(str, pattern, Strlen(pattern)) == 0) {
      return str;
    }

    ++str;
  }

  return nullptr;
}