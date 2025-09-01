#include <cstddef>
#include <deque>
#include <iostream>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n, k;
  cin >> n >> k;

  ll x, a, b, c;
  cin >> x >> a >> b >> c;

  deque<ll> dq;
  dq.push_back(x);

  ll r = 1, wxor = x;
  while (r < k) {
    x = (a * x + b) % c;
    dq.push_back(x);

    wxor ^= x;
    ++r;
  }

  ll xors = wxor;

  while (r < n) {
    x = (a * x + b) % c;
    dq.push_back(x);

    // reverse xor and xor with x
    wxor ^= x ^ dq.front();
    dq.pop_front();

    xors ^= wxor;
    ++r;
  }

  cout << xors;
}
