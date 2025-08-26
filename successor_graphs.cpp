#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int powi(int base, unsigned int exp) {
  int result = 1;
  for (unsigned int k = 1; k <= exp; ++k) {
    result *= base;
  }
  return result;
}

// since a successor graph only as one edge,
// we model it as a 1-dim array
int successor(vector<int> sgraph, int n, int x, int k) {

  int u = (int)ceil(log2(k));

  printf("u = %d\n", u);

  // successor table
  vector<vector<int>> table(u + 1, vector<int>(n + 1));

  // fill-in the 2^0=1 step
  for (int v = 1; v <= n; ++v) {
    table[0][v] = sgraph[v];
  }

  // fill-in the rest of 2^j step
  for (int j = 1; j <= u; ++j) {
    for (int v = 1; v <= n; ++v) {
      // successor of v from previous row
      int vv = table[j - 1][v];
      // successor of vv from previous row
      table[j][v] = table[j - 1][vv];
    }
  }

  for (int v = 1; v <= n; ++v) {
    cout << v << " ";
  }
  cout << endl;
  for (int v = 1; v <= n; ++v) {
    cout << "-";
    if (v < n) {
      cout << "-";
    }
  }
  cout << endl;

  for (int i = 0; i <= u; ++i) {
    for (int v = 1; v <= n; ++v) {
      cout << table[i][v] << " ";
    }
    cout << endl;
  }

  // follow the successor path
  int succ = x;
  for (int exp = u; exp >= 0; --exp) {
    int kpow = powi(2, exp);
    if (kpow > k) {
      continue;
    }

    // printf("succ(%d, %d) = %d\n", succ, kpow, table[exp][succ]);

    // next successor
    succ = table[exp][succ];
    k -= kpow;
  }

  return succ;
}

int cycleLength(vector<int> sgraph, int x) {
  auto a = sgraph[x];
  auto b = sgraph[a];

  while (a != b) {
    a = sgraph[a];
    b = sgraph[sgraph[b]];
  }

  a = x;
  while (a != b) {
    a = sgraph[a];
    b = sgraph[b];
  }

  b = sgraph[a];
  int length = 1;
  while (a != b) {
    b = sgraph[b];
    ++length;
  }

  return length;
}

int main() {
  cout << "2^0 = " << powi(2, 0) << endl;

  int n = 9;
  vector<vector<int>> adjl;

  int x = 4, k = 11;
  vector<int> sgraph1 = {0, 3, 5, 7, 6, 2, 2, 1, 6, 3};
  printf("succ(%d, %d) = %d\n", x, k, successor(sgraph1, n, x, k));

  printf("sgraph1 cycle length: %d\n", cycleLength(sgraph1, 2));

  vector<int> sgraph2 = {0, 2, 3, 4, 5, 6, 3};
  printf("sgraph2 cycle length: %d", cycleLength(sgraph2, 6));
}
