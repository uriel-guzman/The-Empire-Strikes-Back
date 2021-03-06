struct Interval {
  int l, r;
  bool operator < (const Interval &it) const {
    return l < it.l;
  }
};

struct DisjointIntervals : set<Interval> {
  void add(int l, int r) {
    auto it = lower_bound({l, -1});
    if (it != begin() && l <= prev(it)->r)  
      l = (--it)->l;
    for (; it != end() && it->l <= r; erase(it++)) 
      r = max(r, it->r);
    insert({l, r});
  }

  void rem(int l, int r) {
    auto it = lower_bound({l, -1});
    if (it != begin() && l <= prev(it)->r)  
      --it;
    int mn = l, mx = r;
    for (; it != end() && it->l <= r; erase(it++)) 
      mn = min(mn, it->l), mx = max(mx, it->r);
    if (mn < l) insert({mn, l - 1});
    if (r < mx) insert({r + 1, mx});
  }
};