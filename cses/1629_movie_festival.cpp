#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  ll n;
  cin >> n;

  vector<pair<ll, ll>> movies;
  movies.reserve(n);

  ll a, b;
  while (cin >> a >> b) {
    movies.push_back({b, a});
  }

  sort(movies.begin(), movies.end());

  ll count = 1, prev = 0, next = 1;
  while (next < n) {
    // find next movie that ends after previous one
    if (movies[next].second < movies[prev].first) {
      ++next;
      continue;
    }

    // set the new movies as previous
    prev = next++;
    ++count;
  }

  cout << count;
}
