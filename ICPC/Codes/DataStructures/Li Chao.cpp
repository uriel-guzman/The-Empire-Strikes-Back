struct Fun {
  lli m = 0, c = INF;
  lli operator()(lli x) const {
    return m * x + c;
  }
};

struct LiChao {
  lli l, r;
  LiChao *left, *right;
  Fun f;

  LiChao(lli l, lli r, Fun f) : l(l), r(r), f(f) left(0), right(0) {}

  void add(Fun& g) {
    if (f(l) <= g(l) && f(r) <= g(r))
      return;
    if (g(l) < f(l) && g(r) < f(r)) {
      f = g;
      return;
    }
    lli m = (l + r) >> 1;
    if (g(m) < f(m))
      swap(f, g);
    if (g(l) <= f(l))
      left = left ? (left->add(g), left) : new LiChao(l, m, g);
    else
      right = right ? (right->add(g), right) : new LiChao(m + 1, r, g);
  }

  lli query(lli x) {
    if (l == r)
      return f(x);
    lli m = (l + r) >> 1;
    if (x <= m)
      return min(f(x), left ? left->query(x) : INF);
    return min(f(x), right ? right->query(x) : INF);
  }
};
