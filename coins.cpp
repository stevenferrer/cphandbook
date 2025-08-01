#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

#define INF 1000000000ul

int main() {
  vector<ll> coins = {1, 3, 4};

  ll targetSum = 5;

  // minimum coins for the sum
  vector<ll> minCoins(targetSum + 1);
  // first coin in the sum
  vector<ll> firstCoin(targetSum + 1);
  // count of solutions
  vector<ll> solCount(targetSum + 1);

  solCount[0] = 1;
  minCoins[0] = 0;
  for (ll k = 1; k <= targetSum; ++k) {
    minCoins[k] = INF;
    for (auto c : coins) {
      // compute the remaining sum to find
      ll rem = k - c;
      // use sum with minimal coins
      if (rem >= 0 && minCoins[rem] + 1 < minCoins[k]) {
        minCoins[k] = minCoins[rem] + 1;
        firstCoin[k] = c;
      }

      if (rem >= 0) {
        solCount[k] += solCount[rem];
      }
    }
  }

  // coins in the solution
  ll n = targetSum;
  while (n > 0) {
    cout << firstCoin[n] << " ";
    n -= firstCoin[n];
  }
  cout << "\n";

  // solution count
  cout << solCount[targetSum] << endl;
}
