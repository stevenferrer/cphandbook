#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int kth_boss(const vector<vector<int>>& boss, int e, int k) {
  // n number of employees
  int n = boss[0].size();
  // there are at most u levels
  int u = (int)ceil(log2(n));

  int kboss = e;
  for (int p = u; p >= 0; --p) {
    int kpow = k & (1 << p);
    if (kpow) {
      kboss = boss[p][kboss];
      if (!kboss) {
        return -1;
      }
    }
  }

  return kboss;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, q;
  cin >> n >> q;

  int u = (int)ceil(log2(n));
  vector<vector<int>> boss(u + 1, vector<int>(n + 1));

  // immediate boss of e
  for (int e = 2; e <= n; e++) {
    cin >> boss[0][e];
  }

  // table of kth boss of employee e
  for (int k = 1; k <= u; ++k) {
    for (int e = 1; e <= n; ++e) {
      // g is the boss of e
      int g = boss[k - 1][e];
      // the boss of g is the kth boss of e
      boss[k][e] = boss[k - 1][g];
    }
  }

  int x, k;
  while (q--) {
    cin >> x >> k;
    cout << kth_boss(boss, x, k) << "\n";
  }
}
