template <class T>
struct Seg {
  int l, r;
  Seg *left, *right;
  T val;

  template <class Arr>
  Seg(int l, int r, Arr a) : l(l), r(r), left(0), right(0) {
    if (l == r) {
      val = T(a[l]);
      return;
    }
    int m = (l + r) >> 1;
    left = new Seg(l, m, a);
    right = new Seg(m + 1, r, a);
    pull();
  }

  void pull() { 
    val = left->val + right->val; 
  }
  
  template <class... Args>
  void update(int p, const Args&... args) {
    if (l == r) {
      val = T(args...);
      return;
    }
    int m = (l + r) >> 1;
    (p <= m ? left : right)->update(p, args...);
    pull();
  }
  
  T query(int ll, int rr) {
    if (rr < l || r < ll)
      return T();
    if (ll <= l && r <= rr)
      return val;
    return left->query(ll, rr) + right->query(ll, rr);
  }
};