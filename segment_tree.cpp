#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

const int INF = 1e9;

void print_vector(vector<int> v) {
  for (auto e : v) {
    cout << e << " ";
  }

  cout << endl;
}

void st_dot(vector<int> t) {

  // define the nodes
  for (size_t i = 1; i < t.size(); ++i) {
    printf("%lu [label=%d]\n", i, t[i]);
  }

  // define the connections
  for (size_t i = 2; i < t.size(); ++i) {
    printf("%lu->%lu[label=%lu]\n", i, i / 2, i);
  }
}

int sum(const vector<int>& t, size_t n, size_t l, size_t r) {
  // shift indices
  l += n;
  r += n;

  // we want to add only the top-most
  // values of the range

  int s = 0;
  while (l <= r) {
    printf("l: %lu, r: %lu\n", l, r);

    // why does l have to be a right child to be added to the sum?
    if ((l % 2) == 1) {
      printf("left +%d\n", t[l]);
      s += t[l++];
    }

    // why does r have to be a right child to be added to the sum?
    if ((r % 2) == 0) {
      printf("right +%d\n", t[r]);
      s += t[r--];
    }

    // move up one level
    l /= 2;
    r /= 2;
  }

  return s;
}

int minimum(const vector<int>& t, size_t n, size_t l, size_t r) {
  // shift indices
  l += n;
  r += n;

  int m = INF;
  while (l <= r) {
    printf("l: %lu, r: %lu\n", l, r);
    if ((l % 2) == 1) {
      m = min(m, t[l++]);
      printf("minl: %d\n", m);
    }

    if ((r % 2) == 0) {
      m = min(m, t[r--]);
      printf("minr: %d\n", m);
    }

    // move up one level
    l /= 2;
    r /= 2;
  }

  return m;
}

void add(vector<int>& t, size_t n, size_t k, int x) {
  k += n;
  t[k] += x;

  for (k /= 2; k >= 1; k /= 2) {
    t[k] = t[2 * k] + t[2 * k + 1];
  }
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  vector<int> a = {5, 8, 6, 3, 2, 7, 2, 6};
  auto n = a.size();

  vector<int> st(n * 2);
  copy(a.begin(), a.end(), st.begin() + n);

  print_vector(st);

  for (size_t i = n - 1; i > 0; --i) {
    st[i] = st[i * 2] + st[i * 2 + 1];
  }

  print_vector(st);

  //   cout << "Graphviz:\n";
  //   st_dot(t);
  //   cout << endl;

  // ranges are 0-based
  size_t l = 0, r = 3;
  printf("sum(%lu, %lu)\n", l, r);
  int s = sum(st, n, l, r);
  cout << s << endl;

  vector<int> a2 = {5, 8, 6, 3, 1, 7, 2, 6};
  vector<int> mt(n * 2);
  copy(a2.begin(), a2.end(), mt.begin() + n);

  for (size_t i = n - 1; i > 0; --i) {
    mt[i] = min(mt[i * 2], mt[i * 2 + 1]);
  }

  print_vector(mt);
  //   st_dot(mt);

  l = 0, r = 3;
  printf("min(%lu, %lu)\n", l, r);
  int m = minimum(mt, n, l, r);
  cout << m << endl;
}
