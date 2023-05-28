#include <iostream>
#include <vector>
#include <unordered_set>

class Graph {
 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
    parents_ = std::vector<int>(n, -1);
  }

  void FindCycle() {
    std::vector<Color> visited = std::vector<Color>(vertexes_.size(), WHITE);

    for (size_t i = 0; i < vertexes_.size(); ++i) {
      if (has_cycle_) {
        return;
      }

      DFS(i, visited);
    }

    std::cout << "NO";
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> parents_;
  bool has_cycle_ = false;
  enum Color { WHITE, GREY, BLACK };

  void PrintCycle(int start, int curr) {
    if (start != curr) {
      PrintCycle(start, parents_[curr]);
    }

    std::cout << curr + 1 << ' ';
  }

  void DFS(size_t vertex, std::vector<Color> &visited) {
    visited[vertex] = GREY;

    for (auto neighbour : vertexes_[vertex]) {
      if (has_cycle_) {
        break;
      }

      if (visited[neighbour] == GREY) {
        std::cout << "YES\n";
        PrintCycle(neighbour, vertex);
        has_cycle_ = true;
      } else if (visited[neighbour] == WHITE) {
        parents_[neighbour] = vertex;
        DFS(neighbour, visited);
      }
    }

    visited[vertex] = BLACK;
  }
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;
  g.vertexes_[begin].insert(end);
  return is;
}

int main() {
  int v, e;
  std::cin >> v >> e;
  Graph g(v);

  for (int i = 0; i < e; ++i) {
    std::cin >> g;
  }

  g.FindCycle();
  return 0;
}
