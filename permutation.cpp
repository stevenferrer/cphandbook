#include <iostream>
#include <vector>

using namespace std;

void printVector(vector<int> v) {
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v[i];
    if (i + 1 < v.size()) {
      cout << " ";
    }
  }
}

vector<int> permutation;
const int n = 3;
static bool chosen[n + 1];

void searchPermutation() {
  if (permutation.size() == n) {
    // print permutation
    printVector(permutation);
    cout << "\n";
    return;
  }

  for (int i = 1; i <= n; i++) {
    if (chosen[i]) {
      continue;
    }

    chosen[i] = true;
    permutation.push_back(i);
    searchPermutation();
    chosen[i] = false;
    permutation.pop_back();
  }
}

void stdPerm(int n) {
  vector<int> perm;
  for (int i = 1; i <= n; i++) {
    perm.push_back(i);
  }
  do {
    // print permutation
    printVector(perm);
    cout << "\n";
  } while (next_permutation(perm.begin(), perm.end()));
}

int main() {
  cout << "Custom permutation: \n" << n;
  searchPermutation();
  cout << "\n";

  cout << "Std permutation: \n";
  stdPerm(n);
  return 0;
}
