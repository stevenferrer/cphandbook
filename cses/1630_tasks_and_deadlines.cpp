#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  size_t n;
  cin >> n;

  vector<pair<ll, ll>> tasks;
  tasks.reserve(n);

  ll a, d;
  while (cin >> a >> d) {
    tasks.push_back({a, d});
  }

  sort(tasks.begin(), tasks.end());

  ll time = 0, score = 0;
  for (auto task : tasks) {
    // keep track of the time
    time += task.first;
    // score = deadline - time
    score += task.second - time;
  }

  cout << score;
}
