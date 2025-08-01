#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  vector<ll> a = {6, 2, 5, 1, 7, 4, 8, 3};

  ll n = a.size();

  vector<ll> len(n);

  for (ll k = 0; k < n; ++k) {
    len[k] = 1;
    for (ll i = 0; i < k; ++i) {
      if (a[i] < a[k]) {
        len[k] = max(len[k], len[i] + 1);
      }
    }
  }

  for (auto e : len) {
    cout << e << " ";
  }
  cout << endl;
}
