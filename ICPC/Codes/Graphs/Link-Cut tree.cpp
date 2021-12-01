struct LinkCut {
  struct Node {
    Node *left{0}, *right{0}, *par{0};
    bool rev = 0;
    int sz = 1;
    int sub = 0, vsub = 0; // subtree
    lli path = 0; // path
    lli self = 0; // node info

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
      sz = 1;
      sub = vsub + self;
      path = self;
      if (left) {
        sz += left->sz;
        sub += left->sub;
        path += left->path;
      }
      if (right) {
        sz += right->sz;
        sub += right->sub;
        path += right->path;
      }
    }

    void addVsub(Node* v, lli add) {
      if (v)
        vsub += 1LL * add * v->sub;
    }
  };

  vector<Node> a;

  LinkCut(int n = 1) : a(n) {}

  void splay(Node* u) {
    auto assign = [&](Node* u, Node* v, int d) {
      if (v)
        v->par = u;
      if (d >= 0)
        (d == 0 ? u->left : u->right) = v;
    };
    auto dir = [&](Node* u) {
      if (!u->par)
        return -1;
      return u->par->left == u ? 0 : (u->par->right == u ? 1 : -1);
    };
    auto rotate = [&](Node* u) {
      Node *p = u->par, *g = p->par;
      int d = dir(u);
      assign(p, d ? u->left : u->right, d);
      assign(g, u, dir(p));
      assign(u, p, !d);
      p->pull(), u->pull();
    };
    while (~dir(u)) {
      Node *p = u->par, *g = p->par;
      if (~dir(p))
        g->push();
      p->push(), u->push();
      if (~dir(p))
        rotate(dir(p) == dir(u) ? p : u);
      rotate(u);
    }
    u->push(), u->pull();
  }

  void access(int u) {
    Node* last = NULL;
    for (Node* x = &a[u]; x; last = x, x = x->par) {
      splay(x);
      x->addVsub(x->right, +1);
      x->right = last;
      x->addVsub(x->right, -1);
      x->pull();
    }
    splay(&a[u]);
  }

  void reroot(int u) {
    access(u);
    a[u].rev ^= 1;
  }

  void link(int u, int v) {
    reroot(v), access(u);
    a[u].addVsub(v, +1);
    a[v].par = &a[u];
    a[u].pull();
  }

  void cut(int u, int v) {
    reroot(v), access(u);
    a[u].left = a[v].par = NULL;
    a[u].pull();
  }

  int lca(int u, int v) {
    if (u == v)
      return u;
    access(u), access(v);
    if (!a[u].par)
      return -1;
    return splay(&a[u]), a[u].par ? -1 : u;
  }

  int depth(int u) {
    access(u);
    return a[u].left ? a[u].left->sz : 0;
  }

  // get k-th parent on path to root
  int ancestor(int u, int k) {
    k = depth(u) - k;
    assert(k >= 0);
    for (;; a[u].push()) {
      int sz = a[u].left->sz;
      if (sz == k)
        return access(u), u;
      if (sz < k)
        k -= sz + 1, u = u->ch[1];
      else
        u = u->ch[0];
    }
    assert(0);
  }

  lli queryPath(int u, int v) {
    reroot(u), access(v);
    return a[v].path;
  }

  lli querySubtree(int u, int x) {
    // query subtree of u, x is outside
    reroot(x), access(u);
    return a[u].vsub + a[u].self;
  }

  void update(int u, lli val) {
    access(u);
    a[u].self = val;
    a[u].pull();
  }

  Node& operator[](int u) {
    return a[u];
  }
};
