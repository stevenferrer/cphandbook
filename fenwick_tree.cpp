#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<int> make_ft(vector<int> a) {
  int n = a.size();
  vector<int> ft(n + 1, 0);
  for (int i = 1; i <= n; ++i) {
    ft[i] += a[i - 1];
    // get parent node
    auto p = i + (i & -i);

    // only update the parent node
    if (p <= n) {
      ft[p] += ft[i];
    }
  }

  return ft;
}

void add(vector<int>& ft, size_t i, int delta) {
  // start at i and propagate values upward
  while (i < ft.size()) {
    ft[i] += delta;
    i += (i & -i);
  }
}

int sum(vector<int> ft, int i) {
  // start at i and
  int s = 0;
  while (i >= 1) {
    // cout << ft[i];
    s += ft[i];
    i -= (i & -i);
  }
  // cout << endl;

  return s;
}

void print_ft(vector<int> ft) {
  for (size_t i = 1; i < ft.size(); ++i) {
    cout << ft[i] << " ";
  }
}

int sum(vector<int> ft, int l, int r) {
  auto rsum = sum(ft, r);
  auto lsum = sum(ft, l - 1);
  return rsum - lsum;
}

string bit_str(int x, int bits = sizeof(int) * 8) {
  string s;
  for (int k = bits - 1; k >= 0; k--) {
    if (x & (1 << k)) {
      s += '1';
    } else {
      s += '0';
    }
  }

  return s;
}

void dot(vector<int> t, vector<int> a) {
  for (size_t i = 1; i < t.size(); ++i) {
    printf("%lu[label=%d xlabel=%lu]\n", i, a[i - 1], i);
  }

  for (size_t i = 1; i < t.size(); ++i) {
    auto p = i + (i & -i);
    if (p <= t.size()) {
      printf("%lu->%lu[arrowsize=0.5]\n", i, p);
    }
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<int> a = {1, 3, 4, 8, 6, 1, 4, 2};

  cout << "make ft:\n";
  auto t = make_ft(a);

  print_ft(t);
  cout << endl;

  cout << "Graphviz:\n";
  dot(t, a);
  cout << endl;

  cout << "sum:\n";
  cout << sum(t, 4) << endl;
  cout << sum(t, 6) << endl;
  add(t, 3, -t[3]);

  print_ft(t);
  cout << endl;

  cout << sum(t, 1, 4) << endl;
}
