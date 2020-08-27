struct Dyn {
  int l, r;
  lli sum = 0;
  Dyn *L, *R;

  Dyn(int l, int r) : l(l), r(r), L(0), R(0) {}

  void pull() {
    sum = (L ? L->sum : 0);
    sum += (R ? R->sum : 0);
  }

  void update(int p, lli v) {
    if (l == r) {
      sum += v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      if (!L)
        L = new Dyn(l, m);
      L->update(p, v);
    } else {
      if (!R)
        R = new Dyn(m + 1, r);
      R->update(p, v);
    }
    pull();
  }

  lli qsum(int ll, int rr) {
    if (rr < l || r < ll || r < l)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    int m = (l + r) >> 1;
    return (L ? L->qsum(ll, rr) : 0) + 
           (R ? R->qsum(ll, rr) : 0);
  }
};