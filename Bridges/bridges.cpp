#include <iostream>
#include <vector>
#include <set>
#include <map>

using std::vector;

enum Color { WHITE, GREY, BLACK };

struct Vertex {
  int index = 0;
  int time_in = 0;
  int time_up = 0;
  Color color = WHITE;
};

class Graph {
 public:
  explicit Graph(int v) {
    vertexes_ = vector<Vertex>(v);
    edges_ = vector<vector<int>>(v);
  }

  std::set<int> FindBridges() {
    for (auto &vertex : vertexes_) {
      if (vertex.color == WHITE) {
        DFS(vertex, 0);
      }
    }

    return bridges_;
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  vector<Vertex> vertexes_;
  vector<vector<int>> edges_;
  std::set<int> bridges_;
  std::map<std::pair<int, int>, int> edge_numbers_;
  int edges_counter_ = 0;
  int time_ = 0;

  void DFS(Vertex &curr, int ancestor) {
    curr.color = GREY;
    curr.time_in = curr.time_up = ++time_;

    for (auto x : edges_[curr.index]) {
      if (x == ancestor) {
        continue;
      }

      if (vertexes_[x].color == GREY) {
        curr.time_up = std::min(curr.time_up, vertexes_[x].time_in);
      }

      if (vertexes_[x].color == WHITE) {
        DFS(vertexes_[x], curr.index);
        curr.time_up = std::min(curr.time_up, vertexes_[x].time_up);

        if (curr.time_in < vertexes_[x].time_up && edge_numbers_[{curr.index, vertexes_[x].index}] != -1) {
          bridges_.insert(edge_numbers_[{curr.index, vertexes_[x].index}]);
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
  ++g.edges_counter_;

  if (begin == end) {
    // Loop
    return is;
  }

  if (g.edge_numbers_.count(std::pair(begin, end)) > 0) {
    // Multiple edge
    g.edge_numbers_[{begin, end}] = -1;
    g.edge_numbers_[{end, begin}] = -1;
    return is;
  }

  g.vertexes_[begin].index = begin;
  g.vertexes_[end].index = end;
  g.edges_[begin].push_back(end);
  g.edges_[end].push_back(begin);
  g.edge_numbers_[{begin, end}] = g.edge_numbers_[{end, begin}] = g.edges_counter_;

  return is;
}

int main() {
  int v, e;
  std::cin >> v >> e;
  Graph g(v);

  for (int i = 0; i < e; ++i) {
    std::cin >> g;
  }

  std::set<int> bridges = g.FindBridges();

  std::cout << bridges.size() << '\n';
  for (auto bridge : bridges) {
    std::cout << bridge << '\n';
  }

  return 0;
}
