#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<bool> missing(n + 1, true);

  int num;
  while (cin >> num) {
    missing[num] = false;
  }

  for (int i = 1; i <= n; ++i) {
    if (missing[i]) {
      cout << i;
      break;
    }
  }
}
