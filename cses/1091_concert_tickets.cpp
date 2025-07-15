#include <iostream>
#include <set>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, m;
  cin >> n >> m;

  multiset<ll, greater<ll>> h;

  ll x;
  while (n--) {
    cin >> x;
    h.insert(x);
  }

  ll y;
  while (m--) {
    cin >> y;
    auto it = h.lower_bound(y);
    if (it != h.end() && *it <= y) {
      cout << *it << "\n";
      h.erase(it);
      continue;
    }

    cout << -1 << "\n";
  }
}
