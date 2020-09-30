typedef struct Node* Splay;
struct Node {
  int val, mx = 0;
  Splay ch[2] = {0, 0}, p = 0;
  int sz = 1, flip = 0;
  Node(int val) : val(val), mx(val) {}
};

void push(Splay u) {
  if (!u || !u->flip)
    return;
  swap(u->ch[0], u->ch[1]);
  for (Splay v : u->ch)
    if (v) v->flip ^= 1;
  u->flip = 0;
}

void pull(Splay u) {
  #define gsz(t) (t ? t->sz : 0)
  u->sz = 1, u->mx = u->val;
  for (Splay v : u->ch) if (v) {
    push(v);
    u->sz += gsz(v);
    u->mx = max(u->mx, v->mx);
  }
}

int dir(Splay u) {
  if (!u->p) return -2; // root of the LCT component
  if (u->p->ch[0] == u) return 0; // left child
  if (u->p->ch[1] == u) return 1; // right child
  return -1; // root of current splay tree
}

void add(Splay u, Splay v, int d) {
  if (v) v->p = u;
  if (d >= 0) u->ch[d] = v;
}

void rot(Splay u) { // assume p and p->p propagated
  int x = dir(u);
  Splay g = u->p; 
  add(g->p, u, dir(g));
  add(g, u->ch[x ^ 1], x);
  add(u, g, x ^ 1);
  pull(g), pull(u);
}

void splay(Splay u) {
  #define isRoot(u) (dir(u) < 0)
  while (!isRoot(u) && !isRoot(u->p)) {
    push(u->p->p), push(u->p), push(u);
    rot(dir(u) == dir(u->p) ? u->p : u);
    rot(u);
  }
  if (!isRoot(u)) push(u->p), push(u), rot(u);
  push(u);
}

// puts u on the preferred path, then splay 
void access(Splay u) {
  for (Splay v = u, last = 0; v; v = v->p) {
    splay(v); 
    v->ch[1] = last, pull(v), last = v;
  }
  splay(u);
}

void rootify(Splay u) {
  access(u), u->flip ^= 1, access(u);
}

Splay lca(Splay u, Splay v) {
  if (u == v) return u;
  access(u), access(v);
  if (!u->p) return 0;
  return splay(u), u->p ?: u;
}

bool connected(Splay u, Splay v) {
  return lca(u, v);
}

void link(Splay u, Splay v) { // make u parent of v, make sure they aren't connected
  if (!connected(u, v)) {
    rootify(v), access(u);
    add(v, u, 0), pull(v);
  }
}

void cut(Splay u) { // cut u from its parent
  access(u);
  u->ch[0] = u->ch[0]->p = 0;
  pull(u);
}

void cut(Splay u, Splay v) { // if u, v adj in tree
  rootify(u), access(v), cut(v);
}

Splay getRoot(Splay u) {
  access(u);
  while (u->ch[0])
    u = u->ch[0], push(u);
  return access(u), u;
}

Splay lift(Splay u, int k) {
  push(u);
  int sz = gsz(u->ch[0]);
  if (sz == k)
    return splay(u), u;
  return k < sz ? lift(u->ch[0], k) : lift(u->ch[1], k - sz - 1);
}

Splay ancestor(Splay u, int k) {
  return access(u), lift(u, gsz(u->ch[0]) - k);
}

Splay query(Splay u, Splay v) { 
  return rootify(u), access(v), v;
}

Splay lct[N];