#include <iostream>
#include <vector>
#include <unordered_set>
#include <limits>
#include <queue>

class Graph {
 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    dist_ = std::vector<int>(n, inf_);
    parents_ = std::vector<int>(n, -1);
  }

  void PrintShortestPath(int start, int end) {
    BFS(start);
    int distance = dist_[end - 1];

    if (distance == inf_) {
      std::cout << -1;
      return;
    }

    std::cout << distance << '\n';
    GetPath(end - 1);
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> dist_;
  std::vector<int> parents_;
  const int inf_ = std::numeric_limits<int>::max();

  void GetPath(int n) {
    if (parents_[n] != -1) {
      GetPath(parents_[n]);
    }

    std::cout << n + 1 << ' ';
  }

  void BFS(int start) {
    --start;
    std::queue<int> q;
    q.push(start);
    dist_[start] = 0;

    while (!q.empty()) {
      int curr = q.front();
      q.pop();

      for (auto neighbour : vertexes_[curr]) {
        if (dist_[neighbour] >= dist_[curr] + 1) {
          dist_[neighbour] = dist_[curr] + 1;
          parents_[neighbour] = curr;
          q.push(neighbour);
        }
      }
    }
  }
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].insert(end);
  g.vertexes_[end].insert(begin);

  return is;
}

int main() {
  int n, m, a, b;
  std::cin >> n >> m >> a >> b;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    std::cin >> g;
  }

  g.PrintShortestPath(a, b);
  return 0;
}