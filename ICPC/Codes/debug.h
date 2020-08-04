#include <bits/stdc++.h>
using namespace std;

template <class A, class B>
ostream & operator << (ostream& os, pair<A, B> p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

template <class A, class B, class C>
basic_ostream<A, B>& operator << (basic_ostream<A, B>& os, const C& c) {
  os << "[";
  for (const auto &x : c)
    os << ", " + 2 * (&x == &*begin(c)) << x;
  return os << "]";
}

void print(string s) { cout << endl; }
template <class H, class... T>
void print(string s, H h, T... t) {
  do { cout << s[0]; s = s.substr(1);
  } while (s.size() && s[0] != ',');
  cout << ": " << h;
  print(s, t...);
}

#define debug(...) print(#__VA_ARGS__, __VA_ARGS__)