#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

typedef long long ll;

bool knapsack(vector<ll> w0, ll targetSum) {
  ll n = w0.size();

  // add 0 to the weights as base case
  vector<ll> w;
  w.reserve(n + 1);
  w.push_back(0);
  // w{0, w1,w2,...wn}
  w.insert(w.end(), w0.begin(), w0.end());

  // total sum of all weights
  ll totalSum = accumulate(w.begin(), w.end(), 0);

  vector<vector<bool>> ok(totalSum + 1, vector<bool>(n + 1, false));

  ok[0][0] = true;
  for (ll k = 1; k <= n; ++k) {
    for (ll sum = 0; sum <= totalSum; ++sum) {
      ll sum0 = sum - w[k];
      if (sum0 >= 0) {
        // check if we can form sum_0 = sum - w_k
        // using the first k-1 weights
        ok[sum][k] = ok[sum][k] || ok[sum0][k - 1];
      }

      // check if we can form the sum
      // using the first k-1 weights
      ok[sum][k] = ok[sum][k] || ok[sum][k - 1];
    }
  }

  // print the knapsack grid
  cout << "\t";
  for (ll sum = 0; sum <= totalSum; ++sum) {
    cout << sum << "\t";
  }
  cout << endl;
  for (ll k = 0; k <= n; ++k) {
    cout << k << "\t";
    for (ll sum = 0; sum <= totalSum; ++sum) {
      cout << (ok[sum][k] == 1 ? "✔" : ".") << "\t";
    }
    cout << endl;
  }

  return ok[targetSum][n];
}

// bool knapsackCompact(vector<ll> w, ll targetSum) {
//   ll n = w.size();

//   vector<ll> w0;
//   w0.reserve(n + 1);
//   w0.push_back(0);
//   // w{0, w1,w2,...wn}
//   w0.insert(w0.end(), w.begin(), w.end());

//   ll totalSum = accumulate(w0.begin(), w0.end(), 0);

//   vector<ll> ok(totalSum + 1);

//   // Note: possible[] gets updated using multiple passes
//   ok[0] = true;
//   for (ll k = 1; k <= n; k++) {
//     for (ll sum = totalSum - w0[k]; sum >= 0; --sum) {
//       ok[sum + w0[k]] |= ok[sum];
//     }
//   }

//   return ok[targetSum];
// }

int main() {

  vector<ll> w = {1, 3, 3, 5};
  ll targetSum = 12;
  knapsack(w, targetSum);
  //   cout << knapsackCompact(w, targetSum) << "\n";
}
