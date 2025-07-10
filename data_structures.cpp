#include <algorithm>
#include <cstdio>
#include <deque>
#include <functional>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

using namespace std;

int main() {
  printf("---Vector examples---\n");
  printf("New vector\n");
  // vectors
  vector<int> v;
  v.push_back(3);
  v.push_back(2);
  v.push_back(5);

  for (auto e : v) {
    printf("%d ", e);
  }
  printf("\n");

  vector<int> v2 = {2, 4, 3, 5, 1};
  v2.pop_back();
  for (auto e : v2) {
    printf("%d ", e);
  }
  printf("\n");

  printf("Reversed\n");
  reverse(v2.begin(), v2.end());
  for (auto e : v2) {
    printf("%d ", e);
  }
  printf("\n");

  printf("Shuffled\n");
  random_shuffle(v2.begin(), v2.end());
  for (auto e : v2) {
    printf("%d ", e);
  }
  printf("\n");

  printf("Initialized");
  vector<int> v3(8, 1);
  for (auto e : v3) {
    printf("%d ", e);
  }
  printf("\n");

  printf("Upper/lower bound\n");
  // lower bound / upper bound
  vector<int> v4 = {2, 3, 8, 5, 7, 8, 3, 8};
  sort(v4.begin(), v4.end());
  // at least 5
  auto a = lower_bound(v4.begin(), v4.end(), 5);
  // larger than 5
  auto b = upper_bound(v4.begin(), v4.end(), 5);
  printf("a: %d, b: %d\n", *a, *b);

  printf("Unique elements\n");
  // unique elements
  v4.erase(unique(v4.begin(), v4.end()), v4.end());
  for (auto e : v4) {
    printf("%d ", e);
  }
  printf("\n");

  printf("---Deque---\n");
  deque<int> d;
  d.push_back(5);
  d.push_back(2);
  d.push_back(3);
  d.push_front(3);
  d.pop_back();
  d.pop_front();
  for (auto e : d) {
    printf("%d ", e);
  }
  printf("\n");

  printf("---Stack---");
  stack<int> st;
  st.push(2);
  st.push(5);
  printf("top: %d\n", st.top());
  st.pop();
  printf("top: %d\n", st.top());

  printf("---Queue---");
  queue<int> q;
  q.push(2);
  q.push(5);
  printf("front: %d\n", q.front());
  q.pop();
  printf("back: %d\n", q.back());

  printf("---Set---\n");
  set<int> s;
  s.insert(3);
  s.insert(3);
  s.insert(2);
  s.insert(5);
  printf("count(3): %lu\n", s.count(3));
  printf("count(4): %lu\n", s.count(4));
  s.erase(3);
  s.insert(4);
  printf("count(3): %lu\n", s.count(3));
  printf("count(4): %lu\n", s.count(4));

  auto it = s.find(10);
  if (it == s.end()) {
    printf("10 not found in set\n");
  }

  printf("---Multiset---\n");
  multiset<int> ms;
  ms.insert(5);
  ms.insert(5);
  ms.insert(5);
  printf("count(5): %lu\n", ms.count(5));
  ms.erase(ms.find(5));
  printf("count(5): %lu\n", ms.count(5));

  printf("---Map---\n");
  map<string, int> m;
  m["lorem"] = 4;
  m["ipsum"] = 3;
  m["dolor"] = 9;
  for (auto e : m) {
    printf("%s: %d\n", e.first.c_str(), e.second);
  }
  printf("count('lorem'): %lu\n", m.count("lorem"));

  printf("---Priority-Queue---\n");
  printf("Maximum\n");
  priority_queue<int> pq;
  pq.push(3);
  pq.push(5);
  pq.push(7);
  pq.push(2);
  printf("top: %d\n", pq.top());
  pq.pop();
  printf("top: %d\n", pq.top());
  pq.push(6);
  printf("top: %d\n", pq.top());
  pq.pop();

  printf("Minimum\n");
  priority_queue<int, vector<int>, greater<int>> mpq;
  mpq.push(3);
  mpq.push(5);
  mpq.push(7);
  mpq.push(2);
  printf("top: %d\n", mpq.top());
  mpq.pop();
  printf("top: %d\n", mpq.top());
  mpq.push(1);
  printf("top: %d\n", mpq.top());
  mpq.pop();
}
