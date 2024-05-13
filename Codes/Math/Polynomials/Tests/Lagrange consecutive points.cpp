// https://codeforces.com/group/gXivUSZQpn/contest/336740/problem/D

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r)                                      \
  for (auto i = (l) - ((l) > (r)); i != (r) - ((l) > (r)); \
       i += 1 - 2 * ((l) > (r)))
#define sz(x) int(x.size())
#define all(x) begin(x), end(x)
#define f first
#define s second
#define pb push_back

#ifdef LOCAL
#include "debug.h"
#else
#define debug(...)
#endif

using ld = long double;
using lli = long long;
using ii = pair<int, int>;
using vi = vector<int>;

template <const int M>
struct Modular {
  int v;
  Modular(int a = 0) : v(a) {}
  Modular(lli a) : v((a < 0 ? M - -a % M : a) % M) {}

  Modular operator+(Modular m) {
    return Modular((v + m.v) % M);
  }

  Modular operator-(Modular m) {
    return Modular((v - m.v + M) % M);
  }

  Modular operator*(Modular m) {
    return Modular((1LL * v * m.v) % M);
  }

  Modular operator/(Modular m) {
    return *this * m.inv();
  }

  Modular inv() {
    return this->pow(M - 2);
  }

  Modular& operator+=(Modular m) {
    return *this = *this + m;
  }

  Modular& operator-=(Modular m) {
    return *this = *this - m;
  }

  Modular& operator*=(Modular m) {
    return *this = *this * m;
  }

  Modular& operator/=(Modular m) {
    return *this = *this / m;
  }

  friend ostream& operator<<(ostream& os, Modular m) {
    return os << m.v;
  }

  template <class T>
  bool operator==(T x) {
    return v == x;
  }

  Modular pow(lli n) {
    Modular r(1), x = *this;
    for (; n > 0; n >>= 1) {
      if (n & 1)
        r = r * x;
      x = x * x;
    }
    return r;
  }
};

template <class T>
struct Lagrange {
  int n;
  vector<T> y, suf, fac;

  Lagrange(vector<T>& y) : n(sz(y)), y(y), suf(n + 1, 1), fac(n, 1) {
    fore (i, 1, n)
      fac[i] = fac[i - 1] * i;
  }

  T operator[](lli k) {
    for (int i = n - 1; i >= 0; i--) suf[i] = suf[i + 1] * (k - i);

    T pref = 1, val = 0;
    fore (i, 0, n) {
      T num = pref * suf[i + 1];
      T den = fac[i] * fac[n - 1 - i];
      if ((n - 1 - i) % 2)
        den *= -1;
      val += y[i] * num / den;
      pref *= (k - i);
    }
    return val;
  }
};

using Mint = Modular<int(1e9) + 7>;

const int N = 3005;
Mint dp[N][N];
vector<int> graph[N];
int n, d;

void dfs(int u) {
  fill(all(dp[u]), 1);

  for (auto v : graph[u]) {
    dfs(v);

    fore (k, 0, N)
      dp[u][k] *= dp[v][k];
  }

  fore (k, 1, N)
    dp[u][k] += dp[u][k - 1];
}

int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);

  while (cin >> n >> d) {
    fore (u, 0, n) {
      graph[u].clear();
      fill(all(dp[u]), 0);
    }

    fore (u, 1, n) {
      int p;
      cin >> p;
      graph[p - 1].pb(u);
    }

    dfs(0);

    vector<Mint> ways(dp[0], dp[0] + N);
    Lagrange lagrange(ways);

    cout << lagrange[d - 1] << '\n';
  }

  return 0;
}

/* Please, check the following:
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * write down your ideas
 * DON'T get stuck on ONE APPROACH!
 * ASK for HELP from your TEAMMATES
 */