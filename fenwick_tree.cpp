#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

template <class T> class FenwickTree {
public:
  FenwickTree(vector<T> arr) {
    int n = arr.size();
    t.assign(n + 1, 0);
    a.assign(n + 1, 0);

    // initialize fenwick tree
    for (int k = 1; k <= n; ++k) {
      // save original values
      a[k] = arr[k - 1];

      t[k] += a[k];
      // get parent node
      auto p = k + (k & -k);

      // only update the parent node
      if (p <= n) {
        t[p] += t[k];
      }
    }
  }

  void set(size_t k, T u) {
    add(k, u - a[k]);
    a[k] = u;
  }

  void add(size_t k, T delta) {
    // start at k and propagate values upward
    while (k < t.size()) {
      t[k] += delta;
      k += (k & -k);
    }
  }

  T sum(size_t k) {
    // sum of values from k upwards
    T s = 0;
    while (k >= 1) {
      s += t[k];
      k -= (k & -k);
    }
    return s;
  }

  T sum(size_t l, size_t r) {
    auto rsum = sum(r);
    auto lsum = sum(l - 1);
    return rsum - lsum;
  }

  T at(size_t k) { return t[k]; }

  void print() {
    for (int k = 1; k < t.size(); ++k) {
      cout << t[k] << " ";
    }
  }

private:
  vector<size_t> t;
  vector<T> a;
};

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

  // vector<int> a = {1, 3, 4, 8, 6, 1, 4, 2};
  vector<int> a = {3, 2, 4, 5, 1, 1, 5, 3};

  cout << "make ft:\n";
  auto t = make_ft(a);

  print_ft(t);
  cout << endl;

  cout << "Graphviz:\n";
  dot(t, a);
  cout << endl;

  cout << "sum:\n";
  cout << sum(t, 4) << endl;
  cout << sum(t, 5, 6) << endl;

  int k = 3, u = 1;

  // add the difference of delta (u) and
  // the origina value at kth position
  add(t, k, u - a[k - 1]);
  // update the original array
  a[k - 1] = u;

  print_ft(t);
  cout << endl;

  cout << sum(t, 1, 4) << endl;

  cout << "Fenwick tree class:\n";
  // reset to original value
  a[k - 1] = 4;
  auto ft = FenwickTree<int>(a);
  cout << "sum:\n";
  cout << ft.sum(4) << endl;
  cout << ft.sum(5, 6) << endl;
  ft.set(3, 1);
  cout << ft.sum(4) << endl;

  vector<int> a2 = {4, 2, 5, 2, 1};

  cout << "Subtree query fenwick tree:" << endl;
  FenwickTree<int> ft2{a2};

  cout << endl;
  cout << ft2.sum(3, 5);
}
