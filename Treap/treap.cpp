#include <iostream>
#include <vector>

struct Node {
  int key;
  int priority;

  Node *left = nullptr;
  Node *right = nullptr;
  Node *parent = nullptr;

  Node(int key, int priority) : key(key), priority(priority) {}
};

using pair = std::pair<Node *, Node *>;
pair Split(Node *root, int key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }

  if (root->key < key) {
    pair res = Split(root->right, key);
    root->right = res.first;
    res.second->parent = nullptr;
    return {root, res.second};
  }

  pair res = Split(root->left, key);
  root->left = res.second;
  res.first->parent = nullptr;
  return {res.first, root};
}

Node *Merge(Node *first, Node *second) {
  if (first == nullptr) {
    return second;
  }

  if (second == nullptr) {
    return first;
  }

  if (first->priority > second->priority) {
    Node *res = Merge(first->right, second);
    first->right = res;
    res->parent = first;
    return first;
  }

  Node *res = Merge(first, second->left);
  second->left = res;
  res->parent = second;
  return second;
}

Node *Insert(Node *root, int key, int priority) {
  auto node = new Node(key, priority);
  pair separated = Split(root, key);
  Node *res = Merge(node, separated.second);
  return Merge(separated.first, res);
}

Node *Erase(Node *root, int key) {
  pair separated = Split(root, key);
  pair min_right = Split(separated.second, key + 1);
  return Merge(separated.first, min_right.first);
}

Node *Build(std::vector<std::pair<int, int>> &values) {
  Node *root = nullptr;
  Node *last_inserted = nullptr;

  for (auto value : values) {
    auto new_node = new Node(value.first, value.second);
    Node *curr = last_inserted;

    while (curr != nullptr && value.second < curr->priority) {
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

void PrintTreap(Node *root) {
  if (root != nullptr) {
    std::cout << (root->parent != nullptr ? root->parent->key : 0) << ' '
              << (root->left != nullptr ? root->left->key : 0) << ' '
              << (root->right != nullptr ? root->right->key : 0) << '\n';
    PrintTreap(root->left);
    PrintTreap(root->right);
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> values(n);

  for (int i = 0; i < n; ++i) {
    int first, second;
    std::cin >> first >> second;
    values[i] = {first, second};
  }

  Node *root = Build(values);
  std::cout << "YES\n";
  PrintTreap(root);
  return 0;
}