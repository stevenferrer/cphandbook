

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  // {duration, deadline}
  vector<pair<int, int>> tasks = {{4, 2}, {3, 10}, {2, 8}, {4, 15}};

  // sort by duration
  sort(tasks.begin(), tasks.end());

  int points = 0;
  for (auto task : tasks) {
    printf("deadline: %d, duration: %d\n", task.second, task.first);
    points += task.second - task.first;
  }

  cout << points << endl;
}
