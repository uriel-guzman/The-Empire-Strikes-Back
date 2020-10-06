struct Seg {
  int l, r;
  lli sum = 0;
  Seg *ls, *rs;

  Seg(int l, int r) : l(l), r(r), L(0), R(0) {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) >> 1;
    ls = new Seg(l, m);
    rs = new Seg(m + 1, r);
    pull();
  }

  void pull() { 
    sum = ls->sum + rs->sum; 
  }
  
  void update(int p, lli v) {
    if (l == r) {
      sum += v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
      ls->update(p, v);
    else
      rs->update(p, v);
    pull();
  }

  lli qsum(int ll, int rr) {
    if (rr < l || r < ll)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return ls->qsum(ll, rr) + rs->qsum(ll, rr);
  }
};