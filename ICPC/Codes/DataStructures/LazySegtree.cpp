struct Lazy {
  int l, r;
  lli sum = 0, lazy = 0;
  Lazy *ls, *rs;

  Lazy(int l, int r) : l(l), r(r), ls(0), rs(0) {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) >> 1;
    ls = new Lazy(l, m);
    rs = new Lazy(m + 1, r);
    pull();
  }

  void push() {
    if (!lazy)
      return;
    sum += (r - l + 1) * lazy;
    if (l != r) {
      ls->lazy += lazy;
      rs->lazy += lazy;
    }
    lazy = 0;
  }

  void pull() {
    sum = ls->sum + rs->sum;
  }

  void update(int ll, int rr, lli v) {
    push();
    if (rr < l || r < ll)
      return;
    if (ll <= l && r <= rr) {
      lazy += v;
      push();
      return;
    }
    ls->update(ll, rr, v);
    rs->update(ll, rr, v);
    pull();
  }

  lli qsum(int ll, int rr) {
    push();
    if (rr < l || r < ll)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return ls->qsum(ll, rr) + rs->qsum(ll, rr);
  }
};