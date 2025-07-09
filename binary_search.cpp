#include <cstdio>
#include <vector>

using namespace std;

int main() {
  vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  int x = 6, k = 0, n = a.size();
  for (int b = n / 2; b >= 1; b /= 2) {
    printf("b: %d ", b);
    while (k + b < n && a[k + b] <= x) {
      k += b;
      printf("k: %d ", k);
    }
    printf("\n");
  }

  if (a[k] == x) {
    printf("found at index %d\n", k);
  } else {
    printf("not found.\n");
  }
}
