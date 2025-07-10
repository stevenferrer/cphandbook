#include <iostream>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  ll t;
  cin >> t;

  ll y, x;
  while (t--) {
    cin >> y >> x;
    if (y == 1ll && x == 1ll) {
      cout << "1\n";
      continue;
    }

    if (x >= y) {
      if (x % 2ll == 0ll) {
        cout << (x - 1ll) * (x - 1ll) + y << "\n";
      } else {
        cout << (x * x) - (y - 1ll) << "\n";
      }
    } else {
      if (y % 2ll == 0ll) {
        cout << (y * y) - (x - 1ll) << "\n";
      } else {
        cout << (y - 1ll) * (y - 1ll) + x << "\n";
      }
    }
  }
}
