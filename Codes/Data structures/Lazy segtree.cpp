struct Lazy {
  int l, r;
  Lazy *left, *right;
  lli sum = 0, lazy = 0;

  Lazy(int l, int r) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      sum = a[l];
      return;
    }
    int m = (l + r) >> 1;
    left = new Lazy(l, m);
    right = new Lazy(m + 1, r);
    pull();
  }

  void push() {
    if (!lazy) return;
    sum += (r - l + 1) * lazy;
    if (l != r) {
      left->lazy += lazy;
      right->lazy += lazy;
    }
    lazy = 0;
  }

  void pull() { sum = left->sum + right->sum; }

  void update(int ll, int rr, lli v) {
    push();
    if (rr < l || r < ll) return;
    if (ll <= l && r <= rr) {
      lazy += v;
      push();
      return;
    }
    left->update(ll, rr, v);
    right->update(ll, rr, v);
    pull();
  }

  lli query(int ll, int rr) {
    push();
    if (rr < l || r < ll) return 0;
    if (ll <= l && r <= rr) return sum;
    return left->query(ll, rr) + right->query(ll, rr);
  }
};