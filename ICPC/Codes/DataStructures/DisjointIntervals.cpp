struct Interval {
  int l, r;
  bool operator < (const Interval &it) const {
    return l < it.l;
  }
};

struct DisjointIntervals : set<Interval> {
  void add(Interval it) {
    iterator p = lower_bound(it), q = p; 
    if (p != begin() && it.l <= (--p)->r)
      it.l = p->l, --q;
    for (; q != end() && q->l <= it.r; erase(q++))
      it.r = max(it.r, q->r);
    insert(it); 
  }

  void add(int l, int r) {
    add(Interval{l, r});
  }
};