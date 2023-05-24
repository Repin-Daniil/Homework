#include <iostream>
#include <vector>

struct Node {
  int key = -1;
  int priority = -1;
  size_t number = -1;

  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;

  void Set(int x, int y, size_t z) {
    key = x;
    priority = y;
    number = z;
  }
};

std::vector<Node *> Build(std::vector<std::pair<int, int>> &values, Node *nodes) {
  Node *root = nullptr;
  Node *last_inserted = nullptr;
  std::vector<Node *> ans;

  for (size_t i = 0; i < values.size(); ++i) {
    Node *new_node = nodes + i;
    new_node->Set(values[i].first, values[i].second, i + 1);
    ans.push_back(new_node);
    Node *curr = last_inserted;

    while (curr != nullptr && new_node->priority < curr->priority) {
      curr = curr->parent;
    }

    if (curr == nullptr) {
      new_node->left = root;

      if (root != nullptr) {
        root->parent = new_node;
      }

      root = new_node;
    } else {
      new_node->left = curr->right;

      if (curr->right != nullptr) {
        curr->right->parent = new_node;
      }

      curr->right = new_node;
      new_node->parent = curr;
    }

    last_inserted = new_node;
  }

  return ans;
}

int main() {
  int n;
  std::cin >> n;

  std::vector<std::pair<int, int>> values(n);
  auto nodes = new Node[n];

  for (int i = 0; i < n; ++i) {
    int first, second;
    std::cin >> first >> second;
    values[i] = {first, second};
  }

  std::cout << "YES\n";
  for (auto &node : Build(values, nodes)) {
    std::cout << (node->parent != nullptr ? node->parent->number : 0) << ' ';
    std::cout << (node->left != nullptr ? node->left->number : 0) << ' ';
    std::cout << (node->right != nullptr ? node->right->number : 0) << '\n';
  }

  delete[] nodes;
  return 0;
}
