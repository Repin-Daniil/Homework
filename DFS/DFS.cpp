#include <iostream>
#include <vector>
#include <unordered_set>

class Graph {
 public:
  explicit Graph(int n) {
    vertexes_ = std::vector<std::unordered_set<int>>(n);
  }

  void FindCycle() {
    std::vector<Color> visited = std::vector<Color>(vertexes_.size(), WHITE);

    for (size_t i = 0; i < vertexes_.size(); ++i) {
      DFS(i, visited);
      if (!cycle_.empty()) {
        break;
      }
    }

    if (cycle_.empty()) {
      std::cout << "NO";
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  std::vector<std::unordered_set<int>> vertexes_;
  std::vector<int> cycle_;
  enum Color { WHITE, GREY, BLACK };

  struct CycleEx {
    size_t cycle_start;
    explicit CycleEx(int cycle_start) : cycle_start(cycle_start) {
    }
  };

  void DFS(size_t vertex, std::vector<Color> &visited) {
    visited[vertex] = GREY;

    for (auto neighbour : vertexes_[vertex]) {
      if (visited[neighbour] == GREY) {
        cycle_ = std::vector<int>();
        cycle_.push_back(vertex);
        throw CycleEx(neighbour);
      }

      if (visited[neighbour] == WHITE) {
        if (cycle_.empty()) {
          try {
            DFS(neighbour, visited);
          } catch (CycleEx &ex) {
            cycle_.push_back(vertex);
            if (vertex == ex.cycle_start) {
              std::cout << "YES\n";

              for (size_t i = 1; i <= cycle_.size(); ++i) {
                std::cout << cycle_[cycle_.size() - i] + 1 << ' ';
              }
              break;
            }
            throw;
          }
        } else {
          break;
        }
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