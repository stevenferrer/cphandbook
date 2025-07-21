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

  cin >> a[0];

  ll kmax, best;
  best = kmax = a[0];

  size_t k = 1;
  while (k < n) {
    cin >> a[k];
    kmax = max(a[k], kmax + a[k]);
    best = max(kmax, best);

    ++k;
  }

  cout << best;
}
