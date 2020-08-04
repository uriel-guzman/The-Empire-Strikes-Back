struct Lazy {
  int l, r;
  lli sum = 0, lazy = 0;
  Lazy *L, *R;

  Lazy(int l, int r) : l(l), r(r), L(0), R(0) {}

  void push() {
    if (!lazy)
      return;
    sum += (r - l + 1) * lazy;
    if (l != r) {
      L->lazy += lazy;
      R->lazy += lazy;
    }
    lazy = 0;
  }

  void pull() {
    sum = L->sum + R->sum;
  }

  void build() {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) / 2;
    (L = new Lazy(l, m))->build();
    (R = new Lazy(m + 1, r))->build();
    pull();
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
    L->update(ll, rr, v);
    R->update(ll, rr, v);
    pull();
  }

  lli qsum(int ll, int rr) {
    push();
    if (rr < l || r < ll)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return L->qsum(ll, rr) + R->qsum(ll, rr);
  }
};
