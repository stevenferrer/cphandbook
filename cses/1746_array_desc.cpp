
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

#define TEN97 1000000007

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  // table of paths
  vector<vector<ll>> top(n, vector<ll>(m + 1, 0));

  // start path
  int x;
  cin >> x;
  if (x == 0) {
    // paths 1->m are possible start
    fill(top[0].begin(), top[0].end(), 1);
  } else {
    // only path x is possible
    top[0][x] = 1;
  }

  // 1->n path
  for (int i = 1; i < n; ++i) {
    cin >> x;

    // only path x is possible
    if (x != 0) {
      // add inbound paths
      top[i][x] += top[i - 1][x];
      if (x - 1 > 0) {
        top[i][x] += top[i - 1][x - 1];
      }
      if (x + 1 <= m) {
        top[i][x] += top[i - 1][x + 1];
      }

      top[i][x] %= TEN97;
      continue;
    }

    // paths 1->m are possible
    for (int j = 1; j <= m; ++j) {
      // add inbound paths
      top[i][j] += top[i - 1][j];
      if (j - 1 > 0) {
        top[i][j] += top[i - 1][j - 1];
      }
      if (j + 1 <= m) {
        top[i][j] += top[i - 1][j + 1];
      }

      top[i][j] %= TEN97;
    }
  }

  // sum of all the paths
  ll paths = 0;
  for (int j = 1; j <= m; ++j) {
    paths += top[n - 1][j];
    paths %= TEN97;
  }

  cout << paths;
}
