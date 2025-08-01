#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  vector<vector<ll>> grid = {{3, 7, 9, 2, 7},
                             {9, 8, 3, 5, 5},
                             {1, 7, 9, 8, 5},
                             {3, 8, 6, 4, 10},
                             {6, 3, 9, 7, 8}};

  ll n = grid.size();
  vector<vector<ll>> sum(n + 1, vector<ll>(n + 1));

  for (ll y = 0; y < 1; ++y) {
    for (ll x = 0; x < 1; ++x) {
      sum[y][x] = 0;
    }
  }

  for (ll y = 1; y <= n; ++y) {
    for (ll x = 1; x <= n; ++x) {
      sum[y][x] = max(sum[y][x - 1], sum[y - 1][x]) + grid[y - 1][x - 1];
    }
  }

  for (ll y = 1; y <= n; ++y) {
    for (ll x = 1; x <= n; ++x) {
      cout << sum[y][x] << " ";
    }
    cout << "\n";
  }
}
