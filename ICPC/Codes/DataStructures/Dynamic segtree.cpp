struct Dyn {
  int l, r;
  lli sum = 0;
  Dyn *ls, *rs;

  Dyn(int l, int r) : l(l), r(r), ls(0), rs(0) {}

  void pull() {
    sum = (ls ? ls->sum : 0);
    sum += (rs ? rs->sum : 0);
  }

  void update(int p, lli v) {
    if (l == r) {
      sum += v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      if (!ls) ls = new Dyn(l, m);
      ls->update(p, v);
    } else {
      if (!rs) rs = new Dyn(m + 1, r);
      rs->update(p, v);
    }
    pull();
  }

  lli qsum(int ll, int rr) {
    if (rr < l || r < ll || r < l)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    int m = (l + r) >> 1;
    return (ls ? ls->qsum(ll, rr) : 0) + 
           (rs ? rs->qsum(ll, rr) : 0);
  }
};
