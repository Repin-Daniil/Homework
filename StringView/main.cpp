#include <iostream>
#include <cstring>
#include <cassert>
#include "string_view.h"

void Print(StringView str) {
  for (int i = 0; i < str.Size(); ++i) {
    std::cout << str[i];
  }

  std::cout << '\n';
}

void SubStrTestDrive() {
  std::cout << "SubStrTestDrive\n";
  StringView data{"ABCDEF"};

  Print(data.Substr(0)); // ABCDEF, i.e. data[0, 5] that is [0, 6)
  Print(data.Substr(1)); // BCDEF, i.e. [1, 6)
  Print(data.Substr(2, 3)); // CDE, i.e. [2, 2+3)
  Print(data.Substr(4, 42)); // EF, i.e. [4, 6)
  std::cout << '\n';
}

void OperTestDrive() {
  char *str = "Example";
  StringView v(str);
  assert(v[2] == 'a');
}

void AtTestDrive() {
  const char *str = "abcdef";
  StringView str_view("abcdef");

  try {
    for (std::size_t i = 0; true; ++i)
      assert(str_view.At(i) == str[i]);
  }
  catch (StringViewOutOfRange e) {
    return;
  }
  assert(false);
}

void RemovePrefixTestDrive() {
  std::cout << "RemovePrefixTestDrive\n";

  for (StringView str{"ABCDEF"}; !str.Empty(); str.RemovePrefix(1))
    std::cout << str.Front() << ' ' << str.Length() << '\n';

  std::cout << "\n";
}

void RemoveSuffixTestDrive() {
  std::cout << "RemoveSuffixTestDrive\n";

  for (StringView str{"ABCDEF"}; !str.Empty(); str.RemoveSuffix(1))
    std::cout << str.Back() << ' ' << str.Length() << '\n';

  std::cout << "\n";
}

void DataTestDrive() {
  StringView wcstr_v = "xyzzy";
  assert(std::strlen(wcstr_v.Data()) == 5);

  char array[3] = {'B', 'a', 'r'};
  StringView array_v(array, sizeof array);

  std::string str(array_v.Data(), array_v.Size());
  assert(std::strlen(str.data()) == 3);
}
void SmokeTest() {
  const char *cstyle = "very_very_long_string_here";
  std::string s = cstyle;

  StringView sv(cstyle);
  std::strlen(cstyle);
  sv.Size();
}

void SwapTestDrive() {
  std::cout << "SwapTestDrive\n";
  auto s1{StringView{"aaaaa"}};
  auto s2{StringView{"bbbbb"}};

  Print(s1);
  Print(s2);
  s1.Swap(s2);
  Print(s1);
  Print(s2);

  std::cout << "\n";
}

int main() {
  SubStrTestDrive();
  OperTestDrive();
  AtTestDrive();
  RemovePrefixTestDrive();
  RemoveSuffixTestDrive();
  DataTestDrive();
  RemovePrefixTestDrive();
  SwapTestDrive();
  SmokeTest();

  return 0;
}
