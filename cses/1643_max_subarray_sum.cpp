#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n;
  cin >> n;

  vector<ll> a(n);

  for (size_t i = 0; i < n; i++) {
    cin >> a[i];
  }

  ll kmax, best;
  best = kmax = a[0];

  for (size_t k = 1; k < n; k++) {
    kmax = max(a[k], kmax + a[k]);
    best = max(kmax, best);
  }
  cout << best;
}
