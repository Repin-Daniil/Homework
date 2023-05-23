#include <iostream>
#include <vector>

struct Node {
  int key = -1;
  int priority = -1;

  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;

  void Set(int x, int y) {
    key = x;
    priority = y;
  }
};

Node *Build(std::vector<std::pair<int, int>> &values, Node *nodes) {
  Node *root = nullptr;
  Node *last_inserted = nullptr;

  for (size_t i = 0; i < values.size(); ++i) {
    auto value = values[i];
    Node *new_node = nodes + i;
    new_node->Set(value.first, value.second);
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

  return root;
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

  Build(values, nodes);

  std::cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    std::cout << (nodes[i].parent != nullptr ? nodes[i].parent->key + 1: 0) << ' ';
    std::cout << (nodes[i].left != nullptr ? nodes[i].left->key + 1 : 0) << ' ';
    std::cout << (nodes[i].right != nullptr ? nodes[i].right->key + 1 : 0) << '\n';
  }

  delete[] nodes;
  return 0;
}
