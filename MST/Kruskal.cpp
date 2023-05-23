#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

class CDS {
 public:
  explicit CDS(int n) : parents_(n), rank_(n, 0) {
    for (int i = 0; i < n; ++i) {
      parents_[i] = i;
    }
  }

  int FindSet(int x) {
    if (x == parents_[x]) {
      return x;
    }

    return parents_[x] = FindSet(parents_[x]);
  }

  void Union(int x, int y) {
    x = FindSet(x);
    y = FindSet(y);

    if (rank_[x] < rank_[y]) {
      parents_[x] = y;
    } else if (rank_[x] > rank_[y]) {
      parents_[y] = x;
    } else {
      parents_[x] = y;
      ++rank_[y];
    }
  }

 private:
  vector<int> parents_;
  vector<int> rank_;
};

class Graph {
 public:
  int GetMinWeight() {
    CDS cds(edges_.size());
    int sum = 0;

    for (auto edge : edges_) {
      if (cds.FindSet(edge.begin) != cds.FindSet(edge.end)) {
        cds.Union(edge.begin, edge.end);
        sum += edge.weight;
      }
    }

    return sum;
  }

  friend std::istream &operator>>(std::istream &is, Graph &g);

 private:
  struct Edge {
    int begin;
    int end;
    int weight;

    bool operator<(const Edge &other) const {
      return weight < other.weight;
    }
  };

  vector<Edge> edges_;
};

std::istream &operator>>(std::istream &is, Graph &g) {
  int begin, end, weight;
  is >> begin >> end >> weight;
  --begin;
  --end;

  g.edges_.push_back({begin, end, weight});
  return is;
}

int main() {
  int v, e;
  Graph g;

  std::ios_base::sync_with_stdio(false);
  std::cin >> v >> e;

  for (int i = 0; i < e; ++i) {
    std::cin >> g;
  }

  std::cout << g.GetMinWeight();
  return 0;
}
