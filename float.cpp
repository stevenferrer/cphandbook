#include <cstdio>
#include <cstdlib>

using namespace std;

int main() {
  double a = 0.3 * 3 + 0.1;
  double b = 1;
  printf("a: %.20f\n", a); // 0.99999999999999988898
  printf("b: %.20f\n", b);

  const double e = 1e-9;

  // compare
  if (abs(a - b) < e) { // a and b are equal
    printf("a and b are equal\n");
  } else {
    printf("a and b are not equal\n");
  }
}
