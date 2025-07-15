
#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  vector<int> v = {1, 2, 3, 4, 5, 7, 7, 8, 9};

  auto it = upper_bound(v.begin(), v.end(), 5);
  cout << "ub: " << *it << endl;

  it = lower_bound(v.begin(), v.end(), 6);
  cout << "lb: " << *it << endl;

  multiset<ll> ms = {3, 5, 5, 7, 8};

  cout << "ms lb: " << *ms.lower_bound(8) << endl;
  ms.erase(ms.lower_bound(5));
  cout << "ms.count(5): " << ms.count(5) << endl;

  // Reverse lowerbound i.e. lowerbound in descending
  multiset<ll, greater<ll>> ms2 = {9, 3, 9, 6, 6, 8, 6, 2, 6, 3};
  vector<ll> v2 = {9, 5, 4, 6, 3, 9, 3, 3, 5, 2};

  for (size_t i = 0; i < ms2.size(); ++i) {
    ll x = v2[i];
    auto it = ms2.lower_bound(x);
    if (it != ms2.end()) {
      cout << "lb(" << x << "): " << *it << endl;
    }
  }
}
