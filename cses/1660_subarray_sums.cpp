#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, x;
  cin >> n >> x;

  vector<ll> a(n + 1);
  for (ll i = 0; i < n; ++i) {
    cin >> a[i];
  }

  // we allow l and r pointers to go beyond n
  // to simplify the if conditions
  a[n] = 0;

  int sum = a[0];

  int l, r, count;
  l = r = count = 0;
  while (l < n && r < n) {
    if (sum == x) {
      // subtract left element, and move left ptr
      sum -= a[l++];
      // move right ptr and add new element
      sum += a[++r];
      ++count;
    } else if (sum < x) {
      // move right ptr and add new element
      sum += a[++r];
    } else {
      // subtract left element and move left ptr
      sum -= a[l++];
    }
  }

  cout << count;
}
