struct Interval {
  int l, r = -1;
  mutable int v = 0;
  
  bool operator < (const Interval &i) const { 
    return l < i.l; 
  }
};

struct Chtholly : set<Interval> {
  iterator split(int x) {
    auto it = lower_bound({x});
    if (it != end() && x == it->l)
      return it;
    if (it->r < x) return end(); 
    int r = (--it)->r;
    it->r = x - 1;
    return insert({x, r, it->v}).first;
  }

  void assign(int l, int r, int v) {
    auto lo = split(l), hi = split(r + 1);
    // Some stuff with [lo, hi]
    erase(lo, hi);
    insert({l, r, v});
  }

  void add(int l, int r, int v) {
    auto lo = split(l), hi = split(r + 1);
    for (auto it = lo; it != hi; it++)
      it->v += v;
  }
};
