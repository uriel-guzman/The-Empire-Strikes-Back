typedef struct Node* Treap;
struct Node {
  Treap ls = 0, rs = 0;
  unsigned pri = rng();
  int val, sz = 1;
  // define more variables here

  void push() {
    // propagate like segtree, values aren't modified!!
  }

  Treap pull() {
    #define sz(t) (t ? t->sz : 0)
    sz = 1 + sz(ls) + sz(rs);
    // merge(ls, this), merge(this, rs)
    return this;
  }

  Node(int val) : val(val) {}
};

template <class F>
pair<Treap, Treap> split(Treap t, const F &leq) { // {<= val, > val} 
  if (!t) return {t, t};
  t->push();
  if (leq(t)) {
    auto p = split(t->rs, leq);
    t->rs = p.f;
    return {t->pull(), p.s};
  } else {
    auto p = split(t->ls, leq);
    t->ls = p.s;
    return {p.f, t->pull()};
  }
}

Treap merge(Treap l, Treap r) {
  if (!l || !r) return l ? l : r;
  l->push(), r->push();
  if (l->pri > r->pri) 
    return l->rs = merge(l->rs, r), l->pull();
  else
    return r->ls = merge(l, r->ls), r->pull();
}

pair<Treap, Treap> leftmost(Treap t, int k) {
  return split(t, [&](Treap t) {
    int sz = sz(t->ls) + 1;
    if (k >= sz) {
      k -= sz;
      return true;
    }
    return false;
  });
}

int pos(Treap t) { // add parent in Node definition
  int sz = sz(t->ls);
  for (; t->p; t = t->p) {
    Treap p = t->p;
    if (p->rs == t) sz += sz(p->ls) + 1;
  }
  return sz + 1;
}

void insert(Treap &t, int val) {
  auto p1 = split(t, [&](Treap t) {
    return t->val <= val;
  });
  auto p2 = split(p1.f, [&](Treap t) {
    return t->val <= val - 1;
  });
  t = merge(p2.f, merge(new Node(val), p1.s));
}

void erase(Treap &t, int val) {
  auto p1 = split(t, [&](Treap t) {
    return t->val <= val;
  });
  auto p2 = split(p1.f, [&](Treap t) {
    return t->val <= val - 1;
  });
  t = merge(p2.f, p1.s);
}