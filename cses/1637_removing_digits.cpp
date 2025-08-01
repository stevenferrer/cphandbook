#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  int steps = 0;
  while (n) {
    // get max of digits
    int num = n, sub = 0;
    while (num) {
      sub = max(sub, num % 10);
      num /= 10;
    }

    n -= sub;
    ++steps;
  }

  cout << steps;
}
