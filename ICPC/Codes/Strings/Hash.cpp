vi mod = {999727999, 999992867, 1000000123, 1000002193, 1000003211, 1000008223, 1000009999, 1000027163, 1070777777};

struct H : array<lli, 2> {
  #define oper(op) friend H operator op (H a, H b) { \
  fore (i, 0, sz(a)) a[i] = (a[i] op b[i] + mod[i]) % mod[i]; \
  return a; }
  oper(+) oper(-) oper(*)
} pw[N], ipw[N];

struct Hash {
  vector<H> h;

  Hash(string &s) : h(sz(s) + 1) {
    fore (i, 0, sz(s)) {
      int x = s[i] - 'a' + 1;
      h[i + 1] = h[i] + pw[i] * H{x, x};
    }
  }

  H cut(int l, int r) {
    return (h[r + 1] - h[l]) * ipw[l];
  }
};

const int P = uniform_int_distribution<int>(27, min(mod[0], mod[1]) - 1)(rng);
pw[0] = ipw[0] = {1, 1};
H Q = {inv(P, mod[0]), inv(P, mod[1])};
fore (i, 1, N) {
  pw[i] = pw[i - 1] * H{P, P};
  ipw[i] = ipw[i - 1] * Q;
}

// Save {l, r} in the struct and when you do a cut
H merge(vector<H> &cuts) {
  F f = {0, 0};
  fore (i, sz(cuts), 0) {
    F g = cuts[i];
    f = g + f * pw[g.r - g.l + 1];
  }
  return f;
}