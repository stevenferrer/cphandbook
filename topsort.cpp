
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

// pending -> inprogress -> done
enum Status {
  pending,
  inprogress,
  done,
};

vector<int> topSort(vector<vector<int>> adjl, int vertices) {
  vector<int> status(vertices + 1, Status::pending);

  vector<int> l;
  l.reserve(vertices + 1);

  // we skip vertex 0 and start at 1, but
  // we can always change this
  for (int v = 1; v <= vertices; ++v) {
    // skip processed vertices
    if (status[v] == Status::done) {
      continue;
    }

    stack<int> s;
    s.push(v);

    while (!s.empty()) {
      int a = s.top();

      // vertex is marked as in-progress, let's mark it as done
      if (status[a] == Status::inprogress) {
        s.pop();

        status[a] = Status::done;
        l.push_back(a);
        continue;
      }

      // vertex is pending, mark as in-progress
      status[a] = Status::inprogress;

      // visit neighbors
      for (int b : adjl[a]) {
        // skipped processed neighbors
        if (status[b] == Status::done) {
          continue;
        }

        // if neighbor is in-progress, then we have cycle
        if (status[b] == Status::inprogress) {
          // cycle found!
          return {};
        }

        s.push(b);
      }
    }
  }

  reverse(l.begin(), l.end());
  return l;
}

int main() {
  int n = 6;
  vector<vector<int>> adjl(n + 1);
  adjl[1].push_back(2);
  adjl[2].push_back(3);
  adjl[3].push_back(6);
  adjl[4].push_back(1);
  adjl[4].push_back(5);
  adjl[5].push_back(2);
  adjl[5].push_back(3);

  cout << "Top sort:" << endl;
  auto l = topSort(adjl, n);
  for (auto v : l) {
    cout << v << " ";
  }
  cout << endl;

  // add cycle
  adjl[3].push_back(5);
  cout << "Top sort with cycle: " << endl;
  l = topSort(adjl, n);
  for (auto v : l) {
    cout << v << " ";
  }

  cout << endl;
}
