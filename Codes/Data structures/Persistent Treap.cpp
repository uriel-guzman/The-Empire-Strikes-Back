struct PerTreap {
  static PerTreap* null;
  PerTreap *left, *right;
  unsigned pri = rng(), sz = 0;
  int val;

  void push() {
    // propagate like segtree, key-values aren't modified!!
  }

  PerTreap* pull() {
    sz = left->sz + right->sz + (this != null);
    // merge(left, this), merge(this, right)
    return this;
  }

  PerTreap(int val = 0) : val(val) {
    left = right = null;
    pull();
  }

  PerTreap(PerTreap* t)
      : left(t->left), right(t->right), pri(t->pri), sz(t->sz) {
    val = t->val;
  }

  template <class F>
  pair<PerTreap*, PerTreap*> split(const F& leq) { // {<= val, > val}
    if (this == null)
      return {null, null};
    push();
    PerTreap* t = new PerTreap(this);
    if (leq(this)) {
      auto p = t->right->split(leq);
      t->right = p.f;
      return {t->pull(), p.s};
    } else {
      auto p = t->left->split(leq);
      t->left = p.s;
      return {p.f, t->pull()};
    }
  }

  PerTreap* merge(PerTreap* other) {
    if (this == null)
      return new PerTreap(other);
    if (other == null)
      return new PerTreap(this);
    push(), other->push();
    PerTreap* t;
    if (pri > other->pri) {
      t = new PerTreap(this);
      t->right = t->right->merge(other);
    } else {
      t = new PerTreap(other);
      t->left = merge(t->left);
    }
    return t->pull();
  }

  auto leftmost(int k) { // 1-indexed
    return split([&](PerTreap* n) {
      int sz = n->left->sz + 1;
      if (k >= sz) {
        k -= sz;
        return true;
      }
      return false;
    });
  }

  auto split(int x) {
    return split([&](PerTreap* n) { return n->val <= x; });
  }
}* PerTreap::null = new PerTreap;