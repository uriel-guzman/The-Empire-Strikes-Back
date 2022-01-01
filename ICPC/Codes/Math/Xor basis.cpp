template <int D>
struct XorBasis {
  using Num = bitset<D>;
  array<Num, D> basis, keep;
  vector<int> from;
  int n = 0, id = -1;

  XorBasis() : from(D, -1) {
    basis.fill(0);
  }

  bool insert(Num x) {
    ++id;
    Num k;
    for (int i = D - 1; i >= 0; i--)
      if (x[i]) {
        if (!basis[i].any()) {
          k[i] = 1, from[i] = id, keep[i] = k;
          basis[i] = x, n++;
          return 1;
        }
        x ^= basis[i], k ^= keep[i];
      }
    return 0;
  }

  optional<Num> find(Num x) {
    // is x in xor-basis set?
    // v ^ (v ^ x) = x
    Num v;
    for (int i = D - 1; i >= 0; i--)
      if (x[i]) {
        if (!basis[i].any())
          return nullopt;
        x ^= basis[i];
        v[i] = 1;
      }
    return optional(v);
  }

  optional<vector<int>> recover(Num x) {
    auto v = find(x);
    if (!v)
      return nullopt;
    Num tmp;
    for (int i = D - 1; i >= 0; i--)
      if (v.value()[i])
        tmp ^= keep[i];
    vector<int> ans;
    for (int i = tmp._Find_first(); i < D; i = tmp._Find_next(i))
      ans.pb(from[i]);
    return ans;
  }

  optional<Num> operator[](lli k) {
    lli tot = (1LL << n);
    if (k > tot)
      return nullopt;
    Num v = 0;
    for (int i = D - 1; i >= 0; i--)
      if (basis[i]) {
        lli low = tot / 2;
        if ((low < k && v[i] == 0) || (low >= k && v[i]))
          v ^= basis[i];
        if (low < k)
          k -= low;
        tot /= 2;
      }
    return optional(v);
  }
};