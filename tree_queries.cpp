#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class FenwickTree {
public:
  FenwickTree(vector<int> arr) {
    int n = arr.size();
    t.assign(n + 1, 0);
    a.assign(n + 1, 0);

    // initialize fenwick tree
    for (int k = 1; k <= n; ++k) {
      // save original values
      a[k] = arr[k - 1];

      t[k] += a[k];
      // get parent node
      auto p = k + (k & -k);

      // only update the parent node
      if (p <= n) {
        t[p] += t[k];
      }
    }
  }

  void update(size_t k, int u) {
    add(k, u - a[k]);
    a[k] = u;
  }

  void add(size_t k, int delta) {
    // start at k and propagate values upward
    while (k < t.size()) {
      t[k] += delta;
      k += (k & -k);
    }
  }

  int sum(size_t k) {
    // sum of values from k upwards
    int s = 0;
    while (k >= 1) {
      s += t[k];
      k -= (k & -k);
    }
    return s;
  }

  int sum(size_t l, size_t r) {
    auto rsum = sum(r);
    auto lsum = sum(l - 1);
    return rsum - lsum;
  }

private:
  vector<int> t;
  vector<int> a;
};

class QueryTable {
public:
  QueryTable(const vector<pair<int, int>>& edges, size_t n,
             const vector<int>& vals)
      : n{n}, values{vals} {
    traversal.assign(n + 1, 0);
    subtree_size.assign(n + 1, 0);
    path_sum.assign(n + 1, 0);

    adj = make_adj(edges, n);
  }

  void init(int root) {
    int index = 1;
    dfs(root, 0, 0, index);
  }

  int subtree_sum(int v) {
    // TODO: save node id mapping
    int node_id = 0;
    for (size_t i = 1; i <= n; ++i) {
      if (traversal[i] == v) {
        node_id = i;
        break;
      }
    }

    int count = subtree_size[node_id];
    // e.g. if node_id=5 and count=4, then
    // the range of value should be 5 -> 8,
    // thus, 5+4=9-1=8.
    return values.sum(node_id, node_id + count - 1);
  }

  void print() {
    cout << "index:\t";
    for (size_t i = 1; i <= n; ++i) {
      cout << i << this->sep;
    }
    cout << endl;
    cout << "nodeid:\t";
    print_traversal();
    cout << "\n";
    cout << "counts:\t";
    print_counts();
    cout << "\n";
    cout << "values:\t";
    // print_vals();
    cout << "\n";
    cout << "path  :\t";
    print_path_sum();
  }

  void print_traversal() {
    for (size_t i = 1; i <= n; ++i) {
      cout << traversal[i] << this->sep;
    }
  }

  void print_counts() {
    for (size_t i = 1; i <= n; ++i) {
      cout << subtree_size[i] << this->sep;
    }
  }

  // void print_vals() {
  //   for (size_t i = 1; i <= n; ++i) {
  //     cout << values[i] << this->sep;
  //   }
  // }

  void print_path_sum() {
    for (size_t i = 1; i <= n; ++i) {
      cout << path_sum[i] << this->sep;
    }
  }

private:
  size_t n;
  string sep = "\t";
  vector<vector<int>> adj;
  vector<int> traversal;
  vector<int> subtree_size;
  FenwickTree values;
  // TODO: move path sum query to separate file.
  vector<int> path_sum;

  void dfs(int v, int p, int p_path_sum, int& index) {
    int node_id = index;
    traversal[node_id] = v;
    subtree_size[node_id] = 1;

    // path_sum[node_id] = values[v] + p_path_sum;

    for (auto u : adj[v]) {
      if (u == p) {
        continue;
      }
      int child_id = ++index;
      dfs(u, v, path_sum[node_id], index);
      subtree_size[node_id] += subtree_size[child_id];
    }
  }

  vector<vector<int>> make_adj(vector<pair<int, int>> edges, int n) {
    vector<vector<int>> adj(n + 1);
    for (auto e : edges) {
      adj[e.first].push_back(e.second);
      adj[e.second].push_back(e.first);
    }

    return adj;
  }
};

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n = 9;
  vector<pair<int, int>> edges = {
      {1, 2}, //
      {1, 3}, //
      {1, 4}, //
      {1, 5}, //
      {2, 6}, //
      {4, 7}, //
      {4, 8}, //
      {4, 9}, //
  };

  vector<int> vals = {2, 3, 4, 5, 3, 4, 3, 1, 1};
  // vector<int> vals = {4, 5, 3, 5, 2, 3, 5, 3, 1};
  QueryTable qt(edges, n, vals);
  // init and root the tree at 1
  qt.init(1);

  qt.print();
  cout << endl;

  cout << qt.subtree_sum(4) << endl;
}
