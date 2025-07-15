#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  vector<pair<ll, ll>> events;
  events.reserve(n);

  ll a, b;
  while (n--) {
    cin >> a >> b;
    events.push_back(make_pair(a, +1));
    events.push_back(make_pair(b, -1));
  }

  sort(events.begin(), events.end());

  ll best = 0, cust = 0;
  for (auto e : events) {
    cust += e.second;
    best = max(best, cust);
  }

  cout << best;
}
