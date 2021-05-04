struct Treap {
  static Treap *null;
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
  pair<Treap*, Treap*> split(const F &leq) { // {<= val, > val} 
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

  pair<Treap*, Treap*> leftmost(int k) {
    return split([&](Treap* n) {
      int sz = n->left->sz + 1;
      if (k >= sz) {
        k -= sz;
        return true;
      }
      return false;
    });
  }

  friend int pos(Treap *t) {
    int sz = t->left->sz;
    for (; t->par; t = t->par) {
      Treap p = t->par;
      if (p->right == t) sz += p->left->sz + 1;
    }
    return sz;
  }
} *Treap::null = new Treap;