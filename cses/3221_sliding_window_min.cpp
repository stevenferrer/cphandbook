#include <deque>
#include <iostream>
#include <utility>

using namespace std;

typedef long long ll;

void add_item(deque<pair<ll, size_t>>& dq, size_t l, size_t r, ll v) {
  while (!dq.empty() && dq.back().first > v) {
    dq.pop_back();
  }

  dq.push_back({v, r});

  if (!dq.empty() && dq.front().second < l) {
    dq.pop_front();
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n, k;
  cin >> n >> k;

  ll x, a, b, c;
  cin >> x >> a >> b >> c;

  deque<pair<ll, size_t>> dq;

  // add the first window elements
  size_t l, r;
  l = r = 0;
  while (r < k) {
    add_item(dq, l, r++, x);
    x = (a * x + b) % c;
  }
  ++l;

  // save the first window min
  ll xor_min = dq.front().first;

  // move thru windows
  while (r < n) {
    add_item(dq, l++, r++, x);
    x = (a * x + b) % c;
    // update with new window min
    xor_min ^= dq.front().first;
  }

  cout << xor_min;
}
