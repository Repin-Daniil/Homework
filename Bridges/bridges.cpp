#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>
#include <map>

using std::vector;
struct Edge {
  int start;
  int finish;
  bool is_parallel = false;
};

enum Color { WHITE, GREY, BLACK };
struct Vertex {
  int index = -1;
  int time_in = 0;
  int time_up = 0;
  Color color = WHITE;
  std::unordered_set<int> edges;
  static int time;
};

int Vertex::time;

class Graph {
 public:
  explicit Graph(int n, int e) {
    Vertex::time = 0;
    vertexes_ = vector<Vertex>(n);
    edges_ = vector<Edge>(e);
  }

  void PrintArticulationPoints() {
    for (auto &vertex : vertexes_) {
      if (vertex.color == WHITE) {
        DFS(vertex, vertexes_[0]);
      }
    }
    std::cout << bridges.size() << '\n';
    for(auto x : bridges) {
      std::cout << x.first + 1 << ' ' << x.second + 1 << '\n';
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  vector<Vertex> vertexes_;
  std::set<std::pair<int, int>> bridges;
  std::vector<Edge> edges_;
  // Methods
  void DFS(Vertex &curr, Vertex &ancestor) {
    curr.color = GREY;
    curr.time_in = curr.time_up = ++Vertex::time;

    for (auto x : curr.edges) {
      if (x == ancestor.index) {
        continue;
      }

      if (vertexes_[x].color == GREY) {
        curr.time_up = std::min(curr.time_up, vertexes_[x].time_in);
      }

      if (vertexes_[x].color == WHITE) {
        DFS(vertexes_[x], curr);
        curr.time_up = std::min(curr.time_up, vertexes_[x].time_up);

        if (curr.time_in < vertexes_[x].time_up) {

          bridges.insert({curr.index, x});
        }
      }
    }

    curr.color = BLACK;
  }
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end;
  is >> begin >> end;
  --begin;
  --end;
  g.edges_.push_back({std::min(begin, end), std::max(begin, end)})
  g.vertexes_[begin].index = begin;
  g.vertexes_[end].index = end;
  g.vertexes_[begin].edges.insert(end);
  g.vertexes_[end].edges.insert(begin);

  return is;
}

int main() {
  int v, e;
  std::cin >> v >> e;
  Graph g(v, e);

  for (int i = 0; i < e; ++i) {
    std::cin >> g;
  }

  g.PrintArticulationPoints();
  return 0;
}
