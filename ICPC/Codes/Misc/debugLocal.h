#include <bits/stdc++.h>
using namespace std;

template <class A, class B>
ostream& operator<<(ostream& os, const pair<A, B>& p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

template <class A, class B, class C>
basic_ostream<A, B>& operator<<(basic_ostream<A, B>& os, const C& c) {
  os << "[";
  for (const auto& x : c)
    os << ", " + 2 * (&x == &*begin(c)) << x;
  return os << "]";
}

void print(string s) {
  cout << endl;
}

template <class H, class... T>
void print(string s, const H& h, const T&... t) {
  const string reset = "\033[0m", blue = "\033[1;34m", purple = "\033[3;95m";
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
      cout << blue << cut << reset;
      break;
    }
    pos++;
  }
  if (ok)
    cout << ": " << purple << h << reset << ",";
  print(s.substr(pos + 1), t...);
}

#define debug(...) print(string(#__VA_ARGS__) + ",", __VA_ARGS__)
