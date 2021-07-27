struct Dyn {
  int l, r;
  lli mx = -INF;
  Dyn *left, *right;

  Dyn(int l, int r) : l(l), r(r), left(0), right(0) {}

  void pull() {
    mx = max(mx, (left ? left->mx : -INF));
    mx = max(mx, (right ? right->mx : -INF));
  }

  void update(int p, lli v) {
    if (l == r) {
      mx = v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      if (!left) left = new Dyn(l, m);
      left->update(p, v);
    } else {
      if (!right) right = new Dyn(m + 1, r);
      right->update(p, v);
    }
    pull();
  }

  lli qmax(int ll, int rr) {
    if (rr < l || r < ll || r < l)
      return -INF;
    if (ll <= l && r <= rr)
      return mx;
    int m = (l + r) >> 1;
    return max((left ? left->qmax(ll, rr) : 0), 
           (right ? right->qmax(ll, rr) : 0));
  }
};

struct Seg2D {
  int x1, x2;
  Seg2D *left, *right;
  Dyn* tree;

  Seg2D(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), tree(0), left(0), right(0) {
    tree = new Dyn(y1, y2);
    if (x1 == x2) 
      return;
    int m = (x1 + x2) >> 1;
    left = new Seg2D(x1, m, y1, y2);
    right = new Seg2D(m + 1, x2, y1, y2);
  }

  void pull(int y, lli v) {
    tree->update(y, max(v, tree->qmax(y, y)));
  }

  void update(int x, int y, lli v) {
    if (x1 == x2) {
      tree->update(y, v);
      return;
    }
    int m = (x1 + x2) >> 1;
    if (x <= m)
      left->update(x, y, v);
    else
      right->update(x, y, v);
    pull(y, v);
  }

  lli qmax(int xx1, int xx2, int yy1, int yy2) {
    if (xx2 < x1 || x2 < xx1)
      return -INF;
    if (xx1 <= x1 && x2 <= xx2)
      return tree->qmax(yy1, yy2);
    return max(left->qmax(xx1, xx2, yy1, yy2), right->qmax(xx1, xx2, yy1, yy2));
  }
};
