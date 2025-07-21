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

  vector<ll> towers;
  towers.reserve(n);

  ll k;
  while (cin >> k) {
    auto it = upper_bound(towers.begin(), towers.end(), k);
    if (it != towers.end()) {
      *it = k;
      continue;
    }

    towers.push_back(k);
  }

  cout << towers.size();
}
