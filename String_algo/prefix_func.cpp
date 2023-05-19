#include <string>
#include <vector>
#include <iostream>

std::vector<int> PrefixFunction(std::string &str) {
  std::vector<int> p(str.size(), 0);

  for (size_t i = 1; i < str.size(); ++i) {
    int k = p[i - 1];

    while (k > 0 && str[i] != str[k]) {
      k = p[k - 1];
    }

    if (str[i] == str[k]) {
      p[i] = k + 1;
    }
  }

  return p;
}

int main() {
  std::string str;
  std::cin >> str;

  for (auto i : PrefixFunction(str)) {
    std::cout << i << " ";
  }

  return 0;
}