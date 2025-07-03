#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  long n;
  cin >> n;

  long largest = 0, current = 0, moves = 0;
  while (cin >> current) {
    if (largest > current) {
      // increase by move by largest-current
      moves += largest - current;
      continue;
    }

    largest = current;
  }

  cout << moves;
}
