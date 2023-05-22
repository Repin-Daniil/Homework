#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using std::vector;

enum Color { WHITE, GREY, BLACK };
struct Vertex {
  int index;
  int time_in;
  int time_up;
  bool visited = false;
  vector<int> edges;
  static int time;
};

int Vertex::time;

class Graph {
 public:

  explicit Graph(int n) {
    Vertex::time = 0;
    vertexes_ = vector<vector<Vertex>>(n);
  }

  void PrintArticulationPoints() {
    DFS(vertexes_[0][0], true);
    std::cout << articulation_points_.size() << '\n';

    for (auto point : articulation_points_) {
      std::cout << point + 1 << '\n';
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:

  vector<vector<Vertex>> vertexes_;
  std::unordered_set<int> articulation_points_;

  // Methods
  void DFS(Vertex &v, bool is_root) {
    v.visited = true;
    v.time_in = v.time_up = ++Vertex::time;
    int children_amount = 0;

    for (auto neighbour : vertexes_[v.index]) {
      if (neighbour.visited) {
        v.time_up = std::min(v.time_up, neighbour.time_in);
      } else {
        ++children_amount;
        DFS(neighbour, false);
        v.time_up = std::min(v.time_up, neighbour.time_up);

        if (!is_root && v.time_in <= neighbour.time_up) {
          articulation_points_.insert(v.index);
        }
      }
    }
    if (is_root && children_amount > 1) {
      articulation_points_.insert(v.index);
    }
  }
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;
  g.vertexes_[begin].push_back({end, 0, 0});
  g.vertexes_[end].push_back({begin, 0, 0});
  return is;
}

int main() {
  int v, e;
  std::cin >> e >> v;
  Graph g(v);

  for (int i = 0; i < e; ++i) {
    std::cin >> g;
  }

  g.PrintArticulationPoints();
}
