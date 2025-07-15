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

  vector<ll> p;
  p.reserve(n);

  ll w;
  while (cin >> w) {
    p.push_back(w);
  }

  sort(p.rbegin(), p.rend());

  size_t gondolas = 0, j = 0, k = p.size() - 1;
  while (j <= k) {
    if (p[k] <= x - p[j]) {
      --k;
    }

    ++j;
    ++gondolas;
  }

  cout << gondolas;
}
