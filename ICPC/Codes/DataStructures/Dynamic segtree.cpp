template <class T>
struct Dyn {
  int l, r;
  Dyn *left, *right;
  T val;

  Dyn(int l, int r) : l(l), r(r), left(0), right(0) {}

  void pull() {
    val = (left ? left->val : T()) + (right ? right->val : T());
  }

  template <class... Args>
  void update(int p, const Args&... args) {
    if (l == r) {
      val = T(args...);
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      if (!left) left = new Dyn(l, m);
      left->update(p, args...);
    } else {
      if (!right) right = new Dyn(m + 1, r);
      right->update(p, args...);
    }
    pull();
  }

  T query(int ll, int rr) {
    if (rr < l || r < ll || r < l)
      return T();
    if (ll <= l && r <= rr)
      return val;
    int m = (l + r) >> 1;
    return (left ? left->query(ll, rr) : T()) + 
           (right ? right->query(ll, rr) : T());
  }
};