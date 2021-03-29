struct Dyn {
  int l, r;
  Dyn *left, *right;
  lli sum = 0;

  Dyn(int l, int r) : l(l), r(r), left(0), right(0) {}

  void pull() {
    sum = (left ? left->sum : 0);
    sum += (right ? right->sum : 0);
  }

  void update(int p, lli v) {
    if (l == r) {
      sum += v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      if (!left) left = new Dyn(l, m);
      left->update(p, v);
    } else {
      if (!right) right = new Dyn(m + 1, r);
      right->update(p, v);
    }
    pull();
  }

  lli query(int ll, int rr) {
    if (rr < l || r < ll || r < l)
      return 0;
    if (ll <= l && r <= rr)
      return sum;
    int m = (l + r) >> 1;
    return (left ? left->query(ll, rr) : 0) + 
           (right ? right->query(ll, rr) : 0);
  }
};
