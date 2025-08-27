#include <iostream>
#include <stack>
#include <utility>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  stack<pair<int, int>> s;
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    while (!s.empty() && s.top().first >= x) {
      s.pop();
    }

    int pos = 0;
    if (!s.empty()) {
      pos = s.top().second + 1;
    }
    cout << pos << " ";

    s.push({x, i});
  }
}
