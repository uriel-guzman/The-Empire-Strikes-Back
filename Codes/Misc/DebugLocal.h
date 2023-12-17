#include <bits/stdc++.h>
using namespace std;

template <class A, class B, class C>
basic_ostream<A, B>& operator<<(basic_ostream<A, B>& os, const C& c);

template <class A, class B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

template <class A, class B, class C>
basic_ostream<A, B>& operator<<(basic_ostream<A, B>& os, const C& c) {
  os << "[";
  for (const auto& x : c) {
    if (&x != &*begin(c))
      cout << ", ";
    cout << x;
  }
  return os << "]";
}

template <class T, class Container, class Compare>
ostream& operator<<(ostream& os, priority_queue<T, Container, Compare> pq) {
  vector<T> v;
  while (pq.size()) {
    v.emplace_back(pq.top());
    pq.pop();
  }
  return os << v;
}

template <class T>
ostream& operator<<(ostream& os, stack<T> s) {
  vector<T> v;
  while (s.size()) {
    v.emplace_back(s.top());
    s.pop();
  }
  return os << v;
}

template <class T>
ostream& operator<<(ostream& os, queue<T> q) {
  vector<T> v;
  while (q.size()) {
    v.emplace_back(q.front());
    q.pop();
  }
  return os << v;
}

template <class A, class B, class... Args>
basic_ostream<A, B>& operator<<(basic_ostream<A, B>& os, tuple<Args...> const& t) {
  apply(
      [&os](auto&&... args) {
        ((os << args << " "), ...);
      },
      t);
  return os;
}

void pprint(string s) {
  cout << endl;
}

const string resetColor = "\033[0m";
const string blueColor = "\033[1;34m";
const string purpleColor = "\033[3;95m";
const string greenColor = "\033[1;32m";

template <class H, class... T>
void pprint(string s, const H& h, const T&... t) {
  int bal = 0, ok = 1, pos = 0;
  while (pos < s.size()) {
    char c = s[pos];
    if (c == '\"')
      ok = 0;
    if (c == '(')
      bal++;
    if (c == ')')
      bal--;
    if (c == ',' && bal == 0) {
      string cut = s.substr(0, pos);
      replace(cut.begin(), cut.end(), '\"', char(0));
      cout << blueColor << cut << resetColor;
      break;
    }
    pos++;
  }
  if (ok) {
    cout << ": " << purpleColor << fixed << setprecision(2) << h << resetColor << ",";
  }
  pprint(s.substr(pos + 1), t...);
}

#ifdef LINE

#define debug(...) cout << greenColor << "[" << __LINE__ << "] ", pprint(string(#__VA_ARGS__) + ",", __VA_ARGS__);

#else

#define debug(...) pprint(string(#__VA_ARGS__) + ",", __VA_ARGS__);

#endif