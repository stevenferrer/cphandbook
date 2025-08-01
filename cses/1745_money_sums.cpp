#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> coins(n + 1);
  coins[0] = 0;

  int maxSum = 0;
  for (int i = 1; i <= n; ++i) {
    cin >> coins[i];
    maxSum += coins[i];
  }

  // table of sums
  vector<vector<int>> tos(n + 1, vector<int>(maxSum + 1));

  tos[0][0] = 1;
  for (int k = 1; k <= n; ++k) {
    for (int sum = 0; sum <= maxSum; ++sum) {
      if (sum - coins[k] >= 0) {
        tos[k][sum] |= tos[k - 1][sum - coins[k]];
      }
      tos[k][sum] |= tos[k - 1][sum];
    }
  }

  vector<int> sums;
  sums.reserve(maxSum);

  for (int sum = 1; sum <= maxSum; ++sum) {
    if (!tos[n][sum]) {
      continue;
    }
    sums.push_back(sum);
  }

  cout << sums.size() << "\n";
  for (auto sum : sums) {
    cout << sum << " ";
  }
}
