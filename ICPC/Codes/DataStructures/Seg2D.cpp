struct Dyn {
  int l, r;
  lli mx = -inf;
  Dyn *ls, *rs;

  Dyn(int l, int r) : l(l), r(r), ls(0), rs(0) {}

  void pull() {
    mx = max(mx, (ls ? ls->mx : -inf));
    mx = max(mx, (rs ? rs->mx : -inf));
  }

  void update(int p, lli v) {
    if (l == r) {
      mx = v;
      return;
    }
    int m = (l + r) >> 1;
    if (p <= m) {
      if (!ls) ls = new Dyn(l, m);
      ls->update(p, v);
    } else {
      if (!rs) rs = new Dyn(m + 1, r);
      rs->update(p, v);
    }
    pull();
  }

  lli qmax(int ll, int rr) {
    if (rr < l || r < ll || r < l)
      return -inf;
    if (ll <= l && r <= rr)
      return mx;
    int m = (l + r) >> 1;
    return max((ls ? ls->qmax(ll, rr) : 0), 
           (rs ? rs->qmax(ll, rr) : 0));
  }
};

struct Seg2D {
  int x1, x2;
  Dyn* tree;
  Seg2D *ls, *rs;

  Seg2D(int x1, int x2, int y1, int y2) : x1(x1), x2(x2), tree(0), ls(0), rs(0) {
    tree = new Dyn(y1, y2);
    if (x1 == x2) 
      return;
    int m = (x1 + x2) >> 1;
    ls = new Seg2D(x1, m, y1, y2);
    rs = new Seg2D(m + 1, x2, y1, y2);
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
      ls->update(x, y, v);
    else
      rs->update(x, y, v);
    pull(y, v);
  }

  lli qmax(int xx1, int xx2, int yy1, int yy2) {
    if (xx2 < x1 || x2 < xx1)
      return -inf;
    if (xx1 <= x1 && x2 <= xx2)
      return tree->qmax(yy1, yy2);
    return max(ls->qmax(xx1, xx2, yy1, yy2), rs->qmax(xx1, xx2, yy1, yy2));
  }
};
