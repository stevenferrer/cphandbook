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

void searchSubset(vector<int>& subset, int k, int n) {
  if (k == n + 1) {
    // print current subset
    printVector(subset);
    cout << "\n";
  } else {
    // include k
    subset.push_back(k);
    searchSubset(subset, k + 1, n);

    // exclude k
    subset.pop_back();
    searchSubset(subset, k + 1, n);
  }
}

void makeSubsets(vector<int>& nums, vector<int>& sub, vector<vector<int>>& subs,
                 int i) {
  if (i == nums.size()) {
    subs.push_back(sub);
  } else {
    sub.push_back(nums[i]);
    makeSubsets(nums, sub, subs, i + 1);

    sub.pop_back();
    makeSubsets(nums, sub, subs, i + 1);
  }
}

int main() {
  // search and print subsets
  vector<int> subsets;
  subsets.reserve(3);
  searchSubset(subsets, 1, 3);
  cout << "\n";

  // make subsets
  vector<int> nums({3, 6, 9, 12});

  vector<vector<int>> subs;
  vector<int> sub;
  sub.reserve(nums.size());

  makeSubsets(nums, sub, subs, 0);

  for (auto sub : subs) {
    for (auto num : sub) {
      cout << num << " ";
    }
    cout << "\n";
  }
}
