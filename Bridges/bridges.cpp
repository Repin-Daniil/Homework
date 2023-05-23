#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_set>

using std::vector;
struct Edge {
  int start = -1;
  int finish = -1;
  int number = -1;
  bool is_parallel = false;
};

struct pair_hash {
  inline std::size_t operator()(const std::pair<int, int> &v) const {
    return v.first * 31 + v.second;
  }
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

  void FindBridges() {
    for (auto &vertex : vertexes_) {
      if (vertex.color == WHITE) {
        DFS(vertex, 0);
      }
    }
    std::vector<int> ans;
    for (auto x : bridges) {
      for (auto y : edges_) {
        if (y.start == x.first && y.finish == x.second && !y.is_parallel) {
          ans.push_back(y.number);
        }
      }
    }
    std::cout << ans.size() << '\n';
    for(auto x : ans) {
      std::cout << x << '\n';
    }
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  vector<Vertex> vertexes_;
  std::set<std::pair<int, int>> bridges;
  int edges_amount = 0;
  std::vector<Edge> edges_;

  std::unordered_set<std::pair<int, int>, pair_hash> edges_set_;
  // Methods
  void DFS(Vertex &curr, int ancestor) {
    curr.color = GREY;
    curr.time_in = curr.time_up = ++Vertex::time;

    for (auto x : curr.edges) {
      if (x == ancestor) {
        if (bridges.count({std::min(curr.index, ancestor), std::max(curr.index, ancestor)})) {
          bridges.erase({std::min(curr.index, ancestor), std::max(curr.index, ancestor)});
        }
        continue;//Добавить проверку на наличие в bridges чтобы удалить если что
      }

      if (vertexes_[x].color == GREY) {
        curr.time_up = std::min(curr.time_up, vertexes_[x].time_in);
      }

      if (vertexes_[x].color == WHITE) {
        DFS(vertexes_[x], curr.index);
        curr.time_up = std::min(curr.time_up, vertexes_[x].time_up);

        if (curr.time_in < vertexes_[x].time_up) {

          bridges.insert({std::min(curr.index, x), std::max(curr.index, x)});
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

  bool is_parallel = g.edges_set_.count({std::min(begin, end), std::max(begin, end)});
  ++g.edges_amount;
  g.edges_set_.insert({begin, end});
  g.edges_[g.edges_amount] = {std::min(begin, end), std::max(begin, end), g.edges_amount};
  g.edges_[g.edges_amount].is_parallel = is_parallel;


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

  g.FindBridges();
  return 0;
}
