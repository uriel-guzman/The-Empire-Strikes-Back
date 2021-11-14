typedef struct Node* Splay;
struct Node {
  Splay left = 0, right = 0, par = 0;
  bool rev = 0;
  int sz = 1;
  int sub = 0, vsub = 0; // subtree
  int path = 0; // path
  int self = 0; // node info

  void push() {
    if (rev) {
      swap(left, right);
      if (left)
        left->rev ^= 1;
      if (right)
        right->rev ^= 1;
      rev = 0;
    }
  }

  void pull() {
#define sub(u) (u ? u->sub : 0)
#define path(u) (u ? u->path : 0)
#define sz(u) (u ? u->sz : 0)
    sz = 1 + sz(left) + sz(right);
    sub = vsub + sub(left) + sub(right) + self;
    path = path(left) + self + path(right);
  }

  void virSub(Splay v, int add) {
    vsub += 1LL * add * sub(v);
  }
};

void splay(Splay u) {
  auto assign = [&](Splay u, Splay v, bool d) {
    (d == 0 ? u->left : u->right) = v;
    if (v)
      v->par = u;
  };
  auto dir = [&](Splay u) {
    Splay p = u->par;
    if (!p)
      return -1;
    return p->left == u ? 0 : (p->right == u ? 1 : -1);
  };
  auto rotate = [&](Splay u) {
    Splay p = u->par, g = p->par;
    int d = dir(u);
    assign(p, d ? u->left : u->right, d);
    if (dir(p) == -1)
      u->par = g;
    else
      assign(g, u, dir(p));
    assign(u, p, !d);
    p->pull(), u->pull();
  };
  while (~dir(u)) {
    Splay p = u->par, g = p->par;
    if (~dir(p))
      g->push();
    p->push(), u->push();
    if (~dir(p))
      rotate(dir(p) == dir(u) ? p : u);
    rotate(u);
  }
  u->push(), u->pull();
}

void access(Splay u) {
  Splay last = 0;
  for (Splay v = u; v; last = v, v = v->par) {
    splay(v);
    v->virSub(v->right, +1);
    v->virSub(v->right = last, -1);
    v->pull();
  }
  splay(u);
}

void reroot(Splay u) {
  access(u);
  u->rev ^= 1;
}

void link(Splay u, Splay v) {
  reroot(v), access(u);
  u->virSub(v, +1);
  v->par = u;
  u->pull();
}

void cut(Splay u, Splay v) {
  reroot(v), access(u);
  u->left = 0, v->par = 0;
  u->pull();
}

Splay lca(Splay u, Splay v) {
  if (u == v)
    return u;
  access(u), access(v);
  if (!u->par)
    return 0;
  return splay(u), u->par ?: u;
}

Splay queryPath(Splay u, Splay v) {
  return reroot(u), access(v), v; // path
}

Splay querySubtree(Splay u, Splay x) {
  // query subtree of u where x is outside
  return reroot(x), access(u), u; // vsub + self
}