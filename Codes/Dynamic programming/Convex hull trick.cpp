// for doubles, use INF = 1/.0, div(a,b) = a / b
struct Line {
  mutable lli m, c, p;
  bool operator<(const Line& l) const { return m < l.m; }
  bool operator<(lli x) const { return p < x; }
  lli operator()(lli x) const { return m * x + c; }
};

template <bool MAX>
struct DynamicHull : multiset<Line, less<>> {
  lli div(lli a, lli b) { return a / b - ((a ^ b) < 0 && a % b); }

  bool isect(iterator i, iterator j) {
    if (j == end()) return i->p = INF, 0;
    if (i->m == j->m)
      i->p = i->c > j->c ? INF : -INF;
    else
      i->p = div(i->c - j->c, j->m - i->m);
    return i->p >= j->p;
  }

  void add(lli m, lli c) {
    if (!MAX) m = -m, c = -c;
    auto k = insert({m, c, 0}), j = k++, i = j;
    while (isect(j, k)) k = erase(k);
    if (i != begin() && isect(--i, j)) isect(i, j = erase(j));
    while ((j = i) != begin() && (--i)->p >= j->p) isect(i, erase(j));
  }

  lli query(lli x) {
    if (empty()) return 0LL;
    auto f = *lower_bound(x);
    return MAX ? f(x) : -f(x);
  }
};