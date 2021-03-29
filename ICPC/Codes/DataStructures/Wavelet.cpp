struct Wav {
  #define iter int* // vector<int>::iterator
  int lo, hi;
  Wav *left, *right;
  vector<int> amt;

  Wav(int lo, int hi, iter b, iter e) : lo(lo), hi(hi) { // array 1-indexed
    if (lo == hi || b == e)
      return;
    amt.reserve(e - b + 1);
    amt.pb(0);
    int m = (lo + hi) >> 1;
    for (auto it = b; it != e; it++)
      amt.pb(amt.back() + (*it <= m));
    auto p = stable_partition(b, e, [&](int x) { 
      return x <= m; 
    });
    left = new Wav(lo, m, b, p);
    right = new Wav(m + 1, hi, p, e);
  }

  int kth(int l, int r, int k) {
    if (r < l)
      return 0;
    if (lo == hi)
      return lo;
    if (k <= amt[r] - amt[l - 1])
      return left->kth(amt[l - 1] + 1, amt[r], k);
    return right->kth(l - amt[l - 1], r - amt[r], k - amt[r] + amt[l - 1]);
  }

  int leq(int l, int r, int mx) {
    if (r < l || mx < lo)
      return 0;
    if (hi <= mx)
      return r - l + 1;
    return left->leq(amt[l - 1] + 1, amt[r], mx) +
           right->leq(l - amt[l - 1], r - amt[r], mx);
  }
};