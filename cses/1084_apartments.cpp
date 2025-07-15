#include <iostream>
#include <queue>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, m, k;
  cin >> n >> m >> k;

  priority_queue<ll, vector<ll>, greater<ll>> a, b;

  ll x;
  while (n--) {
    cin >> x;
    a.push(x);
  }

  ll y;
  while (m--) {
    cin >> y;
    b.push(y);
  }

  ll assigned = 0;
  while (!a.empty() && !b.empty()) {
    ll minSize = a.top() - k, maxSize = a.top() + k;

    // find at least min size
    while (!b.empty() && b.top() < minSize) {
      b.pop();
    }

    // check if within the max size
    if (!b.empty() && b.top() <= maxSize) {
      b.pop();
      ++assigned;
    }

    a.pop();
  }

  cout << assigned;
}
