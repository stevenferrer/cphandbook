#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, x;
  cin >> n >> x;

  vector<int> weight(n);

  int p = 0;
  while (p < n) {
    cin >> weight[p++];
  }

  vector<pair<int, int>> best(1 << n);

  best[0] = {1, 0};

  for (int s = 1; s < (1 << n); ++s) {
    best[s] = {n + 1, 0};
    for (int p = 0; p < n; ++p) {
      if (s & (1 << p)) {
        auto s2 = best[s ^ (1 << p)];
        if (s2.second + weight[p] <= x) {
          s2.second += weight[p];
        } else {
          ++s2.first;
          s2.second = weight[p];
        }

        best[s] = min(best[s], s2);
      }
    }
  }

  cout << best[(1 << n) - 1].first;
}
