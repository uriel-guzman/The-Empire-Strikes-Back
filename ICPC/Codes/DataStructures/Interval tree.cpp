struct Interval {
  lli l, r, i;
};

struct ITree {
  ITree *left, *right;
  vector<Interval> cur;
  lli m;

  ITree(vector<Interval> &vec, lli l = LLONG_MAX, lli r = LLONG_MIN) : left(0), right(0) {
    if (l > r) { // not sorted yet
      sort(all(vec), [&](Interval a, Interval b) {
        return a.l < b.l;
      });
      for (auto it : vec) 
        l = min(l, it.l), r = max(r, it.r);
    }
    m = (l + r) >> 1;
    vector<Interval> lo, hi;
    for (auto it : vec) 
      (it.r < m ? lo : m < it.l ? hi : cur).pb(it);
    if (!lo.empty())
      left = new ITree(lo, l, m);
    if (!hi.empty())
      right = new ITree(hi, m + 1, r);
  }  

  template <class F>
  void near(lli l, lli r, F f) {
    if (!cur.empty() && !(r < cur.front().l)) {
      for (auto &it : cur)
        f(it);
    }
    if (left && l <= m)
      left->near(l, r, f);
    if (right && m < r)
      right->near(l, r, f);
  }

  template <class F>
  void overlapping(lli l, lli r, F f) {
    near(l, r, [&](Interval it) {
      if (l <= it.r && it.l <= r)
        f(it);
    });
  }

  template <class F>
  void contained(lli l, lli r, F f) {
    near(l, r, [&](Interval it) {
      if (l <= it.l && it.r <= r)
        f(it);
    });
  }
};
