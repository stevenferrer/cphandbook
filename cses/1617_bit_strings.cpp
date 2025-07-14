#include <iostream>

using namespace std;

typedef long long ll;

#define TEN97 1000000007

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  ll base = 2, ans = 1;
  for (;;) {
    // odd or even
    if (n & 1) {
      ans *= base;
      ans %= TEN97;
    }

    n >>= 1;
    if (!n) {
      break;
    }

    base *= base;
    base %= TEN97;
  }

  cout << ans;
}
