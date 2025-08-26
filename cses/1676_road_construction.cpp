#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int find_set(vector<int>& link, int a) {
  if (a == link[a]) {
    return a;
  }

  return link[a] = find_set(link, link[a]);
}

void union_set(vector<int>& link, vector<int>& sz, int a, int b) {
  if (sz[a] < sz[b]) {
    swap(a, b);
  }

  link[b] = a;
  sz[a] += sz[b];
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<int> link(n + 1);
  vector<int> sz(n + 1);
  for (int i = 1; i <= n; ++i) {
    link[i] = i;
    sz[i] = 1;
  }

  int comps = n, max_sz = 1;

  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;

    a = find_set(link, a);
    b = find_set(link, b);

    if (a != b) {
      union_set(link, sz, a, b);
      max_sz = max(max_sz, sz[a]);
      max_sz = max(max_sz, sz[b]);
      --comps;
    }

    cout << comps << " " << max_sz << "\n";
  }
}
