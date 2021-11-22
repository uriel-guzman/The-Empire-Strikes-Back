template <class T, class L>
struct Lazy {
  int l, r;
  Lazy *left, *right;
  T val;
  L lazy = {};

  template <class Arr>
  Lazy(int l, int r, const Arr& a) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      val = T(a[l]);
      return;
    }
    int m = (l + r) >> 1;
    left = new Lazy(l, m, a);
    right = new Lazy(m + 1, r, a);
    pull();
  }

  void push() {
    if (!lazy)
      return;
    val.apply(lazy, l, r);
    if (l != r) {
      left->lazy = left->lazy + lazy;
      right->lazy = right->lazy + lazy;
    }
    lazy = 0;
  }

  void pull() {
    sum = left->sum + right->sum;
  }

  void update(int ll, int rr, L v) {
    push();
    if (rr < l || r < ll)
      return;
    if (ll <= l && r <= rr) {
      lazy += v;
      push();
      return;
    }
    left->update(ll, rr, v);
    right->update(ll, rr, v);
    pull();
  }

  T query(int ll, int rr) {
    push();
    if (rr < l || r < ll)
      return T();
    if (ll <= l && r <= rr)
      return val;
    return left->query(ll, rr) + right->query(ll, rr);
  }
};