#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n, q;
  cin >> n >> q;

  vector<ll> cumsum(n + 1);
  cumsum[0] = 0;
  for (size_t i = 1; i <= n; ++i) {
    cin >> cumsum[i];
    cumsum[i] += cumsum[i - 1];
  }

  size_t a, b;
  while (q--) {
    cin >> a >> b;
    cout << cumsum[b] - cumsum[a - 1] << "\n";
  }
}
