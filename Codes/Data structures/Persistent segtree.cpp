template <class T>
struct Per {
  int l, r;
  Per *left, *right;
  T val;

  Per(int l, int r) : l(l), r(r), left(0), right(0) {}

  Per* pull() {
    val = left->val + right->val;
    return this;
  }

  void build() {
    if (l == r) return;
    int m = (l + r) >> 1;
    (left = new Per(l, m))->build();
    (right = new Per(m + 1, r))->build();
    pull();
  }

  template <class... Args>
  Per* update(int p, const Args&... args) {
    if (p < l || r < p) return this;
    Per* t = new Per(l, r);
    if (l == r) {
      t->val = T(args...);
      return t;
    }
    t->left = left->update(p, args...);
    t->right = right->update(p, args...);
    return t->pull();
  }

  T query(int ll, int rr) {
    if (r < ll || rr < l) return T();
    if (ll <= l && r <= rr) return val;
    return left->query(ll, rr) + right->query(ll, rr);
  }
};