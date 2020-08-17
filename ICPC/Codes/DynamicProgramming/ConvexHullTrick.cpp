// for doubles, use inf = 1/.0, div(a,b) = a / b
struct Line {
  mutable lli m, c, p; 
  bool operator < (const Line &l) const { return m < l.m; }
  bool operator < (lli x) const { return p < x; }
  lli operator ()(lli x) const { return m * x + c; }
};

lli bet(const Line &a, const Line &b) {
  if (a.m == b.m)
    return a.c > b.c ? inf : -inf;
  // can just be a / b?
  return (b.c - a.c) / (a.m - b.m);
  // lli divi(lli a, lli b) { return a / b - ((a ^ b) < 0 && a % b); }
  // return divi(b.c - a.c, a.m - b.m); 
}

struct DynamicHull : multiset<Line, less<>> {
  bool isect(iterator x, iterator y) {
    if (y == end()) {
      x->p = inf;
      return 0;
    }
    x->p = bet(*x, *y);
    return x->p >= y->p;
  }

  void add(lli m, lli c) {
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
    return f(x); 
  }
};

// NOT TESTED YET
struct Hull : deque<Line> { 
  void addBack(Line l) { // assume non empty
    while (1) {
      auto a = back(); 
      pop_back(); 
      a.p = bet(a, l);
      if (size() && back().p >= a.p) 
        continue;
      push_back(a); 
      break;
    }
    l.p = inf; 
    push_back(l);
  }

  void addFront(Line l) {
    while (1) {
      if (!size()) { 
        l.p = inf; 
        break; 
      }
      if ((l.p = bet(l,front())) >= front().p) 
        pop_front();
      else 
        break;
    }
    push_front(l);
  }

  void add(lli m, lli c) { // line goes to one end of deque
    if (!size() || m <= front().m) 
      addFront({m, c, 0});
    else assert(m >= back().m), 
      addBack({m, c, 0});
  }

  int ord = 0; // 1 = increasing, -1 = decreasing
  lli query(lli x) { 
    assert(ord);
    if (ord == 1) { 
    while (front().p < x) 
      pop_front();
      return front()(x);
    } 
    while(size() > 1 && prev(prev(end()))->p >= x) 
      pop_back();
    return back()(x);
  }	
};