#include <iostream>
#include <vector>
#include <memory>

struct Node {
  int key = -1;
  int priority = -1;
  int number = -1;
  std::shared_ptr<Node> left;
  std::shared_ptr<Node> right;
  std::weak_ptr<Node> parent;

  Node() = default;
  Node(int key, int priority, int number) : key(key), priority(priority), number(number) {
  }
};

std::shared_ptr<Node> Build(std::vector<std::pair<int, int>> &values, std::vector<std::shared_ptr<Node>> &ans) {
  std::shared_ptr<Node> root;
  std::shared_ptr<Node> last_inserted;

  for (size_t i = 0; i < values.size(); ++i) {
    auto value = values[i];
    std::shared_ptr<Node> new_node = std::make_shared<Node>(value.first, value.second, i + 1);
    ans.push_back(new_node);
    std::shared_ptr<Node> curr = last_inserted;

    while (curr != nullptr && new_node->priority < curr->priority) {
      curr = curr->parent.lock();
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
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::ios_base::sync_with_stdio(false);
  for (int i = 0; i < n; ++i) {
    int first, second;
    std::cin >> first >> second;
    values[i] = {first, second};
  }

  std::vector<std::shared_ptr<Node>> ans;
  std::shared_ptr<Node> root = Build(values, ans);

  std::cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    std::cout << (!(ans[i]->parent).expired() ? ans[i]->parent.lock()->number : 0) << ' ';
    std::cout << (ans[i]->left != nullptr ? ans[i]->left->number : 0) << ' ';
    std::cout << (ans[i]->right != nullptr ? ans[i]->right->number : 0) << '\n';
  }
  return 0;
}
