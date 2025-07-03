#include <iostream>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  cout << 0 << "\n";
  for (ll k = 2; k <= n; k++) {
    cout << (k * k) * (k * k - 1) / 2 - 4 * (k - 2) * (k - 1) << "\n";
  }
}
