#include <bitset>
#include <iostream>

using namespace std;

typedef long long ll;

#define SIZE 1000001ul

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  if (n < 3) {
    cout << "NO";
    return 0;
  }

  bitset<SIZE> a, b;
  if (n % 2 == 0) {
    ll k = n;
    while (k >= 1) {
      a[k] = 1;
      if (k - 3 >= 1) {
        k -= 3;
        a[k] = 1;
      }

      --k;
    }

    if (k != 0) {
      cout << "NO";
      return 0;
    }

    k = n - 1;
    while (k >= 2) {
      b[k] = 1;
      if (k - 1 >= 2) {
        b[--k] = 1;
      }

      k -= 3;
    }

    if (k + 3 != 2) {
      cout << "NO";
      return 0;
    }
  } else {
    ll k = n;
    while (k >= 3) {
      a[k] = 1;
      if (k - 3 >= 3) {
        k -= 3;
        a[k] = 1;
      }

      k -= 1;
    }

    if (k + 1 != 3) {
      cout << "NO";
      return 0;
    }

    k = n - 1;
    while (k >= 1) {
      b[k] = 1;
      if (k - 1 >= 1) {
        b[--k] = 1;
      }

      k -= 3;
    }

    if (k + 3 != 1) {
      cout << "NO";
      return 0;
    }
  }

  cout << "YES\n";

  cout << a.count() << "\n";
  for (size_t k = n; k >= 1; --k) {
    if (!a[k]) {
      continue;
    }
    cout << k << " ";
  }

  cout << "\n" << b.count() << "\n";
  for (size_t k = n; k >= 1; --k) {
    if (!b[k]) {
      continue;
    }
    cout << k << " ";
  }
}
