#include <iostream>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int maxLen = 1, len = 1;
  char last = ' ', ch;

  while (cin >> ch) {
    if (ch == last) {
      maxLen = max(maxLen, ++len);
    } else {
      len = 1;
    }
    last = ch;
  }

  cout << maxLen;
}
