#include <bits/stdc++.h>
using namespace std;

template <class A, class B>
ostream & operator << (ostream &os, const pair<A, B> &p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

template <class A, class B, class C>
basic_ostream<A, B> & operator << (basic_ostream<A, B> &os, const C &c) {
  os << "[";
  for (const auto &x : c)
    os << ", " + 2 * (&x == &*begin(c)) << x;
  return os << "]";
}

void print(string s) { cout << endl; }

template <class H, class... T>
void print(string s, const H &h, const T&... t) {
  const static string reset = "\033[0m", blue = "\033[1;34m", purple = "\033[3;95m";
  bool ok = 1;
  do { 
    if (s[0] == '\"') ok = 0;
    else cout << blue << s[0] << reset;
    s = s.substr(1);
  } while (s.size() && s[0] != ',');
  if (ok) cout << ": " << purple << h << reset;
  print(s, t...);
}

#define debug(...) print(#__VA_ARGS__, __VA_ARGS__)
