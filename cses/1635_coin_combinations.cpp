#include <iostream>
#include <vector>

#define TEN97 1000000007

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, x;
  cin >> n >> x;

  vector<ll> coins(n);

  ll c = 0;
  while (c < n) {
    cin >> coins[c++];
  }

  vector<ll> count(x + 1);

  count[0] = 1;
  for (ll k = 1; k <= x; ++k) {
    for (auto coin : coins) {
      if (k - coin >= 0) {
        count[k] += count[k - coin];
        count[k] %= TEN97;
      }
    }
  }

  cout << count[x];
}
