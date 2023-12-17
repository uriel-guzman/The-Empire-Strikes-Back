// https://vjudge.net/problem/CodeChef-GENETICS

#include <bits/stdc++.h>
using namespace std;

#define fore(i, l, r) for (auto i = (l); i < (r); i++)
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int K = 4;
int f[26];

struct PerTreap {
  static PerTreap* null;
  PerTreap *left, *right;
  unsigned pri = rng(), sz = 0;

  array<int, K> cnt;
  int c;

  void push() {
    // propagate like segtree, key-values aren't modified!!
  }

  PerTreap* pull() {
    sz = left->sz + right->sz + (this != null);
    fore (i, 0, K) {
      cnt[i] = left->cnt[i] + right->cnt[i];
    }
    if (c != -1)
      cnt[c]++;
    return this;
  }

  PerTreap() {
    left = right = null;
  }

  PerTreap(int c) : c(c) {
    left = right = null;
    pull();
  }

  PerTreap(PerTreap* t) : c(t->c), cnt(t->cnt), left(t->left), right(t->right), pri(t->pri), sz(t->sz) {}

  template <class F>
  pair<PerTreap*, PerTreap*> split(const F& leq) { // {<= val, > val}
    if (this == null)
      return {null, null};
    push();
    PerTreap* t = new PerTreap(this);
    if (leq(this)) {
      auto p = t->right->split(leq);
      t->right = p.f;
      return {t->pull(), p.s};
    } else {
      auto p = t->left->split(leq);
      t->left = p.s;
      return {p.f, t->pull()};
    }
  }

  PerTreap* merge(PerTreap* other) {
    if (this == null)
      return new PerTreap(other);
    if (other == null)
      return new PerTreap(this);
    push(), other->push();
    PerTreap* t;
    if (pri > other->pri) {
      t = new PerTreap(this);
      t->right = t->right->merge(other);
    } else {
      t = new PerTreap(other);
      t->left = merge(t->left);
    }
    return t->pull();
  }

  auto leftmost(int k) { // 1-indexed
    return split([&](PerTreap* n) {
      int sz = n->left->sz + 1;
      if (k >= sz) {
        k -= sz;
        return true;
      }
      return false;
    });
  }

  void tour() {
    if (this == null) {
      return;
    }
    left->tour();
    cout << "AGTC"[c];
    right->tour();
  }
}* PerTreap::null = new PerTreap;

void print(PerTreap*& t) {
#ifdef LOCAL
  if (t->sz == 0) {
    cout << "null";
  } else {
    t->tour();
  }
  debug("");
#endif
}

void printAll(vector<PerTreap*>& treaps) {
#ifdef LOCAL
  debug("------");
  debug("all treaps");
  int id = 0;
  for (auto& t : treaps) {
    debug(id);
    print(t);
    id++;
  }
  debug("");
#endif
}

int main() {
  cin.tie(0)->sync_with_stdio(0), cout.tie(0);

  f['A' - 'A'] = 0;
  f['G' - 'A'] = 1;
  f['T' - 'A'] = 2;
  f['C' - 'A'] = 3;

  int n;
  cin >> n;
  vector<PerTreap*> treaps = {PerTreap::null};
  fore (i, 0, n) {
    string s;
    cin >> s;

    PerTreap* t = PerTreap::null;
    for (char c : s) {
      t = t->merge(new PerTreap(f[c - 'A']));
    }
    treaps.emplace_back(t);
  }

  debug(treaps.size());
  printAll(treaps);

  int q;
  cin >> q;
  string op;
  int id, id2, k, k2;
  char m;
  while (q--) {
    cin >> op;

    debug(op);

    if (op == "CROSS") {
      // cross operation – they take DNA1 and DNA2 and numbers k1 and k2.
      // Then two new DNAs are created:
      // DNA3 = DNA1[1..k1] + DNA2[k2+1..] and
      // DNA4 = DNA2[1..k2] + DNA1[k1+1..].
      cin >> id >> id2 >> k >> k2;

      printAll(treaps);

      auto t1 = treaps[id]->leftmost(k);
      auto t2 = treaps[id2]->leftmost(k2);

      debug(id, k);
      print(treaps[id]);
      print(t1.f);
      print(t1.s);

      debug(id2, k2);
      print(treaps[id2]);
      print(t2.f);
      print(t2.s);

      treaps.emplace_back(t1.f->merge(t2.s));
      treaps.emplace_back(t2.f->merge(t1.s));

    } else if (op == "MUTATE") {
      // mutate operation – they take a DNA, number k and one of the bases. Then they replace the base in position k in DNA with that base. also they
      // need to know certain characteristics of those DNAs. So they can perform

      cin >> id >> k >> m;

      debug(id, k, m);
      print(treaps[id]);

      auto p1 = treaps[id]->leftmost(k - 1);
      auto p2 = p1.s->leftmost(1);

      print(p1.f);
      print(p2.f);
      print(p2.s);

      treaps[id] = p1.f->merge(new PerTreap(f[m - 'A']))->merge(p2.s);

    } else {
      // count operation – they take DNA and numbers k1 and k2 (k1 <= k2). This operation should return the number of A, G, T, C bases in DNA[k1..k2].

      cin >> id >> k >> k2;

      debug(id, k, k2);
      print(treaps[id]);

      auto p1 = treaps[id]->leftmost(k2);
      auto p2 = p1.f->leftmost(k - 1);

      print(p2.s);

      fore (i, 0, K) {
        cout << p2.s->cnt[i] << " \n"[i == K - 1];
      }
    }

    printAll(treaps);
    debug("");
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