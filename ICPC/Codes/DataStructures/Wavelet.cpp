struct Wav {
  #define iter int * // vector<int>::iterator
  int lo, hi;
  Wav *L, *R;
  vi amt;

  Wav(int lo, int hi) : lo(lo), hi(hi), L(0), R(0) {}

  void build(iter b, iter e) { // array 1-indexed
    if (lo == hi || b == e)
      return;
    amt.reserve(e - b + 1);
    amt.pb(0);
    int m = (lo + hi) / 2;
    for (auto it = b; it != e; it++)
      amt.pb(amt.back() + (*it <= m));
    auto p = stable_partition(b, e, [=](int x) { 
      return x <= m; 
    });
    (L = new Wav(lo, m))->build(b, p);
    (R = new Wav(m + 1, hi))->build(p, e);
  }

  int qkth(int l, int r, int k) {
    if (r < l)
      return 0;
    if (lo == hi)
      return lo;
    if (k <= amt[r] - amt[l - 1])
      return L->qkth(amt[l - 1] + 1, amt[r], k);
    return R->qkth(l - amt[l - 1], r - amt[r], k - amt[r] + amt[l - 1]);
  }

  int qleq(int l, int r, int mx) {
    if (r < l || mx < lo)
      return 0;
    if (hi <= mx)
      return r - l + 1;
    return L->qleq(amt[l - 1] + 1, amt[r], mx) +
           R->qleq(l - amt[l - 1], r - amt[r], mx);
  }
};