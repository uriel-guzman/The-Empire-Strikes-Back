typedef struct Node* Splay;
struct Node {
  Splay l = 0, r = 0, par = 0;
  bool rev = 0;
  int sub = 1, vir = 0;
  int self = 0, path = 0;
  
  void push() {
    if (rev) {
      swap(l, r);
      if (l) l->rev ^= 1;
      if (r) r->rev ^= 1;
      rev = 0;
    }
  }

  void pull() {
    #define sub(u) (u ? u->sub : 0)
    #define path(u) (u ? u->path : 0)
    sub = vir + sub(l) + sub(r) + self;
    path = path(l) + self + path(r);
  }
};

void splay(Splay u) {
  auto assign = [&](Splay u, Splay v, bool d) {
    (d == 0 ? u->l : u->r) = v;
    if (v) v->par = u;
  };
  auto dir = [&](Splay u) {
    Splay p = u->par;
    if (!p) return -1;
    return p->l == u ? 0 : (p->r == u ? 1 : -1);
  };
  auto rotate = [&](Splay u) {
    Splay p = u->par, g = p->par;
    int d = dir(u);
    assign(p, d ? u->l : u->r, d);
    if (dir(p) == -1) u->par = g;
    else assign(g, u, dir(p));
    assign(u, p, !d);
    p->pull(), u->pull();
  };
  while (~dir(u)) {
    Splay p = u->par, g = p->par;
    if (~dir(p)) g->push();
    p->push(), u->push();
    if (~dir(p)) rotate(dir(p) == dir(u) ? p : u);
    rotate(u);
  }
  u->push(), u->pull();
}

void access(Splay u) {
  Splay last = 0;
  for (Splay v = u; v; v = v->par) {
    splay(v);
    v->vir += sub(v->r);
    v->r = last;
    v->vir -= sub(v->r);
    last = v;
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
  u->vir += sub(v);
  v->par = u;
  u->pull();
}

void cut(Splay u, Splay v) {
  reroot(v), access(u);
  u->l = 0, v->par = 0;
  u->pull();
}

Splay lca(Splay u, Splay v) {
  if (u == v) return u;
  access(u), access(v);
  if (!u->par) return 0;
  return splay(u), u->par ?: u;
}

Splay queryPath(Splay u, Splay v) { 
  return reroot(u), access(v), v; // path
}

Splay querySubtree(Splay u, Splay x) {
  // query subtree of u where x is outside
  return reroot(x), access(u), u; // vir + self
}