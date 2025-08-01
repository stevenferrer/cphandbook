#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

void printBitSet(int x) {
  for (int k = 0; k < 32; k++) {
    if (x & (1 << k)) {
      cout << k << " ";
    }
  }
}

int main() {
  int n = 4, maxw = 10;

  vector<int> weight = {4, 8, 6, 1};

  // for each subset s, a pair of [rides(s), last(s)]
  vector<pair<int, int>> best(1 << n);

  // single empty ride for the empty subset
  best[0] = {1, 0};

  // 2^n == 1<<n
  for (int s = 1; s < (1 << n); ++s) {
    // initial value: n+1 rides are needed
    best[s] = {n + 1, 0};
    for (int p = 0; p < n; ++p) {
      // person p belongs to subset s?
      if (s & (1 << p)) {
        // a subset of s without person p
        // s^(1<<p) flips bit p from s,
        // removing it from the subset
        auto s2 = best[s ^ (1 << p)];

        // p still fit in this ride?
        if (s2.second + weight[p] <= maxw) {
          // add p to an existing ride
          s2.second += weight[p];
        } else {
          // reserve a new ride for p
          ++s2.first;
          s2.second = weight[p];
        }

        best[s] = min(best[s], s2);
      }
    }
  }

  cout << best[(1 << n) - 1].first << endl;
}
