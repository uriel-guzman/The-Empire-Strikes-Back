typedef struct Node* Treap;
struct Node {
  Treap ls = 0, rs = 0;
  unsigned pri = rng();
  int val, sz = 1;
  // define more variable here

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

pair<Treap, Treap> split(Treap t, int val) { // {<= val, > val} 
  if (!t) return {t, t};
  t->push();
  if (val < t->val) {
    auto p = split(t->ls, val);
    t->ls = p.s;
    return {p.f, t->pull()};
  } else {
    auto p = split(t->rs, val);
    t->rs = p.f;
    return {t->pull(), p.s};
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

void insert(Treap &t, int val) {
  auto p1 = split(t, val);
  auto p2 = split(p1.f, val - 1);
  t = merge(p2.f, merge(new Node(val), p1.s));
}

void erase(Treap &t, int val) {
  auto p1 = split(t, val);
  auto p2 = split(p1.f, val - 1);
  t = merge(p2.f, p1.s);
}

// Use this split for implicit treap aka rope
pair<Treap, Treap> split(Treap t, int sz) {
  if (!t) return {t, t};
  t->push();
  if (sz <= sz(t->ls)) {
    auto p = split(t->ls, sz);
    t->ls = p.s;
    return {p.f, t->pull()};
  } else {
    auto p = split(t->rs, sz - sz(t->ls) - 1);
    t->rs = p.f;
    return {t->pull(), p.s};
  }
}

int pos(Treap t) { // add parent in Node definition
  int sz = sz(t->ls);
  for (; t->par; t = t->par) {
    Treap par = t->par;
    if (par->rs == t) sz += sz(par->ls) + 1;
  }
  return sz + 1;
}