#include <iostream>
#include <vector>

using namespace std;

const int n = 4;
int cnt = 0;

// column marker
vector<int> cols(n, 0);

// left and right diagonal marker
vector<int> ldiag(2 * n - 1, 0);
vector<int> rdiag(2 * n - 1, 0);

void queens(int row) {
  if (row == n) {
    cnt++;
    return;
  }

  // check each column
  for (int col = 0; col < n; col++) {
    int ldiagIdx = col + row;
    int rdiagIdx = (n - 1) + (col - row);

    if (cols[col] || ldiag[ldiagIdx] || rdiag[rdiagIdx]) {
      continue;
    }

    cols[col] = ldiag[ldiagIdx] = rdiag[rdiagIdx] = 1;

    queens(row + 1);

    cols[col] = ldiag[ldiagIdx] = rdiag[rdiagIdx] = 0;
  }
}

int main() {
  queens(0);

  cout << cnt << "\n";

  return 0;
}
