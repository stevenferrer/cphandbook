#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
  int u, v, weight;
  bool operator<(const Edge& other) const { return weight < other.weight; }
};

int find_set(vector<int>& parent, int v) {
  if (v == parent[v]) {
    return v;
  }
  return find_set(parent, parent[v]);
}

// union by size/rank
void union_set(vector<int>& parent, vector<int>& size, int a, int b) {
  a = find_set(parent, a);
  b = find_set(parent, b);
  if (a == b) {
    return;
  }

  // the smaller component shall be
  // linked to the larger component
  if (size[a] < size[b]) {
    swap(a, b);
  }

  parent[b] = a;
  size[a] += size[b];
}

vector<Edge> kruskal(vector<Edge>& edges, int n) {
  vector<int> parent(n + 1), size(n + 1);
  for (int i = 1; i <= n; ++i) {
    parent[i] = i;
    size[i] = 1;
  }

  // sort the edges by weight
  sort(edges.begin(), edges.end());

  vector<Edge> mst;

  for (auto edge : edges) {
    int a = find_set(parent, edge.u);
    int b = find_set(parent, edge.v);
    if (a == b) {
      continue;
    }

    mst.push_back(edge);
    union_set(parent, size, a, b);
  }

  return mst;
}

int main() {
  int n = 6;
  vector<Edge> edges = {
      {1, 5, 5}, //
      {1, 2, 3}, //
      {2, 5, 6}, //
      {2, 3, 5}, //
      {3, 4, 9}, //
      {3, 6, 3}, //
      {4, 6, 7}, //
      {5, 6, 2}, //
  };

  cout << "Kruskal's algorithm:\n";
  auto mst = kruskal(edges, n);

  int total_cost = 0;
  for (auto edge : mst) {
    cout << edge.u << "->" << edge.v << endl;
    total_cost += edge.weight;
  }

  cout << "Total cost: " << total_cost << endl;
}
