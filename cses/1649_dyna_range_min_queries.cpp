#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

int get_min(const vector<int>& t, size_t n, size_t a, size_t b) {
  a += n, b += n;

  int m = INF;
  while (a <= b) {
    if (a % 2 == 1) {
      m = min(m, t[a++]);
    }

    if (b % 2 == 0) {
      m = min(m, t[b--]);
    }

    a /= 2, b /= 2;
  }

  return m;
}

void update(vector<int>& t, size_t n, size_t i, int x) {
  i += n;
  t[i] = x;
  for (i /= 2; i >= 1; i /= 2) {
    t[i] = min(t[2 * i], t[2 * i + 1]);
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n, q;
  cin >> n >> q;

  vector<int> arr(n);
  for (size_t i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vector<int> t(2 * n, INF);
  copy(arr.begin(), arr.end(), t.begin() + n);

  for (size_t i = n - 1; i > 0; --i) {
    t[i] = min(t[2 * i], t[2 * i + 1]);
  }

  while (q--) {
    size_t qt, a, b;
    cin >> qt >> a >> b;

    if (qt == 1) {
      update(t, n, a - 1, b);
      continue;
    }

    cout << get_min(t, n, a - 1, b - 1) << "\n";
  }
}
