#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int ancestor(vector<vector<int>> table, int n, int x, int k) {
  int u = (int)ceil(log2(n));
  int anc = x;

  // if k=3, in bits, 0011
  // so, ancestor(ancestor(8, 1), 2)
  // thus, k is a sum of powers of 2 (e.g. 1 and 2)

  // we can move from 2^u -> 2^0 or;
  // we can also do 2^0 -> 2^u;
  // either way works

  for (int p = u; p >= 0; --p) {
    int kpow = k & (1 << p);
    if (kpow) {
      anc = table[p][anc];
      printf("p: %d, kpow: %d, anc: %d\n", p, kpow, anc);
      if (!anc) {
        break;
      }
    }
  }

  return anc;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n = 8;
  vector<int> parent = {
      0, // skip 0,
      0, // 1 has no parent,
      1, // 2->1
      4, // 3->4
      1, // 4->1
      1, // 5->1
      2, // 6->2
      4, // 7->4
      7, // 8->7
  };

  // k is a power of 2, at most 2^u
  // 2^k <= 2^u
  int u = ceil(log2(n));

  // Binary lifting table (ancestor)
  vector<vector<int>> table(u + 1, vector<int>(n + 1));

  // 2^0-th step, i.e., immediate parent
  for (int v = 1; v <= n; ++v) {
    table[0][v] = parent[v];
  }

  // 0 is a sentinel value, meaning no parent

  // 2^k-th steps
  for (int k = 1; k <= u; ++k) {
    for (int v = 1; v <= n; ++v) {
      // w is the parent of v
      int w = table[k - 1][v];
      // parent of u
      table[k][v] = table[k - 1][w];
    }
  }

  for (int k = 0; k <= u; ++k) {
    printf("ancestor(x, %d) | ", (1 << k));
    for (int v = 1; v <= n; ++v) {
      cout << table[k][v] << " ";
    }
    cout << endl;
  }

  auto anc = ancestor(table, n, 8, 3);
  cout << "ancestor(8, 3): " << anc << endl;
}
