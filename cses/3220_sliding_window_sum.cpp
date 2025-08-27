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

  ll r = 1, sum = x;
  while (r < k) {
    x = (a * x + b) % c;
    dq.push_back(x);

    sum += x;
    ++r;
  }

  ll xor_sum = sum;

  while (r < n) {
    x = (a * x + b) % c;
    dq.push_back(x);

    sum += x - dq.front();
    dq.pop_front();

    xor_sum ^= sum;
    ++r;
  }

  cout << xor_sum;
}
