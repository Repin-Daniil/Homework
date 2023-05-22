#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

enum Color { WHITE, GREY, BLACK };
struct Vertex {
  int index = -1;
  int time_in = 0;
  int time_up = 0;
  Color color = WHITE;
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
      if (vertex.color == WHITE) {
        DFS(vertex);
      }
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:

  vector<Vertex> vertexes_;
//  std::unordered_set<int> articulation_points_set_;

  // Methods
  void DFS(Vertex &v) {
//    v.visited = true;
    v.color = GREY;
    v.time_in = v.time_up = ++Vertex::time;

    for (auto x : v.edges) {
      if (v.index == vertexes_[x].index) {
        continue;
      }

//      if (vertexes_[x].visited) {
      if (vertexes_[x].color == GREY) {
        v.time_up = std::min(v.time_up, vertexes_[x].time_in);
      }
      if (vertexes_[x].color == WHITE) {
        DFS(vertexes_[x]);
        v.time_up = std::min(v.time_up, vertexes_[x].time_up);

        if (v.time_in < vertexes_[x].time_up) {
//          articulation_points_set_.insert(std::pair<int, int>);
          std::cout << v.index + 1 << ' ' << vertexes_[x].index + 1 << '\n';
        }
      }
    }
    v.color = BLACK;
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

