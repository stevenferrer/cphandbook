#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

void update(vector<ll>& ft, size_t k, ll u) {
  while (k < ft.size()) {
    ft[k] += u;
    k += (k & -k);
  }
}

ll sum(vector<ll>& ft, size_t k) {
  ll s = 0;
  while (k >= 1) {
    s += ft[k];
    k -= (k & -k);
  }

  return s;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n, q;
  cin >> n >> q;

  vector<ll> ft(n + 1, 0), arr(n + 1, 0);
  for (size_t i = 1; i <= n; ++i) {
    cin >> arr[i];
    ft[i] += arr[i];
    auto j = i + (i & -i);
    if (j <= n) {
      ft[j] += ft[i];
    }
  }

  while (q--) {
    size_t qt;
    cin >> qt;

    if (qt == 1) {
      size_t k, u;
      cin >> k >> u;

      // new value - original value
      update(ft, k, u - arr[k]);
      arr[k] = u;
      continue;
    }

    size_t a, b;
    cin >> a >> b;
    cout << sum(ft, b) - sum(ft, a - 1) << "\n";
  }
}
