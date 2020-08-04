// I don't know if this works !!!

typedef struct Node* Splay;
struct Node {
  int v, mx = 0;
  Splay ch[2], p;
  int sz = 1, flip = 0;

  Node(int v = 0) : v(v) { ch[0] = ch[1] = p = 0; }

  void push() {
    if (flip) {
      swap(ch[0], ch[1]);
      fore(i, 0, 2) if (ch[i]) { ch[i]->flip ^= 1; }
      flip = 0;
    }
  }

  void pull() {
    sz = 1, mx = v;
    fore(i, 0, 2) if (ch[i]) {
      ch[i]->push();
      mx = max(mx, ch[i]->mx);
      sz += ch[i]->sz;
    }
  }

  int dir() {
    if (!p) return -2;  // root of the LCT component
    fore(i, 0, 2) if (p->ch[i] == this) {
      return i;  // i-th child
    }
    return -1;  // root of current splay tree
  }

  bool isRoot() { return dir() < 0; }

  void set(Splay u, Splay v, int d) {
    if (v) v->p = u;
    if (d >= 0) u->ch[d] = v;
  }

  void rot() {  // assume p and p->p propagated
    int x = dir();
    Splay g = p;
    set(g->p, this, g->dir());
    set(g, ch[x ^ 1], x);
    set(this, g, x ^ 1);
    g->pull(), pull();
  }

  void splay() {
    while (!isRoot() && !p->isRoot()) {
      p->p->push(), p->push(), push();
      dir() == p->dir() ? p->rot() : rot();
      rot();
    }
    if (!isRoot()) p->push(), push(), rot();
    push();
  }
};

// I don't know if this works !!!