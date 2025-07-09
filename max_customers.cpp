#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// maxCustomers takes a list of events (+1, -1)
// where +1 means customer arrives and
// -1 means customer departs. The max counter
// will indicate the maximum number of customers
// at the same time.
int maxCustomers(vector<int> restaurant) {
  int maximum = 0, counter = 0;
  for (auto event : restaurant) {
    counter += event;
    maximum = max(maximum, counter);
  }

  return maximum;
}

int main() {
  // assuming we already did the sorting of
  // restaurant events (e.g. arrival and departure)
  vector<int> restaurant = {1, 1, 1, -1, -1, 1, -1, -1};
  cout << "Max customers: " << maxCustomers(restaurant) << "\n";
}
