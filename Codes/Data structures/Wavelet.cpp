struct Wav {
  int lo, hi;
  Wav *left, *right;
  vector<int> amt;

  template <class Iter>
  Wav(int lo, int hi, Iter& b, Iter& e)
      : lo(lo), hi(hi) { // array 1-indexed, check on reference (&)
    if (lo == hi || b == e)
      return;
    amt.reserve(e - b + 1);
    amt.pb(0);
    int mid = (lo + hi) >> 1;
    auto leq = [mid](auto x) { return x <= mid; };
    for (auto it = b; it != e; it++) amt.pb(amt.back() + leq(*it));
    auto p = stable_partition(b, e, leq);
    left = new Wav(lo, mid, b, p);
    right = new Wav(mid + 1, hi, p, e);
  }

  // kth value in [l, r]
  int kth(int l, int r, int k) {
    if (r < l)
      return 0;
    if (lo == hi)
      return lo;
    if (k <= amt[r] - amt[l - 1])
      return left->kth(amt[l - 1] + 1, amt[r], k);
    return right->kth(l - amt[l - 1], r - amt[r], k - amt[r] + amt[l - 1]);
  }

  // Count all values in [l, r] that are in range [x, y]
  int count(int l, int r, int x, int y) {
    if (r < l || y < x || y < lo || hi < x)
      return 0;
    if (x <= lo && hi <= y)
      return r - l + 1;
    return left->count(amt[l - 1] + 1, amt[r], x, y) +
           right->count(l - amt[l - 1], r - amt[r], x, y);
  }
};