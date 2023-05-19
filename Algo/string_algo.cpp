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

std::vector<int> ZFunction(std::string &str) {
  std::vector<int> z(str.size(), 0);
  int left = 0;
  int right = 0;
  int len = str.size();
  z[0] = len;

  for (int i = 1; i < len; ++i) {
    if (i <= right) {
      z[i] = std::min(z[i - left], right - i);
    }

    while (i + z[i] < len && str[z[i]] == str[i + z[i]]) {
      ++z[i];
    }

    if (right < i + z[i]) {
      left = i;
      right = i + z[i];
    }
  }

  return z;
}

int main() {
  std::string str;
  std::cin >> str;

  for (auto i : ZFunction(str)) {
    std::cout << i << " ";
  }

  return 0;
}