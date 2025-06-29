#include <iostream>

using namespace std;

typedef long long ll;

int main() {
  ll x = 1;
  int mod = 3;
  int n = 100;
  for (ll i = 1; i <= n; i++) {
    x = (x * i) % mod;
    if (x < 0) {
      x += mod;
    }
    cout << x << " ";
  }

  cout << x % 3 << "\n";

  cout << 17 % 5 << "\n";
}
