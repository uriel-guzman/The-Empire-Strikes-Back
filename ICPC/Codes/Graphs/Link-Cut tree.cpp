typedef struct Node* Splay;
struct Node {
  Splay l = 0, r = 0, par = 0;
  int sub = 1, vir = 0;
  bool rev = 0;
  int self, path;
};

void push(Splay u) {
  if (u && u->rev) {
    swap(u->l, u->r);
    if (u->l) u->l->rev ^= 1;
    if (u->r) u->r->rev ^= 1;
    u->rev = 0;
  }
}

void pull(Splay u) {
  #define sub(u) (u ? u->sub : 0)
  #define path(u) (u ? u->path : 0)
  if (u) {
    u->sub = u->vir + sub(u->l) + sub(u->r) + u->self;
    u->path = path(u->l) + u->self + path(u->r);
  }
}

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
  };
  while (~dir(u)) {
    Splay p = u->par, g = p->par;
    push(g), push(p), push(u);
    if (~dir(p)) rotate(dir(u) == dir(p) ? p : u);
    rotate(u);
    pull(g), pull(p), pull(u);
  }
  push(u);
}

void access(Splay u) {
  Splay last = 0;
  for (Splay v = u; v; v = v->par) {
    splay(v);
    v->vir += sub(v->r);
    v->r = last;
    v->vir -= sub(v->r);
    last = v;
    pull(v);
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
  pull(u);
}

void cut(Splay u, Splay v) {
  reroot(v), access(u);
  u->l = 0, v->par = 0;
  pull(u);
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

Splay querySubtree(Splay u, Splay v) {
  return reroot(u), access(v), v; // vir + self
}