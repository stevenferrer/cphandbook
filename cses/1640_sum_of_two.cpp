#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, x;
  cin >> n >> x;

  vector<pair<ll, ll>> a;
  a.reserve(n);

  ll k, i = 1;
  while (i <= n) {
    cin >> k;
    a.push_back({k, i++});
  }

  sort(a.begin(), a.end());

  size_t l = 0, r = n - 1;
  while (l < r) {
    ll sum = a[l].first + a[r].first;
    if (sum == x) {
      cout << a[l].second << " " << a[r].second;
      return 0;
    }

    if (sum > x) {
      --r;
      continue;
    }

    ++l;
  }

  cout << "IMPOSSIBLE";
}
