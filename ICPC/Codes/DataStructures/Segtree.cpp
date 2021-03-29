struct Seg {
  int l, r;
  Seg *left, *right;
  lli sum = 0;

  Seg(int l, int r) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) >> 1;
    left = new Seg(l, m);
    right = new Seg(m + 1, r);
    pull();
  }

  void pull() { 
    sum = left->sum + right->sum; 
  }
  
  void update(int p, lli v) {
    if (l == r) {
      sum += v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m)
      left->update(p, v);
    else
      right->update(p, v);
    pull();
  }

  lli query(int ll, int rr) {
    if (rr < l || r < ll)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    return left->query(ll, rr) + right->query(ll, rr);
  }
};