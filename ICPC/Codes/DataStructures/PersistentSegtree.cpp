struct Per {
  int l, r;
  lli sum = 0;
  Per *L, *R;

  Per(int l, int r) : l(l), r(r), L(0), R(0) {}

  Per* pull() {
    sum = L->sum + R->sum;
    return this;
  }

  void build() {
    if (l == r)
      return;
    int m = (l + r) >> 1;
    (L = new Per(l, m))->build();
    (R = new Per(m + 1, r))->build();
    pull();
  }

  Per* update(int p, lli v) {
    if (p < l || r < p)
      return this;
    Per* t = new Per(l, r);
    if (l == r) {
      t->sum = v;
      return t;
    }
    t->L = L->update(p, v);
    t->R = R->update(p, v);
    return t->pull();
  }

  lli qsum(int ll, int rr) {
    if (r < ll || rr < l)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return L->qsum(ll, rr) + R->qsum(ll, rr);
  }
};