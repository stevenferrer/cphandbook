#include <iostream>

using namespace std;

int main() {
  // io optimization
  ios::sync_with_stdio(0);
  cin.tie(0);

  int a, b;
  string s;

  cin >> a >> b >> s;

  printf("printf: %d %d %s\n", a, b, s.c_str());
  cout << "cout: " << a << " " << b << " " << s << "\n";
}
