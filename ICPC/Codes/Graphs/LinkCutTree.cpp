void access(Splay u) {
  // puts u on the preferred path, splay (right subtree is empty)
  for (Splay v = u, pre = NULL; v; v = v->p) {
    v->splay(); // now pull virtual children
    if (pre) v->vsub(pre, false);
    if (v->ch[1]) v->vsub(v->ch[1], true);
    v->ch[1] = pre, v->pull(), pre = v;
  }
  u->splay();
}

void rootify(Splay u) {
  // make u root of LCT component
  access(u), u->flip ^= 1, access(u);
  assert(!u->ch[0] && !u->ch[1]);
}

Splay lca(Splay u, Splay v) {
  if (u == v) return u;
  access(u), access(v);
  if (!u->p) return NULL;
  return u->splay(), u->p ?: u;
}

bool connected(Splay u, Splay v) { 
  return lca(u, v) != NULL; 
}

void link(Splay u, Splay v) { // make u parent of v
  if (!connected(u, v)) {
    rootify(v), access(u);
    add(v, u, 0), v->pull();
  }
}

void cut(Splay u) {
  // cut u from its parent
  access(u);
  u->ch[0]->p = u->ch[0] = NULL;
  u->pull();
}

void cut(Splay u, Splay v) { // if u, v are adjacent in the tree
  cut(depth(u) > depth(v) ? u : v);
}

int depth(Splay u) {
  access(u);
  return gsz(u->ch[0]);
}

Splay getRoot(Splay u) { // get root of LCT component
  access(u);
  while (u->ch[0]) u = u->ch[0], u->push();
  return access(u), u;
}

Splay ancestor(Splay u, int k) {
  // get k-th parent on path to root
  k = depth(u) - k;
  assert(k >= 0);
  for (;; u->push()) {
    int sz = gsz(u->ch[0]);
    if (sz == k) return access(u), u;
    if (sz < k) k -= sz + 1, u = u->ch[1];
    else u = u->ch[0];
  }
  assert(0);
}

Splay query(Splay u, Splay v) { 
  return rootify(u), access(v), v;
}