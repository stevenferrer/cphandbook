#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef unsigned long long ull;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ull n, q;
  cin >> n >> q;

  // precompute log2 values
  vector<ull> lg(n + 1);
  lg[1] = 0;
  for (size_t i = 2; i <= n; ++i) {
    lg[i] = lg[i / 2] + 1;
  }

  ull max_k = lg[n];
  vector<vector<ull>> st(max_k + 1, vector<ull>(n));

  for (ull j = 0; j < n; ++j) {
    cin >> st[0][j];
  }

  for (ull k = 1; k <= max_k; ++k) {
    for (ull j = 0; j + (1 << k) <= n; ++j) {
      st[k][j] = min(st[k - 1][j], st[k - 1][j + (1 << (k - 1))]);
    }
  }

  ull a, b;
  while (q--) {
    cin >> a >> b;
    ull k = lg[b - a + 1];
    ull minl = st[k][a - 1];
    ull minr = st[k][b - (1 << k)];

    cout << min(minl, minr) << "\n";
  }
}
