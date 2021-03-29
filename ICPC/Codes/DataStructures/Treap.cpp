typedef struct Node* Treap;
struct Node {
  Treap left = 0, right = 0;
  unsigned pri = rng();
  int val, sz = 1;
  // define more variables here

  void push() {
    // propagate like segtree, values aren't modified!!
  }

  Treap pull() {
    #define sz(t) (t ? t->sz : 0)
    sz = 1 + sz(left) + sz(right);
    // merge(l, this), merge(this, r)
    return this;
  }

  Node(int val) : val(val) {
    pull();
  }
};

template <class F>
pair<Treap, Treap> split(Treap t, const F &leq) { // {<= val, > val} 
  if (!t) return {t, t};
  t->push();
  if (leq(t)) {
    auto p = split(t->right, leq);
    t->right = p.f;
    return {t->pull(), p.s};
  } else {
    auto p = split(t->left, leq);
    t->left = p.s;
    return {p.f, t->pull()};
  }
}

Treap merge(Treap l, Treap r) {
  if (!l || !r) return l ? l : r;
  l->push(), r->push();
  if (l->pri > r->pri) 
    return l->right = merge(l->right, r), l->pull();
  else
    return r->left = merge(l, r->left), r->pull();
}

pair<Treap, Treap> leftmost(Treap t, int k) {
  return split(t, [&](Treap t) {
    int sz = sz(t->left) + 1;
    if (k >= sz) {
      k -= sz;
      return true;
    }
    return false;
  });
}

int pos(Treap t) { // add parent in Node definition
  int sz = sz(t->left);
  for (; t->par; t = t->par) {
    Treap p = t->par;
    if (p->right == t) sz += sz(p->left) + 1;
  }
  return sz + 1;
}

pair<Treap, Treap> split(Treap t, int val) {
  return split(t, [&](Treap t) {
    return t->val <= val;
  });
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