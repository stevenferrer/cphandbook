#include <iostream>
#include <vector>

#define TEN97 1000000007

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  vector<vector<ll>> grid(n, vector<ll>(n));

  char ch;
  for (ll r = 0; r < n; ++r) {
    for (ll c = 0; c < n; ++c) {
      cin >> ch;
      grid[r][c] = ch == '.' ? 1 : 0;
    }
  }

  for (ll c = 1; c < n; ++c) {
    if (!grid[0][c]) {
      continue;
    }
    grid[0][c] = grid[0][c - 1];
  }
  for (ll r = 1; r < n; ++r) {
    if (!grid[r][0]) {
      continue;
    }
    grid[r][0] = grid[r - 1][0];
  }

  for (ll r = 1; r < n; ++r) {
    for (ll c = 1; c < n; ++c) {
      if (!grid[r][c]) {
        continue;
      }
      grid[r][c] = grid[r][c - 1] + grid[r - 1][c];
      grid[r][c] %= TEN97;
    }
  }

  cout << grid[n - 1][n - 1] << endl;
}
