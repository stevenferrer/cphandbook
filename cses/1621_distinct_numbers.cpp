#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  vector<ll> s;
  s.reserve(n);

  ll x;
  while (cin >> x) {
    s.push_back(x);
  }

  sort(s.begin(), s.end());

  ll distinct = 1;
  for (ll i = 1; i < n; ++i) {
    if (s[i - 1] != s[i]) {
      ++distinct;
    }
  }

  cout << distinct;
}
