struct Seg {
  int l, r;
  lli sum = 0;
  Seg *L, *R;

  Seg(int l, int r) : l(l), r(r), L(0), R(0) {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) >> 1;
    L = new Seg(l, m);
    R = new Seg(m + 1, r);
    pull();
  }

  void pull() { 
    sum = L->sum + R->sum; 
  }
  
  void update(int p, lli v) {
    if (l == r) {
      sum += v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
      L->update(p, v);
    else
      R->update(p, v);
    pull();
  }

  lli qsum(int ll, int rr) {
    if (rr < l || r < ll)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return L->qsum(ll, rr) + R->qsum(ll, rr);
  }
};