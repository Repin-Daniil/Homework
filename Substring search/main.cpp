#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;

using std::string;

vector<size_t> PrefixFunction(string &str) {
  vector<size_t> p(str.size(), 0);

  for (size_t i = 1; i < str.size(); ++i) {
    size_t k = p[i - 1];

    while (k > 0 && str[i] != str[k]) {
      k = p[k - 1];
    }

    if (str[i] == str[k]) {
      p[i] = k + 1;
    }
  }

  return p;
}

// Knuth–Morris–Pratt
bool IsPossible(string &str, size_t n) {
  vector<size_t> result = PrefixFunction(str);
  return (*std::max_element(result.begin(), result.end()) == n);
}

string Predict(string &before_rotation, string &after_rotation) {
  string loaded = before_rotation + "#" + after_rotation + "1" + after_rotation;
  string unloaded = before_rotation + "#" + after_rotation + "0" + after_rotation;

  bool bad_case = IsPossible(loaded, before_rotation.size());
  bool good_case = IsPossible(unloaded, before_rotation.size());

  if (bad_case && good_case) {
    return "Random";
  }

  return good_case ? "No" : "Yes";
}

int main() {
  int n;
  string before_rotation, after_rotation;
  std::cin >> n >> before_rotation >> after_rotation;
  std::cout << Predict(before_rotation, after_rotation);
  return 0;
}
