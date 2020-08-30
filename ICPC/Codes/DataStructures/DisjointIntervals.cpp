struct Range {
  int l, r;
  bool operator < (const Range& rge) const {
    return l < rge.l;
  }
};

struct DisjointIntervals : set<Range> {
  void add(Range rge) {
    iterator p = lower_bound(rge), q = p; 
    if (p != begin() && rge.l <= (--p)->r)
      rge.l = p->l, --q;
    for (; q != end() && q->l <= rge.r; erase(q++))
      rge.r = max(rge.r, q->r);
    insert(rge); 
  }

  void add(int l, int r) {
    add(Range{l, r});
  }
};