struct Treap {
  static Treap* null;
  Treap *left, *right;
  unsigned pri = rng(), sz = 0;
  int val = 0;

  void push() {
    // propagate like segtree, key-values aren't modified!!
  }

  Treap* pull() {
    sz = left->sz + right->sz + (this != null);
    // merge(left, this), merge(this, right)
    return this;
  }

  Treap() { left = right = null; }

  Treap(int val) : val(val) {
    left = right = null;
    pull();
  }

  template <class F>
  pair<Treap*, Treap*> split(const F& leq) { // {<= val, > val}
    if (this == null) return {null, null};
    push();
    if (leq(this)) {
      auto p = right->split(leq);
      right = p.f;
      return {pull(), p.s};
    } else {
      auto p = left->split(leq);
      left = p.s;
      return {p.f, pull()};
    }
  }

  Treap* merge(Treap* other) {
    if (this == null) return other;
    if (other == null) return this;
    push(), other->push();
    if (pri > other->pri) {
      return right = right->merge(other), pull();
    } else {
      return other->left = merge(other->left), other->pull();
    }
  }

  pair<Treap*, Treap*> leftmost(int k) { // 1-indexed
    return split([&](Treap* n) {
      int sz = n->left->sz + 1;
      if (k >= sz) {
        k -= sz;
        return true;
      }
      return false;
    });
  }

  auto split(int x) {
    return split([&](Treap* n) { return n->val <= x; });
  }

  Treap* insert(int x) {
    auto&& [leq, ge] = split(x);
    // auto &&[le, eq] = split(x); // uncomment for set
    return leq->merge(new Treap(x))->merge(ge); // change leq for le for set
  }

  Treap* erase(int x) {
    auto&& [leq, ge] = split(x);
    auto&& [le, eq] = leq->split(x - 1);
    auto&& [kill, keep] = eq->leftmost(1); // comment for set
    return le->merge(keep)->merge(ge); // le->merge(ge) for set
  }
}* Treap::null = new Treap;