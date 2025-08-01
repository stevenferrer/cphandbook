#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n, x;
  cin >> n >> x;

  vector<int> costs(n + 1);
  costs[0] = 0;

  int i = 1;
  while (i <= n) {
    cin >> costs[i++];
  }

  vector<int> pages(n + 1);
  pages[0] = 0;

  i = 1;
  while (i <= n) {
    cin >> pages[i++];
  }

  // table of pages
  vector<vector<int>> top(n + 1, vector<int>(x + 1, 0));

  for (int k = 1; k <= n; ++k) {
    for (int budget = 1; budget <= x; ++budget) {
      // save max pages in this budget for first k-1 books
      top[k][budget] = top[k - 1][budget];

      // can we afford this book?
      if (costs[k] <= budget) {
        // remaining budget after purchase
        int rem = budget - costs[k];
        // save whichever max pages for this budget
        top[k][budget] = max(top[k][budget], top[k - 1][rem] + pages[k]);
      }
    }
  }

  // print the table
  // cout << "\t";
  // for (int budget = 1; budget <= x; ++budget) {
  //   cout << budget << "\t";
  // }
  // cout << endl;

  // for (int k = 1; k <= n; ++k) {
  //   cout << costs[k] << "\t";
  //   for (int budget = 1; budget <= x; ++budget) {
  //     cout << top[k][budget] << "\t";
  //   }
  //   cout << endl;
  // }

  cout << top[n][x];
}
