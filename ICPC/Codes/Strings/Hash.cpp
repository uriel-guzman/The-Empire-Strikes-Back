struct Hash : array<int, 2> {
  static constexpr int mod = 1e9 + 7;
#define oper(op)                               \
  friend Hash operator op(Hash a, Hash b) {    \
    fore (i, 0, sz(a))                         \
      a[i] = (1LL * a[i] op b[i] + mod) % mod; \
    return a;                                  \
  }
  oper(+) oper(-) oper(*)
} pw[N], ipw[N];

struct Hashing {
  vector<Hash> h;

  Hashing(string& s) : h(sz(s) + 1) {
    fore (i, 0, sz(s)) {
      int x = s[i] - 'a' + 1;
      h[i + 1] = h[i] + pw[i] * Hash{x, x};
    }
  }

  Hash query(int l, int r) {
    return (h[r + 1] - h[l]) * ipw[l];
  }
};

#warning "Ensure all base[i] > alphabet"
pw[0] = ipw[0] = {1, 1};
Hash base = {12367453, 14567893};
Hash inv = {::inv(base[0], base.mod), ::inv(base[1], base.mod)};
fore (i, 1, N) {
  pw[i] = pw[i - 1] * base;
  ipw[i] = ipw[i - 1] * inv;
}

// Save len in the struct and when you do a cut
Hash merge(vector<Hash>& cuts) {
  Hash f = {0, 0};
  fore (i, sz(cuts), 0) {
    Hash g = cuts[i];
    f = g + f * pw[g.len];
  }
  return f;
}