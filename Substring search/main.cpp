#include <iostream>
#include <string>
#include <vector>

using std::vector;

using std::string;

bool IsPossible(string &str, int n) {
  vector<int> p(str.size(), 0);

  for (size_t i = 1; i < str.size(); ++i) {
    int k = p[i - 1];

    while (k > 0 && str[i] != str[k]) {
      k = p[k - 1];
    }

    if (str[i] == str[k]) {
      p[i] = k + 1;

      if (n == p[i]) {
        return true;
      }
    }
  }

  return false;
}

string Predict(string &before_rotation, string &after_rotation) {
  if (before_rotation == after_rotation) {
    return "Random";
  }

  bool bad_case, good_case;

  {
    string loaded = before_rotation + "#" + after_rotation + "1" + after_rotation;
    bad_case = IsPossible(loaded, before_rotation.size());
  }

  {
    string unloaded = before_rotation + "#" + after_rotation + "0" + after_rotation;
    good_case = IsPossible(unloaded, before_rotation.size());
  }

  if (bad_case && good_case) {
    return "Random";
  }

  return good_case ? "No" : "Yes";
}

int main() {
  int n;
  string before_rotation, after_rotation;

  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  std::cin >> n >> before_rotation >> after_rotation;
  std::cout << Predict(before_rotation, after_rotation);

  return 0;
}
