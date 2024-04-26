struct LiChao {
  struct Fun {
    lli m = 0, c = -INF;
    lli operator()(lli x) const { return m * x + c; }
  } f;

  lli l, r;
  LiChao *left, *right;
  LiChao(lli l, lli r, Fun f) : l(l), r(r), f(f), left(0), right(0) {}

  void add(Fun& g) {
    lli m = (l + r) >> 1;
    bool bl = g(l) > f(l), bm = g(m) > f(m);
    if (bm) swap(f, g);
    if (l == r) return;
    if (bl != bm)
      left ? left->add(g) : void(left = new LiChao(l, m, g));
    else
      right ? right->add(g) : void(right = new LiChao(m + 1, r, g));
  }

  lli query(lli x) {
    if (l == r) return f(x);
    lli m = (l + r) >> 1;
    if (x <= m) return max(f(x), left ? left->query(x) : -INF);
    return max(f(x), right ? right->query(x) : -INF);
  }
};