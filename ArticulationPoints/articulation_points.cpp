#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using std::vector;

struct Vertex {
  int index = -1;
  int time_in = 0;
  int time_up = 0;
  bool visited = false;
  vector<int> edges;
  static int time;
};

int Vertex::time;

class Graph {
 public:
  explicit Graph(int n) {
    Vertex::time = 0;
    vertexes_ = vector<Vertex>(n);
  }

  void PrintArticulationPoints() {
    for (auto &vertex : vertexes_) {
      if (!vertex.visited) {
        DFS(vertex, true);
      }
    }

    std::cout << articulation_points_set_.size() << '\n';

    for (auto point : articulation_points_set_) {
      std::cout << point + 1 << '\n';
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  vector<Vertex> vertexes_;
  std::set<int> articulation_points_set_;

  // Methods
  void DFS(Vertex &v, bool is_root) {
    v.visited = true;
    v.time_in = v.time_up = ++Vertex::time;
    int children_amount = 0;

    for (auto x : v.edges) {
      if (vertexes_[x].visited) {
        v.time_up = std::min(v.time_up, vertexes_[x].time_in);
      } else {
        ++children_amount;
        DFS(vertexes_[x], false);
        v.time_up = std::min(v.time_up, vertexes_[x].time_up);

        if (!is_root && v.time_in <= vertexes_[x].time_up) {
          articulation_points_set_.insert(v.index);
        }
      }
    }

    if (is_root && children_amount > 1) {
      articulation_points_set_.insert(v.index);
    }
  }
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;

  g.vertexes_[begin].index = begin;
  g.vertexes_[end].index = end;
  g.vertexes_[begin].edges.push_back(end);
  g.vertexes_[end].edges.push_back(begin);

  return is;
}

int main() {
  int v, e;
  std::cin >> v >> e;
  Graph g(v);

  for (int i = 0; i < e; ++i) {
    std::cin >> g;
  }

  g.PrintArticulationPoints();
  return 0;
}
