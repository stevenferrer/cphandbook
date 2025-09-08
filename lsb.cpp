#include <iostream>

using namespace std;

string bit_str(int x, int bits = sizeof(int) * 8) {
  string s;
  for (int k = bits - 1; k >= 0; k--) {
    if (x & (1 << k)) {
      s += '1';
    } else {
      s += '0';
    }
  }

  return s;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n = 15;
  for (int k = 11; k <= n; ++k) {
    int lsb = k & -k;
    cout << bit_str(k, 4) << " & ";
    cout << bit_str(-k, 4) << " -> ";
    cout << bit_str(lsb, 4) << " = ";
    cout << lsb;
    cout << endl;
  }
}
