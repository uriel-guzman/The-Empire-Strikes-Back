typedef struct Node* Splay;
struct Node {
  Splay ch[2] = {0, 0}, p = 0;
  bool flip = 0;
  int sz = 1;

  int dir() {
    if (!p) return -2; // root of LCT component
    if (p->ch[0] == this) return 0; // left child
    if (p->ch[1] == this) return 1; // right child
    return -1; // root of current splay tree
  }

  bool isRoot() { return dir() < 0; }

  friend void add(Splay u, Splay v, int d) {
    if (v) v->p = u;
    if (d >= 0) u->ch[d] = v;
  }

  void rotate() {
    // assume p and p->p propagated
    assert(!isRoot());
    int x = dir();
    Splay g = p;
    add(g->p, this, g->dir());
    add(g, ch[x ^ 1], x);
    add(this, g, x ^ 1);
    g->pull(), pull();
  }

  void splay() {
    // bring this to top of splay tree
    while (!isRoot() && !p->isRoot()) {
      p->p->push(), p->push(), push();
      dir() == p->dir() ? p->rotate() : rotate();
      rotate();
    }
    if (!isRoot()) p->push(), push(), rotate();
    push(), pull();
  }

  void pull() { 
    #define gsz(t) (t ? t->sz : 0)
    sz = 1 + gsz(ch[0]) + gsz(ch[1]); 
  }

  void push() {
    if (flip) {
      swap(ch[0], ch[1]);
      for (auto ch : ch) if (ch) {
        ch->flip ^= 1;
      }
      flip = 0;
    }
  }

  void vsub(Splay t, bool add) {}
};