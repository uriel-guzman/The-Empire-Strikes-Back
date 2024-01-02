struct Hash : array<int, 2> {
  static constexpr array<int, 2> mod = {1070777777, 1070777777};
#define oper(op)                               \
  friend Hash operator op(Hash a, Hash b) {    \
    fore (i, 0, sz(a))                         \
      a[i] = (1LL * a[i] op b[i] + mod[i]) % mod[i]; \
    return a;                                  \
  }
  oper(+) oper(-) oper(*)
} pw[N], ipw[N];

struct Hashing {
  vector<Hash> h;

  static void init() {
    #warning "Ensure all base[i] > alphabet"
    pw[0] = ipw[0] = {1, 1};
    Hash base = {12367453, 14567893};
    Hash inv = {::inv(base[0], base.mod[0]), ::inv(base[1], base.mod[1])};
    fore (i, 1, N) {
      pw[i] = pw[i - 1] * base;
      ipw[i] = ipw[i - 1] * inv;
    }
  }

  Hashing(string& s) : h(sz(s) + 1) {
    fore (i, 0, sz(s)) {
      int x = s[i] - 'a' + 1;
      h[i + 1] = h[i] + pw[i] * Hash{x, x};
    }
  }

  Hash query(int l, int r) {
    return (h[r + 1] - h[l]) * ipw[l];
  }

  lli queryVal(int l, int r) {
    Hash hash = query(l, r);
    return (1LL * hash[0] << 32) | hash[1];
  }
};

// // Save len in the struct and when you do a cut
// Hash merge(vector<Hash>& cuts) {
//   Hash f = {0, 0};
//   fore (i, sz(cuts), 0) {
//     Hash g = cuts[i];
//     f = g + f * pw[g.len];
//   }
//   return f;
// }