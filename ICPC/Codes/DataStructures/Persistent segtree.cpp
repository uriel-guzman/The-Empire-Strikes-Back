struct Per {
  int l, r;
  lli sum = 0;
  Per *ls, *rs;

  Per(int l, int r) : l(l), r(r), ls(0), rs(0) {}

  Per* pull() {
    sum = ls->sum + rs->sum;
    return this;
  }

  void build() {
    if (l == r)
      return;
    int m = (l + r) >> 1;
    (ls = new Per(l, m))->build();
    (rs = new Per(m + 1, r))->build();
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
    t->ls = ls->update(p, v);
    t->rs = rs->update(p, v);
    return t->pull();
  }

  lli qsum(int ll, int rr) {
    if (r < ll || rr < l)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return ls->qsum(ll, rr) + rs->qsum(ll, rr);
  }
};
