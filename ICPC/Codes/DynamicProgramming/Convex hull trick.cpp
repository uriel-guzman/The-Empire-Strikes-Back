// for doubles, use INF = 1/.0, div(a,b) = a / b
struct Line {
  mutable lli m, c, p; 
  bool operator < (const Line &l) const { return m < l.m; }
  bool operator < (lli x) const { return p < x; }
  lli operator ()(lli x) const { return m * x + c; }
};

template <bool Max>
struct DynamicHull : multiset<Line, less<>> {
  lli div(lli a, lli b) { 
    return a / b - ((a ^ b) < 0 && a % b); 
  }
 
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = INF, 0;
    if (x->m == y->m) x->p = x->c > y->c ? INF : -INF;
    else x->p = div(x->c - y->c, y->m - x->m);
    return x->p >= y->p;
  }

  void add(lli m, lli c) {
    if (!Max) m = -m, c = -c;
    auto z = insert({m, c, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y))
      isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p)
      isect(x, erase(y));
  }

  lli query(lli x) {
    if (empty()) return 0LL;
    auto f = *lower_bound(x);
    return Max ? f(x) : -f(x); 
  }
};